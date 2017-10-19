//
//  AlinkProtocalDefine.h
//  Pods
//
//  Created by Dong on 2017/4/4.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AlinkResponse;

/**
 登录选项
 */
typedef NS_ENUM(NSInteger, AKLoginOption) {
    AKLoginOptionAutoLoginOnly = 1,         ///< 只走AutoLogin，失败什么都不做！
    AKLoginOptionAutoLoginAndManualLogin,   ///< 先走AutoLogin，失败再拉登录页面
};


/**
 请求响应回调

 @param response 响应
 */
typedef void(^AlinkResponseHandler)(AlinkResponse *response);

/**
 字典回调
 
 @param dict 字典
 */
typedef void(^AlinkCallback)(NSDictionary *dict);

NS_ASSUME_NONNULL_END
