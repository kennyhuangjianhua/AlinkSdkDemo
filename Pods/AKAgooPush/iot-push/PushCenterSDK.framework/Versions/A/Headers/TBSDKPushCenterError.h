//    '########'########::'######:'########:'##:::'##:
//    ... ##..::##.... ##'##... ##:##.... ##:##::'##::
//    ::: ##::::##:::: ##:##:::..::##:::: ##:##:'##:::
//    ::: ##::::########:. ######::##:::: ##:#####::::
//    ::: ##::::##.... ##:..... ##:##:::: ##:##. ##:::
//    ::: ##::::##:::: ##'##::: ##:##:::: ##:##:. ##::
//    ::: ##::::########:. ######::########::##::. ##:
//    :::..::::........:::......::........::..::::..::
//
//  Created by 亿刀 pushsdk_version 1.1  iTeam on 13-3-1.
//  Copyright (c) 2013年 亿刀  iTeam. All rights reserved.
//
/*! 可能出现的错误
 *  如果请求出错都可以从model的error属性获取描述
 */
#ifndef PushCenterDemo_TBSDKPushCenterError_h
#define PushCenterDemo_TBSDKPushCenterError_h

#import "PushCenterDefine.h"


/*************************************错误码***********************************************************/
//本地错误
#define LOCAL_ERROR_PARAMETER_INCORRECT         @"LOCAL_ERROR_PARAMETER_INCORRECT"      //参数不合法或参数不能为空
#define LOCAL_ERROR_PUSH_TOKEN_NOT_NULL         @"LOCAL_ERROR_PUSH_TOKEN_NOT_NULL"      //上传的deviceToken 不能为空
#define TBSDKPUSHCENTER_REQUEST_NOT_NETWORK     TBSDK_REQUEST_NOT_NETWORK               //无网络
#define TBSDKPUSHCENTER_REQUEST_TIME_OUT        TBSDK_REQUEST_TIME_OUT                  //请求超时
#define TBSDKPUSHCENTER_SESSION_IS_NOT_NULL     @"SESSION_IS_NOT_NULL"                  //session不能为空    
#define LOCAL_ERROR_BUILD_ACCS_MESSAGE_FAIL     @"LOCAL_ERROR_BUILD_ACCS_MESSAGE_FAIL"  //构建ACCS MESSAGE失败
#define ACCS_MESSAGE_SEND_FAIL                  @"ACCS_MESSAGE_SEND_FAIL"               //ACCS MESSAGE 发送失败
#define ACCS_RESPONSE_EMPTY                     @"ACCS_RESPONSE_EMPTY"                  //ACCS RESPONSE 为空
#define ACCS_RESPONSE_INVALID                   @"ACCS_RESPONSE_INVALID"                //ACCS RESPONSE 不合法

//服务器返回错误码
#define ER_SYS                                  @"ER_SYS"                               //::系统错误
#define ER_PARAM_INVALID                        @"ER_SYS"                               //::无效的参数
#define ER_PARAM_DEVICE_GLOBAL_ID               @"ER_PARAM_DEVICE_GLOBAL_ID"            //::全局设备号格式错误
#define ER_BIZ_APP_VER_INVALID                  @"ER_BIZ_APP_VER_INVALID"               //::无效app版本
#define ER_PARAM_APP_KEY                        @"ER_PARAM_APP_KEY"                     //::appKey格式错误
#define ER_BIZ_NEW_DEVICE_ID_FAIL               @"ER_BIZ_NEW_DEVICE_ID_FAIL"            //::生成DeviceId失败
#define ER_BIZ_REGISTER_FAIL                    @"ER_BIZ_REGISTER_FAIL"                 //::注册失败
#define ER_PARAM_TTID                           @"ER_PARAM_TTID"                        //::ttid格式错误
#define ER_DEVICE_APP_NOT_MATCH                 @"ER_DEVICE_APP_NOT_MATCH"              //::device信息和appkey不匹配
#define ER_PARAM_DEVICE_ID                      @"ER_PARAM_DEVICE_ID"                   //::设备号格式错误
#define ER_DEVICE_NOT_FOUND                     @"ER_DEVICE_NOT_FOUND"                  //::没有找到设备信息
#define ER_PUSHKEY_INVALID                      @"ER_PUSHKEY_INVALID"                   //::无效的pushKey
#define ER_BIZ_BIND_USER_WITHOUT_USERINFO       @"ER_BIZ_BIND_USER_WITHOUT_USERINFO"    //::绑定用户失败，未找到用户信息
#define ER_BIZ_BIND_USER_FAIL_NOT_REGISTER      @"ER_BIZ_BIND_USER_FAIL_NOT_REGISTER"   //::绑定用户失败，未注册
#define ER_BIZ_UPDATE_USER_INFO_FAIL            @"ER_BIZ_UPDATE_USER_INFO_FAIL"         //::更新用户信息失败
#define ER_USER_PUSHTOKEN_INVALID               @"ER_USER_PUSHTOKEN_INVALID"            //::无效的用户签名

#define ER_PARAM_USER_INFO                      @"ER_PARAM_USER_INFO"                   //::userinfo格式错误
#define ER_PARAM_INDEX                          @"ER_PARAM_INDEX"                       //::index错误
#define ER_PARAM_MSG_TYPE                       @"ER_PARAM_MSG_TYPE"                    //::消息类型格式错误
#define ER_PARAM_NUM                            @"ER_PARAM_NUM"                         //::超过数量的最大值
#define ER_PARAM_MESSAGE_IDS                    @"ER_PARAM_MESSAGE_IDS"                 //::消息id格式错误或数量超过最大限制
#define ER_PARAM_DEVICE_TOKEN                   @"ER_PARAM_DEVICE_TOKEN"                //::deviceToken格式错误
#define ER_BIZ_APPLETOKEN_FAIL                  @"ER_BIZ_APPLETOKEN_FAIL"               //::插入错误
#define ER_BIZ_SUBSCRIBE_NOT_EXIST              @"ER_BIZ_SUBSCRIBE_NOT_EXIST"           //::订阅信息不存在
#define ER_PARAM_STATUS                         @"ER_PARAM_STATUS"                      //::status格式错误
#define ER_DEVICE_DEV_ID_NOT_MATCH              @"ER_DEVICE_DEV_ID_NOT_MATCH"           //devicesId与device信息中的不匹配

//mtop.push.subscribe.update返回的子错误
#define ER_BIZ_SUBSCRIBE_FAIL                   @"ER_BIZ_SUBSCRIBE_FAIL"                //表示失败，
#define ER_BIZ_SUBSCRIBE_NOT_EXIST              @"ER_BIZ_SUBSCRIBE_NOT_EXIST"           //表示不存在，
#define ER_BIZ_SUBSCRIBE_ILLEGAL_DEVICE_MSG     @"ER_BIZ_SUBSCRIBE_ILLEGAL_DEVICE_MSG"  //表示“不是设备消息”，
#define ER_BIZ_SUBSCRIBE_UNKNOWN                @"ER_BIZ_SUBSCRIBE_UNKNOWN"             //表示未知，
#define ER_DEVICE_NOT_REGISTER                  @"ER_DEVICE_NOT_REGISTER"


#endif

