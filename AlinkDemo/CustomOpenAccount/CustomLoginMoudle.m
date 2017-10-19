//
//  CustomLoginMoudle.m
//  AlinkDemo
//
//  Created by 文季 on 2017/6/6.
//  Copyright © 2017年 aliyun. All rights reserved.
//

#import "CustomLoginMoudle.h"
#import <ALBBOpenAccountSDK/ALBBOpenAccountSDK.h>
#import <AlinkSDK/AlinkOpenSDK.h>

//使用DDLog打印日志
#import <CocoaLumberjack/CocoaLumberjack.h>
static DDLogLevel ddLogLevel = DDLogLevelAll;

@interface CustomLoginMoudle() <ALBBOpenAccountSSODelegate>

@property (nonatomic, assign) BOOL isPresenting; //登录框是否已弹出
@property (nonatomic, copy) void (^completionHandler)(BOOL isSuccessful, NSDictionary *loginResult);
@property (atomic, assign, getter=isInited) BOOL inited; //OpenAccount是否已初始化完成

@end

@implementation CustomLoginMoudle

- (instancetype)init {
    self = [super init];
    if (self) {
        //指定环境
        TaeSDKEnvironment env;
        switch (kAlinkEnvConfig.env) {
            case AlinkDaily:
                env = TaeSDKEnvironmentDaily;
                break;
            case AlinkPreRelease:
                env = TaeSDKEnvironmentPreRelease;
                break;
            case AlinkSandbox:
                env = TaeSDKEnvironmentSandBox;
                break;
            default:
                env = TaeSDKEnvironmentRelease;
                break;
        }
        [[ALBBOpenAccountSDK sharedInstance] setTaeSDKEnvironment:env];
        //NOTE: OpenAccount是异步初始化的，大部分情况下都是200ms左右，偶发有可能比较慢
        //调整为同步初始化，设置超时0.5s，避免短时间内OpenAccount未初始化完成，session相关信息未ready，导致依赖登录态的Alink请求失败
        //需要检测是否初始化完成，避免后续调用OpenAccount出问题（如，未初始化完成，调用接口不报错而是没有回调）
        DDLogInfo(@"OpenAccount 开始初始化");
        dispatch_group_t group = dispatch_group_create();
        dispatch_group_enter(group);
        [[ALBBOpenAccountSDK sharedInstance] asyncInit:^{
            DDLogInfo(@"OpenAccount初始化成功");
            id<ALBBOpenAccountUIService> uiService = ALBBService(ALBBOpenAccountUIService);
            [uiService setOpenAccountSSODelegate:self];
            _inited = YES;
            dispatch_group_leave(group);
        } failure:^(NSError *error) {
            DDLogWarn(@"OpenAccount初始化出错：%@", error);
            dispatch_group_leave(group);
        }];
        dispatch_group_wait(group, 0.5);
    }
    
    return self;
}

//OpenAccount的SSO登录成功或失败不会触发completionHandler或cancelationHandler回调，实现delegate
- (void)openAccountSSOLoginError:(NSError *)error Session:(ALBBOpenAccountSession *)session {
    _isPresenting = NO;
    if (self.completionHandler) {
        NSDictionary *loginResult = [self currentSession];
        self.completionHandler(!error, loginResult);
    }
    
    if (!error) {
        [[NSNotificationCenter defaultCenter] postNotificationName:kAKNotificationUserLoggedIn object:nil];
    }
}

- (void)loginWithViewController:(nullable UIViewController *)viewController completionHandler:(void (^)(BOOL isSuccessful, NSDictionary *loginResult))completionHandler cancelationHandler:(void (^)())cancelationHandler {
    if (!self.isInited) {
        DDLogWarn(@"OpenAccount未初始化完成");
        if (completionHandler) {
            completionHandler(NO, @{@"msg" : @"OpenAccount未初始化完成"});
        }
        return;
    }
    
    UIViewController *vc = viewController;
    if (!vc) {
        vc = [self getTopContoller];
    }
    
    id<ALBBOpenAccountUIService> uiService = ALBBService(ALBBOpenAccountUIService);
    //登录框已弹出，直接监听登录结果，避免弹出多个登陆框
    if (_isPresenting) {
        __block id observerForSuccess;
        __block id observerForCancel;
        void (^removeObserverBlock)() = ^{
            if (observerForSuccess) {
                [[NSNotificationCenter defaultCenter] removeObserver:observerForSuccess];
            }
            if (observerForCancel) {
                [[NSNotificationCenter defaultCenter] removeObserver:observerForCancel];
            }
        };
        observerForSuccess = [[NSNotificationCenter defaultCenter] addObserverForName:kAKNotificationUserLoggedIn object:nil queue:nil usingBlock:^(NSNotification * _Nonnull note) {
            if (completionHandler) {
                completionHandler(YES, [self currentSession]);
            }
            
            removeObserverBlock();
        }];
        
        observerForCancel = [[NSNotificationCenter defaultCenter] addObserverForName:kAKNotificationUserGiveUpLogin object:nil queue:nil usingBlock:^(NSNotification * _Nonnull note) {
            if (cancelationHandler) {
                cancelationHandler();
            }
            
            removeObserverBlock();
        }];
        
        return;
    }
    
    _isPresenting = YES;
    self.completionHandler = completionHandler;
    [uiService presentLoginViewController:vc success:^(ALBBOpenAccountSession *currentSession) {
        _isPresenting = NO;
        //登录成功
        if (completionHandler) {
            completionHandler(YES, [self currentSession]);
        }
        
        [[NSNotificationCenter defaultCenter] postNotificationName:kAKNotificationUserLoggedIn object:nil];
    } failure:^(NSError *error) {
        //用户取消登录
        _isPresenting = NO;
        if (cancelationHandler) {
            cancelationHandler();
        }
        
        [[NSNotificationCenter defaultCenter] postNotificationName:kAKNotificationUserGiveUpLogin object:nil];
    }];
}

- (void)refreshToken:(AKLoginOption)option completion:(void (^)(BOOL isSuccessful, NSDictionary *loginResult))completionHandler {
    if (!self.isInited) {
        DDLogWarn(@"OpenAccount未初始化完成");
        if (completionHandler) {
            completionHandler(NO, @{@"msg" : @"OpenAccount未初始化完成"});
        }
        return;
    }
    
    //刷新登陆token，使用自定义账号的token换取iotToken服务端报token失效的时候触发
    //根据option选项，进行自动登录或唤起登录框
    DDLogDebug(@"开始刷新OpenAccount sessionId");
    [[ALBBOpenAccountSession sharedInstance] refreshSessionIDWithCallback:^(NSString *sid, NSError *err) {
        DDLogDebug(@"刷新OpenAccount sessionId完成：sid: %@, error: %@", sid, err);
        //自动刷新token成功
        if (!err) {
            if (completionHandler) {
                completionHandler(YES, [self currentSession]);
            }
        }
        //自动刷新token失败
        else {
            BOOL isSeesionExpired = NO;
            if (err.code == ALBBOpenAccountCodeSessionExpireError ||
                err.code == ALBBOpenAccountCodeLoginError) {
                isSeesionExpired = YES;
            }
            
            //如果要求唤起登录框手动登录
            if (isSeesionExpired &&
                option == AKLoginOptionAutoLoginAndManualLogin) {
                [self loginWithViewController:nil completionHandler:completionHandler cancelationHandler:^{
                    if (completionHandler) {
                        NSDictionary *errorDict = @{@"msg" : @"用户取消登录"};
                        completionHandler(NO, errorDict);
                    }
                }];
                return;
            }
            
            //出现了其他错误
            if (completionHandler) {
                NSDictionary *errorDict = @{@"msg" : err.localizedDescription ?: @""};
                completionHandler(!err, errorDict);
            }
        }
    }];
}

- (void)logout:(void (^)(NSError *error))completionHandler {
    if (!self.isInited) {
        DDLogWarn(@"OpenAccount未初始化完成");
        if (completionHandler) {
            NSError *error = [[NSError alloc] initWithDomain:@"OpenAccount"
                                                        code:-1
                                                    userInfo:@{NSLocalizedDescriptionKey : @"OpenAccount未初始化完成"}];
            completionHandler(error);
        }
        return;
    }
    
    [[ALBBOpenAccountSession sharedInstance] logout];
    //发送登出通知
    [[NSNotificationCenter defaultCenter] postNotificationName:kAKNotificationUserLoggedOut object:nil];
    if (completionHandler) {
        completionHandler(nil);
    }
}

- (BOOL)isLogin {
    return [[ALBBOpenAccountSession sharedInstance] isLogin];
}

- (NSDictionary *)currentSession {
    ALBBOpenAccountUser *user = [[ALBBOpenAccountSession sharedInstance] getUser];
    //原始的账号session信息，主要用于Debug，可选
    NSDictionary *rawSession = @{
                                 @"accountId" : user.accountId ?: @"",
                                 @"authToken" : [[ALBBOpenAccountSession sharedInstance] getAuthToken] ?: @"",
                                 @"sid" : [[ALBBOpenAccountSession sharedInstance] sessionID] ?: @"",
                                 @"accountInfo" : user.openaccountInfoDict?:@{},
                                 @"oAuthInfo" : user.oauthInfoDict?:@{}
                                 };
    DDLogDebug(@"currentSession: %@", rawSession);
    
    NSString *nick = user.displayName;
    if (!nick) {
        nick = user.mobile;
    }
    //以下几个协议字段必须实现
    return @{
             kAKSessionKeyAccount : user.accountId ?: @"",
             kAKSessionKeyToken : [[ALBBOpenAccountSession sharedInstance] sessionID] ?: @"",
             kAKSessionKeyNick : nick ?: @"",
             kAKSessionKeyAvatarUrl : user.avatarUrl ?: @""
             };
}

- (NSString *)accountType {
    //实现你的自定义账号类型
    return @"OA";
}

#pragma mark - Helper

- (UIViewController *)getTopContoller {
    UIViewController *result = nil;
    UIWindow * window = [[UIApplication sharedApplication] keyWindow];
    if (window.windowLevel != UIWindowLevelNormal)
    {
        NSArray *windows = [[UIApplication sharedApplication] windows];
        for(UIWindow * tmpWin in windows)
        {
            if (tmpWin.windowLevel == UIWindowLevelNormal)
            {
                window = tmpWin;
                break;
            }
        }
    }
    
    UIView *frontView = [[window subviews] objectAtIndex:0];
    id nextResponder = [frontView nextResponder];
    
    if ([nextResponder isKindOfClass:[UIViewController class]])
        result = nextResponder;
    else
        result = window.rootViewController;
    
    return result;
}

@end
