//
//  AlinkRequestTask.h
//  AlinkSDK
//
//  Created by 文季 on 2016/12/14.
//
//

#import <Foundation/Foundation.h>

/**
 Alink请求任务协议
 */
@protocol AlinkRequestTask <NSObject>

/**
 挂起任务
 */
- (void)suspend;

/**
 继续任务
 */
- (void)resume;

/**
 取消任务
 */
- (void)cancel;

@end
