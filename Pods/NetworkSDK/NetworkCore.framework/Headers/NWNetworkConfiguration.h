//
//  NWNetworkConfiguration.h
//  ALINetworkSDK
//
//  Created by Roger.Mu on 1/19/15.
//  Copyright (c) 2015 Taobao.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NWNetworkTraceAnalysis.h"
#import "NWUserPolicy.h"
#import "NWUserTrace.h"
#import "NWUserLoger.h"

typedef enum {
    release = 0,    //线上环境
    releaseDebug,   //预发环境
    daily           //日常环境
} NetworkEnv;

#define NETWORK_PROTOCOL_SKIP @"network_skip"
#define NETWORK_PROTOCOL_CONNECTION_REGISTER @"connection_register"


@interface NWNetworkConfiguration : NSObject

#pragma mark -- initial properties

@property (nonatomic, nullable, weak)     id<NWUserTraceDelegate>     utDelegate;         // 自定义 UT
@property (nonatomic, nullable, weak)     id<NWUserLogDelegate>       logDelegate;        // 自定义 LOG
@property (nonatomic, nullable, weak)     id<NWPolicyDelegate>        policyDelegate;     // 自定义 策略
@property (nonatomic, nullable, weak)     id<NWRequestCostProtocol>   traceProtocol;      // 记录请求和结束的轨迹
@property (nonatomic, nullable, weak)     id<NWRequestFlowProtocol>   flowProtocol;       // 记录请求流量


@property (nonatomic, nullable, strong)             NSString          *appkey;
@property (nonatomic, nullable, strong)             NSString          *appSecret;         // 如果使用安全保镖，该参数不用填写
@property (nonatomic, nullable, strong)             NSString          *authCode;          // 安全保镖SDK的授权码，不传或为空串，使用默认加密文件
@property (nonatomic, nullable, strong)             NSString          *clusterPublickey;  // ASERVER 集群预置公钥: ACS, AE, OPEN
@property (nonatomic, nullable, strong, readonly)   NSString          *utdid;
@property (nonatomic, nullable, strong, readonly)   NSString          *uid;
@property (nonatomic, assign)                       NetworkEnv        netEnvironment;     // 设置网络环境: release, releaseDebug, daily
@property (nonatomic, assign)                       BOOL              isUseSecurityGuard; // 是否使用安全保镖，默认为YES



+ (nullable NWNetworkConfiguration *)shareInstance;

/**
 * 设置网络环境。
 * @param env: release, releaseDebug, daily
 */
+ (void)setEnvironment:(NetworkEnv)env;


/**
 * 定制Aserver中心域名
 * @param releaseHost  线上域名
 * @param debugHost    预发域名
 * @param dailyHost    日常域名
 */
+ (void)setAcsCenterHosts:(nullable NSString *)releaseHost debugHost:(nullable NSString *)debugHost dailyHost:(nullable NSString *)dailyHost;



/**
 * 定制预置IP
 * @param releaseIps 线上预置IP列表
 * @param debugIps   预发预置IP列表
 * @param dailyIps   日常预置IP列表
 */
+ (void)setAcsCenterIPs:(nullable NSArray *)releaseIps debugIps:(nullable NSArray *)debugIps dailyIps:(nullable NSArray *)dailyIps;



/**
 * 定制AMDC域名
 * @param releaseHost  线上域名
 * @param debugHost    预发域名
 * @param dailyHost    日常域名
 */
+ (void)setAmdcHosts:(nullable NSString *)releaseHost debugHost:(nullable NSString *)debugHost dailyHost:(nullable NSString *)dailyHost;



/**
 * 定制AMDC预置IP
 * @param releaseIps 线上预置IP列表
 * @param debugIps   预发预置IP列表
 * @param dailyIps   日常预置IP列表
 */
+ (void)setAmdcIPs:(nullable NSArray *)releaseIps debugIps:(nullable NSArray *)debugIps dailyIps:(nullable NSArray *)dailyIps;



/**
 * 定制预建连接
 * @param hosts      需要预建连接的域名
 */
+ (void)setPrebuiltConnections:(nullable NSArray *)hosts;



/**
 * 设置内置热域名。
 * 默认情况下，内置的是手机淘宝的热域名，如果应用需要定义自己的热域名，可调用该方法进行覆盖。
 *
 * @param domains: 域名列表, 元素类型为NSString
 */
+ (void)setHotDomains:(nullable NSArray *)domains;


/**
 * 获取当前的设备的 utdid
 */
- (nullable NSString *)getAuthUtdid;


/**
 * 设置userid
 */
- (void)setuid:(nullable NSString *) uid;


@end