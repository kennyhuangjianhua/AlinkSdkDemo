//
//  AKPWifiConfigureService.h
//  Alink Device Kit
//
//  Created by 文季 on 2015/9/21.
//  Copyright (c) 2015年 Alibaba. All rights reserved.
//


#import <Foundation/Foundation.h>

/**
 * 配网错误Domian
 */
extern NSString *const AKPWifiConfigureErrorDomain;

/**
 * 配网错误类型枚举值
 */
typedef NS_ENUM(NSInteger, AKPWifiConfigureError) {
    
    AKPWifiConfigurNoError = 0,             ///< 没有错误，不会有该值
    AKPWifiConfigurFatalError,              ///< 内部错误
    AKPWifiConfigurBadParameterError,       ///< 输入参数错误
    AKPWifiConfigurSocketError,             ///< Socket错误
    AKPWifiConfigureDeviceResponseError,    ///< 设备响应错误
};

/**
 * 配网类型
 */
extern NSString *const AKPWifiConfigureTypeSmartConfigV1;    ///< 一键配网v1
extern NSString *const AKPWifiConfigureTypeSmartConfigV2;    ///< 一键配网v2
extern NSString *const AKPWifiConfigureTypeSoftAP;           ///< SoftAP配网

/**
 * 当前配网进度
 */
typedef NS_ENUM(int, AKPWifiConfigureProgress) {
	
    AKPWifiConfigureProgressShouldConnectToAP = 5,          ///< SoftAP配网，APP需要连接到设备热点
    AKPWifiConfigureProgressDidConnectToAP = 10,            ///< SoftAP配网，APP已经连接到设备热点
    AKPWifiConfigureProgressIsSendingData = 15,             ///< APP正在发送联网信息
    AKPWifiConfigureProgressDidSendDataToAP = 20,           ///< SoftAP配网，设备热点已经收到联网信息
    AKPWifiConfigureProgressShouldSwitchBackToRouter = 30,  ///< SoftAP配网，APP需要切换网络回到家庭路由器
    AKPWifiConfigureProgressDidSwitchBackToRouter = 40,     ///< SoftAP配网，APP已经切换网络回到家庭路由器
    AKPWifiConfigureProgressDidFindDevice = 50,             ///< APP已经发现设备
    AKPWifiConfigureProgressDidGetUuid = 100,               ///< APP已经获取到设备uuid，可以开始绑定
    AKPWifiConfigureProgressDidGetMacOrSn = 100,            ///< APP已经获取到设备mac或sn，可以开始绑定
};

/**
 * 设备配网参数
 */
@interface AKPWifiConfigureParams : NSObject

/**
 * 设备配网类型，通过AKPWifiConfigureTypeXXX定义，如，AKPWifiConfigureTypeSmartConfigV2
 */
@property (nonatomic, copy) NSString *configureType;

/**
 * 家庭路由器ssid信息，通过[AKPWifiConfigureService ssidForConnectedNetwork]获取
 */
@property (nonatomic, copy) NSString *ssid;

/**
 * 家庭路由器密码
 */
@property (nonatomic, copy) NSString *password;

/**
 * 可选参数
 * 发现设备支持的最低协议版本号，默认最小支持版本为1.5
 */
@property (nonatomic, copy) NSString *opt_minimumDiscoverVersion;

/**
 * 可选参数
 * 设备model，1.6及以后版本需要校验发现的model和配置指定的model一致性
 */
@property (nonatomic, copy) NSString *opt_model;

/**
 * 可选参数
 * softAP专用，指定阿里服务端指定的设备热点前缀，默认前缀：alink_
 * 非softAp配网或使用默认前缀，该参数可置为nil
 */
@property (nonatomic, copy) NSString *opt_softApPrefix;

/**
 * 可选参数
 * 家庭路由器bssid信息
 */
@property (nonatomic, copy) NSString * bssid;
@end

/**
 * Wi-Fi配网服务
 */
@interface AKPWifiConfigureService : NSObject

/**
 * 单例
 */
+ (instancetype)sharedInstance;

/**
 * 开始配网，发配网包（ssid+密码），设备连接路由器，发现设备，设备连接Alink云并获取设备uuid，APP得到uuid设备配网完成。
 *
 * @param params		设备配网参数
 * @param progressHandler	当前配网进度回调，会被多次调用，该回调带2个参数：
 *	progress		配网进度信息0-100
 *	progressInfo	进度描述信息
 * @param completionHandler	配网完成回调，该回调带3个参数：
 *	 success	成功返回YES，
 *	 deviceInfo	失败为nil，成功，字典为：
 *				{	"state"		: "GOT_UUID",
 *					"uuid"		: "xxxxxxxxxxx",
 *					"model"		: "xxxxxx"
 *				}
 *				或
 *				{	"state"		: "GOT_MAC_SN",
 *					"mac"		: "aa:bb:cc:dd:ee:ff",
 *					"model"		: "xxx",
 *					"sn"		: "xxxxxxxxxxxxxxxx"
 *				}
 *				或
 *				{	
 *					"state"		: "GOT_MAC_SN",
 *					"version"	: "1.1"
 *					"macAddr"	: "aa:bb:cc:dd:ee:ff",
 *					"model"		: "xxx",
 *				}
 *				或
 *				{	
 *					"state"		: "GOT_MAC_SN",
 *					"version"	: "1.5"
 *					"key"		: "bIjq3G1NcgjSfF9uSeK2",
 *					"mac"		: "18:fe:34:a2:c7:3f",
 *					"sn"		: "empty_sn",
 *					"model"		: "ALINKTEST_LIVING_LIGHT_SMARTLED_LUA",
 *					"rand"		: "400049ac",
 *					"sign"		: "f2cba8722755e73c02d1d508d6d66dfa",
 *				}
 *	 error		成功为nil，错误则携带具体错误信息
 */
- (void)startConfigure:(AKPWifiConfigureParams *)params
       progressHandler:(void (^)(int progress, NSString *progressInfo))progressHandler
     completionHandler:(void (^)(BOOL success, NSDictionary *deviceInfo, NSError *error))completionHandler;


/**
 * 停止配网
 */
- (void)stopConfigure;

@end

@interface AKPWifiConfigureService (Utils)

/**
 * 获取手机当前连接网络的ssid
 *
 * @return 当前ssid，如果当前不是wifi网络则返回空串。
 */
+ (NSString *)ssidForConnectedNetwork;

/**
 * 提供一个单独的当前连接的Wi-Fi热点检测接口
 *
 * 什么时候需要用到这个接口？对于softAP配网模式，当需要引导用户先连接热点再输入ssid和密码时候，就
 * 需要检测手机是否连接到指定的Wi-Fi热点，这里提供一个单独的当前连接热点检测接口。
 *
 * **NOTE:** 
 * 当调用该接口后，会开个timer来监听当前连接的热点，请确保在不需要的时候结束监听。
 * 该接口会检测以`ssidPrefix`开头的ssid，比如`ssidPrefix`为"alink"，如果当前连接
 * 的wifi热点是"alinkXXX"则会被检测到。
 *
 * - 在检测到已连接到指定的热点后会通过`completionHandler`来回调，并结束监听。
 * - 如果用户提前退出，没有进行后续的`startConfigure:progressHandler:completionHandler:`需
 *	 调用`stopConfigure`来结束监听。
 *
 * @param ssidPrefix 设备热点ssid前缀
 * @param completionHandler 异步回调接口，如果APP已经连接到特定AP，该回调触发，success参数目前只返回YES
 */
- (void)connectToSoftAP:(NSString *)ssidPrefix completionHandler:(void (^)(BOOL success))completionHandler;

@end
