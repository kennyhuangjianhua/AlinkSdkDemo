//
//  AlinkLoginProtocol.h
//  Pods
//
//  Created by 文季 on 2016/12/27.
//
//

#import <UIKit/UIKit.h>
#import "AlinkDefine.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const kAKNotificationUserLoggedIn;     ///< 登录成功通知Key
FOUNDATION_EXPORT NSString * const kAKNotificationUserLoggedOut;    ///< 登出成功通知Key
FOUNDATION_EXPORT NSString * const kAKNotificationUserGiveUpLogin;  ///< 取消登录通知Key


FOUNDATION_EXPORT NSString * const kAKSessionKeyAccount;    ///< 账号ID
FOUNDATION_EXPORT NSString * const kAKSessionKeyToken;      ///< 账号登录Token
FOUNDATION_EXPORT NSString * const kAKSessionKeyNick;       ///< 用户昵称
FOUNDATION_EXPORT NSString * const kAKSessionKeyAvatarUrl;  ///< 用户头像URL
FOUNDATION_EXPORT NSString * const kAKSessionKeyRawSession; ///< 原始的Session信息，用于Debug，可选


/**
 Alink登录协议
 */
@protocol AlinkLoginProtocol <NSObject>

@required

/**
 登录
 
 @param viewController      从该viewController上弹出登录框，如果viewController为nil，从keyWindow的rootViewController弹出
 @param completionHandler   登录结果回调
 @param cancelationHandler  用户取消回调
 */
- (void)loginWithViewController:(nullable UIViewController *)viewController completionHandler:(void (^)(BOOL isSuccessful, NSDictionary *loginResult))completionHandler cancelationHandler:(void (^)())cancelationHandler;

/**
 刷新登录态Token
 
 @param option 登录选项
 @param completionHandler 刷新结果回调，刷新成功loginResult为currentSession，刷新失败loginResult的key为msg，value为错误详情字符串
 */
- (void)refreshToken:(AKLoginOption)option completion:(void (^)(BOOL isSuccessful, NSDictionary *loginResult))completionHandler;

/**
 登出
 
 @param completionHandler 完成回调
 */
- (void)logout:(void (^)(NSError *error))completionHandler;

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
 账号类型：OA，TAOBAO，...
 
 @return 账号类型
 */
- (NSString *)accountType;

@end

NS_ASSUME_NONNULL_END
