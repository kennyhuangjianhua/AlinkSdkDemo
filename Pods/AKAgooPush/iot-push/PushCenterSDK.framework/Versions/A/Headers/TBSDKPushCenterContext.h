//    '########'########::'######:'########:'##:::'##:
//    ... ##..::##.... ##'##... ##:##.... ##:##::'##::
//    ::: ##::::##:::: ##:##:::..::##:::: ##:##:'##:::
//    ::: ##::::########:. ######::##:::: ##:#####::::
//    ::: ##::::##.... ##:..... ##:##:::: ##:##. ##:::
//    ::: ##::::##:::: ##'##::: ##:##:::: ##:##:. ##::
//    ::: ##::::########:. ######::########::##::. ##:
//    :::..::::........:::......::........::..::::..::
//
//  Created by 亿刀 pushsdk_version 1.1  iTeam on 13-3-7.
//  Copyright (c) 2013年 亿刀  iTeam. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TBSDKPushCenterModel.h"

/** 存储回调信息的数据模型类
 */
@interface TBSDKPushCenterContext : NSObject

/** 回调对象 */
@property (nonatomic, unsafe_unretained) id<TBSDKPushCenterDataModelDelegate>   modelDelegate;

/** 操作失败后，回调block */
@property (nonatomic, strong) PushCenterModelFailureBlock                       failureBlock;

/** 操作失成功，回调block */
@property (nonatomic, strong) PushCenterModelSuccessBlock                       successBlock;

/** 初始化context
 *
 *  @param  delegate        回调对象
 *  @param  successBlock    操作失败后，回调block
 *  @param  failureBlock    操作失成功，回调block
 */
+ (TBSDKPushCenterContext *)contextWithModelDelegate:(id<TBSDKPushCenterDataModelDelegate>)delegate
                                   modelSuccessBlock:(PushCenterModelSuccessBlock)successBlock
                                   modelFailureBlock:(PushCenterModelFailureBlock)failureBlock;

- (void)setCallbackforModel:(TBSDKPushCenterModel *)model;

@end