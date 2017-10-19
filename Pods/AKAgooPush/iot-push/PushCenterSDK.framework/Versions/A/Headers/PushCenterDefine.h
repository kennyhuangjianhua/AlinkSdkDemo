//    '########'########::'######:'########:'##:::'##:
//    ... ##..::##.... ##'##... ##:##.... ##:##::'##::
//    ::: ##::::##:::: ##:##:::..::##:::: ##:##:'##:::
//    ::: ##::::########:. ######::##:::: ##:#####::::
//    ::: ##::::##.... ##:..... ##:##:::: ##:##. ##:::
//    ::: ##::::##:::: ##'##::: ##:##:::: ##:##:. ##::
//    ::: ##::::########:. ######::########::##::. ##:
//    :::..::::........:::......::........::..::::..::
//
//  Created by 亿刀 pushsdk_version 1.1  iTeam on 13-3-3.
//  Copyright (c) 2013年 亿刀  iTeam. All rights reserved.
//

#ifndef PushCenterDemo_Define_h
#define PushCenterDemo_Define_h

//----------------------------------------消息名称-----------------------------------------------------//

#define kPushCenterNewSummaryNotification @"PushCenter New Summary Notification"
#define kPushCenterGetDetailNotification  @"PushCenter Get Detail Notification"

//---------------------------------------------------------------------------------------------------//






//----------------------------------------------------------------------------------------------------//
/** 编译设置
 *  如果以framework的方式引入PushCenterSDK，kPushCenterSDKIsFramework的定义不起任何作用
 *  如果源码的方式引入NetworkSDK，“TBSDkPushCenterSDK.h”将将产生条件编译
 */
#define kPushCenterSDKIsFramework 0
//----------------------------------------------------------------------------------------------------//

#define PUSH_CNETER_ERROR_DOMAIN                    @"com.taobao.push"
#define ECODE_PUSH_ACCS_MESSAGE_BUILD_FAILED        6000
#define ECODE_PUSH_ACCS_MANAGER_GET_FAILED          6001
#define ECODE_PUSH_ACCS_REPONSE_NO_RESULT_DATA      6002
#define ECODE_PUSH_ACCS_REPONSE_FORMAT_NO_JSON      6003

#define ECODE_PUSH_REGISTER_RESPONSE_EMPTY          7000
#define ECODE_PUSH_REGISTER_RESPONSE_ERROR          7001

#endif
