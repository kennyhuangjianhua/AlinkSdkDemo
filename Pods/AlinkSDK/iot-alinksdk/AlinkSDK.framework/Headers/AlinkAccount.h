//
//  AlinkAccount.h
//  AlinkSDK
//
//  Created by 文季 on 2017/5/22.
//
//

#import <Foundation/Foundation.h>
#import "AlinkLoginProtocol.h"

NS_ASSUME_NONNULL_BEGIN

/**
 统一账号模块
 */
@interface AlinkAccount : NSObject

/**
 单例
 */
+ (instancetype)sharedInstance;

/**
 登录
 
 @param viewController      从该viewController上弹出登录框，如果viewController为nil，从keyWindow的rootViewController弹出
 @param completionHandler   登录结果回调
 @param cancelationHandler  用户取消回调
 */
- (void)loginWithViewController:(nullable UIViewController *)viewController completionHandler:(void (^)(BOOL isSuccessful, NSDictionary *loginResult))completionHandler cancelationHandler:(void (^)())cancelationHandler;

/**
 刷新Token
 
 @param option 刷新选项
 @param completionHandler 刷新结果回调
 */
- (void)refreshToken:(AKLoginOption)option completion:(void (^)(BOOL isSuccessful, NSDictionary *loginResult))completionHandler;

/**
 登出
 
 @param completionHandler 完成回调
 */
- (void)logout:(nullable void (^)(NSError *error))completionHandler;

/**
 是否登录
 
 @return 是否登录
 */
- (BOOL)isLogin;

/**
 当前登录账号的session信息
 
 @return session信息
 */
- (NSDictionary *)currentSession;

/**
 安装一个自定义的登录模块

 @param loginHandler 自定义登录协议
 */
- (void)installCustomLoginModule:(id<AlinkLoginProtocol>)loginHandler;

/**
 获取当前安装的登录模块
 
 @return 登录模块实例
 */
- (id<AlinkLoginProtocol>)loginModule;

@end

NS_ASSUME_NONNULL_END
