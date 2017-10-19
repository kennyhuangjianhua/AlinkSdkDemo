//
//  AlinkSDKCore.h
//  AlinkSDK
//
//  Created by 文季 on 12/14/2016.
//  Copyright © 2016 Alibaba, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AlinkRequest.h"
#import "AlinkRequestTask.h"

#define kAlinkSDK AlinkSDK.sharedManager

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const kAKNotificationDownStream;

/**
 *	Alink协议及相关操作
 */
@interface AlinkSDK : NSObject

/**
 *	单例
 */
+ (instancetype)sharedManager;

/**
 异步初始化

 @param completionHandler 结果回调
 */
- (void)asyncInit:(nullable void (^)(NSError  * _Nullable error))completionHandler;

/**
 * 上行通道
 *
 * 如果请求支持取消，返回具体任务的实例，如果不支持取消则返回nil
 * 如果执行出错在completionHandler返回
 *
 * @param method 请求的方法
 * @param params 请求的参数
 * @param completionHandler 请求结果回调
 *
 * @return 任务实例
 */
- (nullable id<AlinkRequestTask>)invokeWithMethod:(NSString *)method
                                           params:(NSDictionary *)params
                                completionHandler:(AlinkResponseHandler)completionHandler;

/**
 * 上行通道
 *
 * @param request 请求
 * @param completionHandler 请求结果回调
 * @return 任务实例
 */
- (nullable id<AlinkRequestTask>)invokeWithRequest:(AlinkRequest *)request
                                 completionHandler:(AlinkResponseHandler)completionHandler;

/**
 * 下行通道
 * 有DownStream既会回调，也会发送kAKNotificationDownStream通知
 *
 * @param callback 服务端下行消息
 */
- (void)setDownStreamCallback:(AlinkCallback)callback;

@end

NS_ASSUME_NONNULL_END

