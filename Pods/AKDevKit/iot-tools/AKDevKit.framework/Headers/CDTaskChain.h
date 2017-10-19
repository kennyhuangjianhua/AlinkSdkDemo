//
//  CDTaskChain.h
//  ticket
//
//  Created by 张光宇 on 3/31/15.
//
//

#import <Foundation/Foundation.h>

@class CDTask,CDTaskResult;
/////////// CDTaskChain
@interface CDTaskChain : NSObject
@property(nonatomic,assign)NSTimeInterval minIntervalBetweenTask;

@property (nonatomic,copy) void(^completion)(CDTaskChain *chain);
@property (nonatomic,copy) void(^singleTaskCompletion)(CDTaskChain *chain,CDTask *completedTask);
@property (nonatomic,copy) void(^messageProgress)(NSString *message);
@property(nonatomic,assign,readonly)int reRunCounter;

+ (instancetype)runWithTasks:(NSArray *)tasks completion:(void(^)(CDTaskChain *chain))completion;

- (CDTask *)previousTask:(CDTask *)task;

- (instancetype)initWithTask:(CDTask *)task;
- (instancetype)initWithTasks:(NSArray *)tasks;

- (CDTask *)findWithTaskID:(NSString *)taskID;

- (void)addTask:(CDTask *)task;

- (CDTaskResult *)completionResult;

- (BOOL)isSuccessed;

- (NSArray *)allTasks;

- (BOOL)isCompleted;

- (BOOL)isCanceled;

- (void)reRunTask:(CDTask *)task delay:(NSTimeInterval)interval;

- (void)reportProgressWithMessage:(NSString *)message;

//- (void)proceedWithMessage:(NSString *)message;
//- (void)proceedWithMessage:(NSString *)message payload:(id)payload;
//- (void)proceedWithMessage:(NSString *)message payload:(id)payload error:(NSError *)error;

//! 跳过尚未执行的task，直接宣布chain执行完毕
- (void)allTaskFinished:(BOOL)successed payload:(id)payload error:(NSError *)error;

- (void)taskFinished:(BOOL)successed payload:(id)payload error:(NSError *)error;

- (void)taskFinished:(CDTaskResult *)result;

- (void)resume;

- (void)suspend;

- (void)cancel;

- (void)reRunChainAfterDelay:(NSTimeInterval)delay;
@end