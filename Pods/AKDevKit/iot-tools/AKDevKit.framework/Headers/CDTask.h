//
//  CDTask.h
//  CDKit
//
//  Created by 张光宇 on 3/24/15.
//  Copyright (c) 2015 Copyright (c) 2014年 Alibaba(China)Technology Co.,Ltd. All rights reserved.  Copyright (c) 2014年 Alibaba(China)Technology Co.,Ltd. All rights reserved. Alibaba(China)Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CDTaskChain.h"

typedef NS_ENUM(NSInteger, CDTaskState) {
    CDTaskNotStart = 0,
    CDTaskRunning = 1,
    CDTaskSuspended = 2,
    CDTaskCompleted = 3,
} NS_ENUM_AVAILABLE(NSURLSESSION_AVAILABLE, 7_0);


@class CDTaskResult,CDTask;

typedef id (^CDTaskBlock)(CDTaskChain *chain,CDTask *cdTask);
typedef void (^CDTaskBlock2)(CDTaskChain *chain,CDTask *cdTask);

/////////// CDTaskResult
@interface CDTaskResult : NSObject

@property(nonatomic,assign)BOOL successed;

//@property(nonatomic,assign)NSString *message;

@property(nonatomic,strong)NSError *error;

@property(nonatomic,strong)id payload;

+ (instancetype)resultWithSuccessed:(BOOL)successed payload:(id)payload error:(NSError *)error;

@end

/////////// CDTask
@interface CDTask : NSObject

@property (nonatomic, strong)NSString *taskId;

@property (nonatomic, copy) CDTaskBlock proceedBlock;

@property (nonatomic, copy) void(^cancelBlock)(void);

@property (nonatomic,assign,readonly)int runblockCounter;

@property (nonatomic,assign)CDTaskState state;

@property (nonatomic,strong)CDTaskResult *result;


+ (instancetype)taskWithID:(NSString *)taskID block:(CDTaskBlock)block;

+ (instancetype)taskWithBlock:(CDTaskBlock)block;
+ (instancetype)taskWithBlock2:(CDTaskBlock2)block;

- (void)setTimeoutInterval:(NSTimeInterval)interval block:(void (^)(void))timeoutBlock;

- (void)runBlock:(CDTaskChain *)chain;

- (void)cancel;

- (void)resume;

- (void)suspend;

@end

@interface CDTaskChain (Ext)
+ (instancetype)chainWithTaskBlock:(CDTaskBlock)block;
@end



