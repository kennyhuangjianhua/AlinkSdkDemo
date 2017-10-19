//
//  AlinkEnvConfig.h
//  AlinkSDK
//
//  Created by 文季 on 12/14/2016.
//  Copyright © 2016 Alibaba, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 Alink环境
 外部环境只能用AlinkRelease
 */
typedef NS_ENUM(NSInteger, AlinkEnviroment) {
	AlinkDaily = 0,			///< 日常 供内部调试使用 ,外部只能用AlinkRelease
	AlinkPreRelease = 1,	///< 预发 供内部调试使用 ,外部只能用AlinkRelease
	AlinkRelease = 2,		///< 线上
	AlinkSandbox = 3		///< 沙箱 供内部调试使用 ,外部只能用AlinkRelease
};

#define kAlinkEnvConfig AlinkEnvConfig.sharedInstance

NS_ASSUME_NONNULL_BEGIN


/**
 Alink环境配置信息
 */
@interface AlinkEnvConfig : NSObject

@property (nonatomic, assign) AlinkEnviroment env;  ///< 指定环境，默认线上
@property (nonatomic, strong) NSString *appKey;     ///< 指定appKey
@property (nonatomic, strong) NSString *appSecret;  ///< 指定appSecret


/**
 打开调试日志

 @param open 是否打开
 */
- (void)openDebugLog:(BOOL)open;

/**
 单例

 @return  单例
 */
+ (instancetype)sharedInstance;

@end

NS_ASSUME_NONNULL_END
