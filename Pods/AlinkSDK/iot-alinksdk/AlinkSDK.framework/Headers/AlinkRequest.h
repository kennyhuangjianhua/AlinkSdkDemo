//
//  AlinkRequest.h
//  AlinkSDK
//
//  Created by 文季 on 2017/4/13.
//  Copyright © 2017年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AlinkDefine.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Alink请求对象
 */
@interface AlinkRequest : NSObject

@property (nonatomic, copy) NSString *method;                       ///< api方法
@property (nonatomic, copy) NSString *apiVersion;                   ///< api版本
@property (nonatomic, strong) NSDictionary *params;                 ///< 参数
@property (nonatomic, strong) NSDictionary *options;                ///< 更多选项

@property (nonatomic, assign, getter=isNeedLogin) BOOL needLogin;   ///< 登录才能访问
@property (nonatomic, assign) AKLoginOption sessionExpiredOption;   ///< 过期自动重登／拉起登录框重登

@end

NS_ASSUME_NONNULL_END
