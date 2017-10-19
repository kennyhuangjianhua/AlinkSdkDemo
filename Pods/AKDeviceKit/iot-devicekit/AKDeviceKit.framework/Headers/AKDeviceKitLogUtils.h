//
//  AKDeviceKitLogUtils
//  Alink Device Kit
//
//  Created by 文季 on 2017/4/11.
//  Copyright © 2017年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, AKDeviceKitLogLevel) {
    AKDeviceKitLogLevelVerbose = 0,
    AKDeviceKitLogLevelDebug,
    AKDeviceKitLogLevelInfo,
    AKDeviceKitLogLevelWarn,
    AKDeviceKitLogLevelError
};

@protocol AKDeviceKitLogDelegate <NSObject>

@optional

- (void)log:(AKDeviceKitLogLevel)flag file:(const char *)file func:(const char *)func line:(int)line fmt:(NSString *)fmt args:(va_list)args;

@end

@interface AKDeviceKitLogUtils : NSObject

+ (void)setDelegate:(id<AKDeviceKitLogDelegate>)delegate;

+ (void)turnLogOn:(BOOL)on;

@end
