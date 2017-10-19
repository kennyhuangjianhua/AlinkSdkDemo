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
//  -Copyright (c) 2013年 亿刀  iTeam. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TBSDKPushCenterError.h"
#import "TBSDKPushCenterModel.h"

/** PushCenter的基础服务类。提供了上传deviceToken、注册、绑定、解绑功能。
 *  封装的主要API：
 *  http://dev.wireless.taobao.net/mediawiki/index.php?title=Mtop.sys.newDeviceId
 *  http://dev.wireless.taobao.net/mediawiki/index.php?title=Mtop.push.device.register_v4
 *  http://dev.wireless.taobao.net/mediawiki/index.php?title=Mtop.push.device.synDeviceToken
 */
@interface TBSDKPushCenterEngine : NSObject

/** 以单例模式初始化 */
+ (id)shareInstance;

/** 上传deviceToken，当应用程序代理方法– application:didRegisterForRemoteNotificationsWithDeviceToken:获取deviceToken后，应调用此方法上传deviceToken。
 *
 *  @param  deviceToken     通过appDelegate代理方法获取的deviceToken
 *  @param  successBlock    deviceToken上传成功后，回调block
 *  @param  failBlock       deviceToken上传失败后，回调block，可以在model中查看error和服务器返回值responseString
 *  @param  userInfo        回调model携带的userInfo。用于回调传参和辨别是哪个请求的回调
 */
- (void)upLoaderDeviceToken:(NSData *)deviceToken
                   userInfo:(NSDictionary *)userInfo
         uploadSuccessBlock:(PushCenterModelSuccessBlock)successBlock
            uploadFailBlock:(PushCenterModelFailureBlock)failBlock;


/** 将登录用户和手机绑定在一起.
 *
 *  @param  userId          用户userId
 *  @param  successBlock    绑定成功后，回调block
 *  @param  failBlock       绑定失败后，回调block
 *  @param  userInfo        回调的时候，model携带的userInfo。用于回调传参和辨别是哪个请求的回调
 *
 *  @note   sessionID 和 sToken不能同时为空，如果sessionID 和 sToken同时不为空，以sessionID为准，sToken被忽略
 */
- (void)bindUserIntoPushCenterWithAlias:(NSString *)userId
                               userInfo:(NSDictionary *)userInfo
                       bindSuccessBlock:(PushCenterModelSuccessBlock)successBlock
                          bindFailBlock:(PushCenterModelFailureBlock)failBlock;


/** 将用户和手机解除绑定。
 *
 *  @param  pushUserToken   绑定成功后，pushUserToken会保存在 TBSDKPushCenterConfiguration 单例的pushUserToken属性中（实际是存储在NSUserDefaults中）。
 *  @param  userInfo        回调的时候，model携带的userInfo。用于回调传参和辨别是哪个请求的回调
 *  @param  successBlock    绑定成功后，回调block
 *  @param  failBlock       绑定失败后，回调block
 */
- (void)unbindUserIntoPushCenterWithPushUserInfo:(NSDictionary *)userInfo
                              unBindSuccessBlock:(PushCenterModelSuccessBlock)successBlock
                                 unBindFailBlock:(PushCenterModelFailureBlock)failBlock;


/**
 * 该接口已废弃，返回 nil.
 *
 * tag集合为标签集合，此接口为同步接口，即为全量更新
 */
- (TBSDKPushErrorResponse *)updateTag:(NSArray *)tag;


/** 获取Device ID
 * @return device id value
 */
- (NSString *)getDeviceID;

@end