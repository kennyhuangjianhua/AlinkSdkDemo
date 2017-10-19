//
//  AliLinkForNative.h
//  AlinkApp
//
//  Created by Wenji.lsl on 15/7/28.
//  Copyright (c) 2015年 Alink. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * 配网错误Domian
 */
extern NSString *const AliLinkForNativeErrorDomain;

/**
 * 配网错误类型枚举值
 */
typedef NS_ENUM(NSInteger, AliLinkForNativeError) {
	
	AliLinkForNativeNoError = 0,		///< 没有错误，不会有该值
	AliLinkForNativeFatalError,			///< 内部错误
	AliLinkForNativeBadParameterError,	///< 输入参数错误
	AliLinkForNativeSocketError,		///< Socket错误
	AliLinkForNativeDeviceResponseError,///< 设备响应错误
};

/**
 * 配网类型枚举值
 */
typedef NS_ENUM(NSUInteger, AliLinkType) {
	
	AliLinkBroadcast,	///< 广播配网
	AliLinkP2P,			///< P2P配网
	AliLinkAP,			///< SoftAP配网
	AliLinkRouter		///< 智能路由器配网
};

/**
 * 当前配网进度
 */
typedef NS_ENUM(int, AliLinkProgress) {
	
	AliLinkProgressShouldConnectToAP = 5,			///< SoftAP配网，APP需要连接到设备热点
	AliLinkProgressDidConnectToAP = 10,				///< SoftAP配网，APP已经连接到设备热点
	AliLinkProgressIsSendingData = 15,				///< APP正在发送联网信息
	AliLinkProgressDidSendDataToAP = 20,			///< SoftAP配网，设备热点已经收到联网信息
	AliLinkProgressShouldSwitchBackToRouter = 30,	///< SoftAP配网，APP需要切换网络回到家庭路由器
	AliLinkProgressDidSwitchBackToRouter = 40,		///< SoftAP配网，APP已经切换网络回到家庭路由器
	AliLinkProgressDidFindDevice = 50,				///< APP已经发现设备
	AliLinkProgressDidGetUuid = 100,				///< APP已经获取到设备uuid，可以开始绑定
	AliLinkProgressDidGetMacOrSn = 100,				///< APP已经获取到设备mac或sn，可以开始绑定
	AliLinkProgressDidFinishWithCustomDiscoverBlock = 100, ///< APP通过用户定义的设备发现回调，发现了设备
};

@class AlinkDeviceDiscover;

/**
 * 阿里自主配网，配网Native化适配类
 */
@interface AliLinkForNative : NSObject

/**
 * 单例
 */
+ (instancetype)shareInstance;

/**
 * 广播发现设备，支持的最低协议版本，默认是1.0版本
 */
@property (nonatomic, copy) NSString * minimumDiscoverVersion;

/**
 * 准备配网，发配网引导包，协助设备定信道
 * @param alinkType 设备配网类型
 */
- (void)prepareProvisionWithType:(AliLinkType)alinkType;

/**
 * 产品需求：SoftAP配网，需要先连接设备热点再开始发送联网信息
 * 如果用户提前退出，需调用stopProvision停止监测
 * @param ssidPrefix 设备热点ssid前缀
 * @param completionHandler 异步回调接口，如果APP已经连接到特定AP，该回调触发，success参数目前只返回YES
 */
- (void)connectToSoftAP:(NSString *)ssidPrefix completionHandler:(void (^)(BOOL success))completionHandler;

/**
 * 开始配网，发配网包（ssid+密码），设备连接路由器，发现设备，设备连接Alink云并获取设备uuid，APP得到uuid设备配网完成。
 *
 * Note: ssid+passwd总长度数不能超过55个字节
 *
 * @param ssidInfo 家庭路由器ssid信息，通过[AlinkNetworkProvision infoForConnectedNetwork]获取, 字典范例如下：
 *									{	@"ssid" : @"alibaba-inc",
 *										@"bssid" : @"xx:xx:xx:xx:xx",
 *										@"ssidData" : [NSData data],
 *										@"softApSsidPrefix" : @"alink_XXX" //softAP专用，服务端指定的设备热点前缀
 *									}
 * @param passwdStr 家庭路由器密码
 * @param model 设备model信息
 * @param alinkType 设备配网类型
 * @param progressHandler 当前配网进度回调，会被多次调用，该回调带2个参数：
 *	progress		配网进度信息0-100
 *	progressInfo	进度描述信息
 * @param completionHandler 配网完成回调，该回调带3个参数：
 *	 success	成功返回YES，
 *	 deviceInfo	失败为nil，成功，字典为{@"state":@"GOT_UUID", @"uuid":@"xxxxxxxxxxx", @"model":@"xxxxxx"}
 *				或{@"state" : @"GOT_MAC_SN", @"mac" : @"aa:bb:cc:dd:ee:ff", @"sn" : @"xxxxxxxxxxxxxxxx", @"model" : @"xxx"}
 *				或{@"state" : @"GOT_MAC_SN", @"macAddr" : @"aa:bb:cc:dd:ee:ff", @"model" : @"xxx", @"version" : @"1.1"}
 *	 error		成功为nil
 */
- (void)startProvision:(NSDictionary *)ssidInfo
				passwd:(NSString *)passwdStr
				 model:(NSString *)model
			 alinkType:(AliLinkType)alinkType
	   progressHandler:(void (^)(int progress, NSString *progressInfo))progressHandler
	 completionHandler:(void (^)(BOOL success, NSDictionary *deviceInfo, NSError *error))completionHandler;

/**
 * 停止配网
 */
- (void)stopProvision;

@end
