//
//  DemoLoggingFormatter.m
//  AlinkDemo
//
//  Created by 文季 on 2017/5/31.
//  Copyright © 2017年 aliyun. All rights reserved.
//

#import "DemoLoggingFormatter.h"

//日志打印格式化
@implementation DemoLoggingFormatter

+ (NSDateFormatter *)dateFormatter {
    static NSDateFormatter *_dateFormatter = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _dateFormatter = [[NSDateFormatter alloc] init];
        [_dateFormatter setDateFormat:@"MM-dd HH:mm:ss.SSS"];
    });
    
    return _dateFormatter;
}

- (NSString *)formatLogMessage:(DDLogMessage *)logMessage
{
    NSString *logLevel;
    switch (logMessage.flag)
    {
        case DDLogFlagError		: logLevel = @"E"; break;
        case DDLogFlagWarning	: logLevel = @"W"; break;
        case DDLogFlagInfo		: logLevel = @"I"; break;
        case DDLogFlagDebug		: logLevel = @"D"; break;
        default					: logLevel = @"V"; break;
    }
    
    //Format the message for the server-side log file parser
    NSString *timestampStr = [[self.class dateFormatter] stringFromDate:logMessage.timestamp];
    
    return [NSString stringWithFormat:@"[%@ %@] %@ || %@ %@ || %@",
            logLevel,
            timestampStr,
            logMessage.function,
            logMessage.fileName,
            @(logMessage.line),
            [self _truncateMessage:logMessage.message]];
}

- (NSString *)_truncateMessage:(NSString *)string {
    static int kMaxLines = 100;
    NSUInteger numberOfLines, index, stringLength = [string length];
    
    for (index = 0, numberOfLines = 0; index < stringLength; numberOfLines++){
        index = NSMaxRange([string lineRangeForRange:NSMakeRange(index, 0)]);
        if(numberOfLines >= kMaxLines)
            break;
    }
    
    NSString *result = [string substringToIndex:index];
    if (numberOfLines == kMaxLines) {
        result = [result stringByAppendingString:@"....."];
    }
    return result;
}

@end
