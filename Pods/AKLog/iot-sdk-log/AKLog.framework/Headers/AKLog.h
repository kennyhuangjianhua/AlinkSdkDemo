//
//  AKLog.h
//  BoneKit
//
//  Created by 文季 on 2017/4/12.
//  Copyright © 2017年 Alibaba Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, AKLogLevel) {
    AKLogLevelVerbose = 0,
    AKLogLevelDebug,
    AKLogLevelInfo,
    AKLogLevelWarn,
    AKLogLevelError
};

@protocol AKLogDelegate <NSObject>

- (void)log:(AKLogLevel)flag file:(const char *)file func:(const char *)func line:(int)line fmt:(NSString *)fmt args:(va_list)args;

@end

@interface AKLog : NSObject

+ (void)turnLogOn:(BOOL)on;
+ (void)log:(AKLogLevel)flag file:(const char *)file func:(const char *)func line:(int)line fmt:(NSString *)fmt, ...;
+ (void)log:(AKLogLevel)flag file:(const char *)file func:(const char *)func line:(int)line fmt:(NSString *)fmt args:(va_list)args;

+ (void)setDelegate:(id<AKLogDelegate>)delegate;

@end


#define AKLogError(frmt, ...)	[AKLog log:AKLogLevelError file:__FILE__ func:__PRETTY_FUNCTION__ line:__LINE__ fmt:(frmt), ##__VA_ARGS__]
#define AKLogWarn(frmt, ...)	[AKLog log:AKLogLevelWarn file:__FILE__ func:__PRETTY_FUNCTION__ line:__LINE__ fmt:(frmt), ##__VA_ARGS__]
#define AKLogInfo(frmt, ...)	[AKLog log:AKLogLevelInfo file:__FILE__ func:__PRETTY_FUNCTION__ line:__LINE__ fmt:(frmt), ##__VA_ARGS__]
#define AKLogDebug(frmt, ...)	[AKLog log:AKLogLevelDebug file:__FILE__ func:__PRETTY_FUNCTION__ line:__LINE__ fmt:(frmt), ##__VA_ARGS__]
#define AKLogVerbose(frmt, ...)	[AKLog log:AKLogLevelVerbose file:__FILE__ func:__PRETTY_FUNCTION__ line:__LINE__ fmt:(frmt), ##__VA_ARGS__]

//! 默认的DDLog协议实现，弱依赖DDLog
@interface AKDDLog : NSObject <AKLogDelegate>

+ (instancetype)sharedInstance;

@end

NS_ASSUME_NONNULL_END
