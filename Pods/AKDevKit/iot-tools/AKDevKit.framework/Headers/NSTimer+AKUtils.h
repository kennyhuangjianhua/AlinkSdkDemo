//
//  NSTimer+AKUtils.h
//  AKDevKit
//
//  Created by 文季 on 16/1/19.
//
//

#import <Foundation/Foundation.h>

@interface NSTimer (AKUtils)

+ (NSTimer *)ak_timerWithTimeInterval:(NSTimeInterval)ti repeats:(BOOL)yesOrNo userInfo:(id)userInfo usingBlock:(void (^)(id userInfo))block;

@end
