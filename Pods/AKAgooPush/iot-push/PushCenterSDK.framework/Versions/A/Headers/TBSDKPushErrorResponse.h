//
//  TBSDKPushErrorResponse.h
//  PushCenterSDK
//
//  Created by wuchen.xj on 16/9/26.
//  Copyright © 2016年 yidao. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TBSDKPushErrorResponse : NSObject
//! 服务器返回的错误码
@property (nonatomic, strong) NSString                                          *errorCode;

//! 错误信息
@property (nonatomic, strong) NSString                                          *msg;

//! 子错误代码
@property (nonatomic, strong)  NSString                                         *sub_code;

//! 子错误信息
@property (nonatomic, strong)  NSString                                         *sub_msg;

//! 调用接口时传递的参数
@property (nonatomic, strong)  NSDictionary                                     *args;

//! 原始错误信息
@property (nonatomic, strong)  NSDictionary                                     *raw;

//开发调试使用的参数，用于存放代码出错的位置(__FUNCTION__, __LINE__)
@property (nonatomic, strong) NSString                                          *errorLocation;

@property (nonatomic, strong) NSError                                           *error;

@end
