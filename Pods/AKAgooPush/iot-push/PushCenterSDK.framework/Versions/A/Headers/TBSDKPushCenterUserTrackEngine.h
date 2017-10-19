//    '########'########::'######:'########:'##:::'##:
//    ... ##..::##.... ##'##... ##:##.... ##:##::'##::
//    ::: ##::::##:::: ##:##:::..::##:::: ##:##:'##:::
//    ::: ##::::########:. ######::##:::: ##:#####::::
//    ::: ##::::##.... ##:..... ##:##:::: ##:##. ##:::
//    ::: ##::::##:::: ##'##::: ##:##:::: ##:##:. ##::
//    ::: ##::::########:. ######::########::##::. ##:
//    :::..::::........:::......::........::..::::..::
//
//  Created by 亿刀 pushsdk_version 1.1  iTeam on 13-3-18.
//  Copyright (c) 2013年 亿刀  iTeam. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kPageForPushCenter @"agoo"
#define kEventIDForPushCenter 20005

/** TBSDKPushCenterUserTrackEngine用于推送消息统计，如推送消息到达率等。
 */
@interface TBSDKPushCenterUserTrackEngine : NSObject

/** 激活打点，SDK内部调用 */
+ (void)activating;

/** 消息已被点开埋点。
 *
 *  @param  userInfo    launchOptions或userInfo
 */
+ (void)userTrackForReceivePushWithAPS:(NSDictionary *)userInfo;


/** 消息已被点开埋点。
 *
 *  @param  messageId    收到的消息的 'm' 字段
 */
+ (void)userTrackForMessageOpened:(NSString *)messageId;


/** 收到push消息后，埋点。
 *
 *  @param  messageID    消息id
 *  @param  mesgStatus   消息状态 4：消息已到达客户端 8：消息已被点开 9：消息被清除
 */
+ (void)uploadAgooPoint:(NSString *)messageID MsgStatus:(NSString *)mesgStatus;

/** 用户读取的了一个消息的详情 
 *
 *  @param  task    服务器返回的任务id，可以在TBSDKPushCenterMessageListObject对象中获取
 */
+ (void)userTrackForReadWithMessageList:(NSArray *)messageList;

@end
