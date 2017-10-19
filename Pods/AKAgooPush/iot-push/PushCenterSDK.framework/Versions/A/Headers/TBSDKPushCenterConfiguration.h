//    '########'########::'######:'########:'##:::'##:
//    ... ##..::##.... ##'##... ##:##.... ##:##::'##::
//    ::: ##::::##:::: ##:##:::..::##:::: ##:##:'##:::
//    ::: ##::::########:. ######::##:::: ##:#####::::
//    ::: ##::::##.... ##:..... ##:##:::: ##:##. ##:::
//    ::: ##::::##:::: ##'##::: ##:##:::: ##:##:. ##::
//    ::: ##::::########:. ######::########::##::. ##:
//    :::..::::........:::......::........::..::::..::
//
//  Created by 亿刀 pushsdk_version 1.1  iTeam on 13-2-28.
//  Copyright (c) 2013年 亿刀  iTeam. All rights reserved.
//

#import <Foundation/Foundation.h>

#define PUBKEY_KEY_IN_USER_DEFALUT                  @"pubkey key in userDefault"
#define PUBKEY_DEVICEID_KEY_IN_USER_DEFALUT         @"deviceID of pubkey key in userDefalut"
#define PUSH_USER_TOKEN_KEY                         @"PUSH_USER_TOKEN_KEY"
#define PUSH_KEY_APP_VERSION                        @"PUSH_KEY_APP_VERSION"

/** PushCenterSDK的配置类 */
@interface TBSDKPushCenterConfiguration : NSObject

/** 以单例模式初始化 */
+ (instancetype)shareInstance;

/** 调用网络接口，创建的deviceID */
@property (nonatomic, strong) NSString                                          *deviceID;

/** 已废弃 */
@property (nonatomic, strong) NSString                                          *pushkey;

/** 绑定API的返回值，解绑的使用。 */
@property (nonatomic, strong) NSString                                          *pushUserToken;

/** 自定义AppVersion
 * 强烈建议：如果使用自定义AppVersion, 参数版本最好加上特殊后缀，标示该版本并非主客真实版本
 */
@property (nonatomic, strong) NSString                                          *customAppVersion;

@end