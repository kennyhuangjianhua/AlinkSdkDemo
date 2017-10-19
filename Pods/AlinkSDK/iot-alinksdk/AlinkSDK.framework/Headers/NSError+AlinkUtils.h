//
//  NSError+AlinkUtils.h
//  AlinkSDK
//
//  Created by 文季 on 2016/12/20.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const AKErrorDomain;

/**
 Alink错误码
 */
typedef NS_ENUM(NSInteger, AKErrorCode) {
    AKErrorSuccess = 0,                     ///< 业务成功
    
    AKErrorUnknownError = 4201,             ///< 客户端内部错误
    AKErrorInvokeNetError = 4101,           ///< 网络错误
    AKErrorInvokeServerError = 4102,        ///< 网关错误或业务网关错误
    AKErrorServerBusinessError = 4103,      ///< 业务错误
    AKErrorLoginTokenIllegalError = 4001,   ///< 登录token失效 或 session过期
};

/**
 * Alink业务错误
 * 两级错误：
 * 1）第一级错误：domain总是AKErrorDomain，code对应AKErrorCode，localizedDescription对应用户感知错误msg
 * 2）第二级错误：通过NSUnderlyingErrorKey把原始错误透出，用于调试和具体业务错误码判断
 */
@interface NSError (AlinkUtils)

+ (instancetype)ak_errorWithCode:(NSInteger)code;
+ (instancetype)ak_errorWithCode:(NSInteger)code userInfo:(NSDictionary *)dict;

/**
 是否网络错误

 @return YES为网络错误
 */
- (BOOL)ak_isNetworkError;
/**
 是否服务器网关错误

 @return YES为服务器网关错误
 */
- (BOOL)ak_isServerError;
/**
 是否服务器业务错误

 @return YES为服务器业务错误
 */
- (BOOL)ak_isServerBusinessError;
/**
 是否为登录相关错误

 @return YES为登录相关错误，登录token失效或session过期
 */
- (BOOL)ak_isLoginTokenIllegalError;
/**
 是否为客户端内部错误

 @return YES为客户端内部检测到错误
 */
- (BOOL)ak_isUnknownError;

@end

NS_ASSUME_NONNULL_END
