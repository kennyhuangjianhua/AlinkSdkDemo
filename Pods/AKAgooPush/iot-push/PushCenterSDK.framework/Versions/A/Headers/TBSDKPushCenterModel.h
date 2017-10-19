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
#import "TBSDKPushErrorResponse.h"

@class TBSDKPushCenterModel;
@class TBSDKPushCenterContext;

@protocol TBSDKPushCenterDataModelDelegate;

/** 操作成功，回调block */
typedef void(^ PushCenterModelSuccessBlock)(TBSDKPushCenterModel *);

/** 操作失败，回调block */
typedef void(^ PushCenterModelFailureBlock)(TBSDKPushCenterModel *, TBSDKPushErrorResponse *);

/** 所有数据处理类的基类
 *  负责回调逻辑和错误处理逻辑
 */
@interface TBSDKPushCenterModel : NSOperation

/** 服务器返回的字符串 */
@property (nonatomic, strong) NSString                                          *responseString;

/** 服务器返回的字符串，转换为JSON */
@property (nonatomic, strong) id                                                responseJSON;

/** 用户传入的userInfo */
@property (nonatomic, strong) NSDictionary                                      *userInfo;

/** 错误描述对象 */
@property (nonatomic, strong) TBSDKPushErrorResponse                            *error;

/** 回调对象 */
@property (nonatomic, weak) id<TBSDKPushCenterDataModelDelegate>   delegate;

/** 回调信息存储对象 */
@property (nonatomic, weak) TBSDKPushCenterContext                 *context;

/** 操作失败，回调block */
@property (nonatomic, copy) PushCenterModelFailureBlock                         modelFailureBlock;

/** 操作成功，回调block */
@property (nonatomic, copy) PushCenterModelSuccessBlock                         modelSuccessBlock;

/** 回调操作成功的代理方法和block */
- (void)performSuccess;

/** 回调操作失败的代理方法和block */
- (void)performFailure;

- (TBSDKPushErrorResponse *)errorWithErrorCode:(NSString *)errorCode
                                       msg:(NSString *)msg
                             errorLocation:(NSString *)errorLocation;

- (void)setErrorAndErrorWithErrorCode:(NSString *)errorCode
                                  msg:(NSString *)msg
                        errorLocation:(NSString *)errorLocation;

@end

/** TBSDKPushCenterModel的delegate需要实现的协议 */
@protocol TBSDKPushCenterDataModelDelegate <NSObject>

@optional

/** 操作成功的代理方法 
 *
 *  @param pushCenterDataModel  数据处理对象，在pushCenterDataModel的属性中可以获取服务器返回值，错误描述等
 *  @param error                错误描述对象
 */
- (void)pushCenterDataModelDidFail:(TBSDKPushCenterModel *)pushCenterDataModel
                             error:(TBSDKPushErrorResponse *)error;

/** 操作成功的代理方法
 *
 *  @param pushCenterDataMode  数据处理对象，在pushCenterDataModel的属性中可以获取服务器返回值，错误描述等
 */
- (void)pushCenterDataModelDidSuccess:(TBSDKPushCenterModel *)pushCenterDataMode;


@end
