//
//  NetworkDemote.h
//  TBSDKNetworkSDK
//
//  Created by Roger.Mu on 8/1/14.
//  Copyright (c) 2014 taobao.com. All rights reserved.
//
// 开发开关,主要是方便抓包使用

#import <Foundation/Foundation.h>

@interface NetworkDemote : NSObject

@property (nonatomic) int spdyLinkHoldTimeRate;
@property (nonatomic) int spdyCreateConnectionTimeout;

+ (NetworkDemote *)shareInstance;

/* 是否已经降级了SPDY */
- (BOOL)isDemoteSPDY;

/* 不降级SPDY，默认 */
- (void)unDemoteSPDY;

/* 降级SPDY,功能一旦开启，那么所有的请求都会以HTTP短连接方式发起! */
- (void)networkDemoteSPDY;

/* 是否禁用了HTTPDNS功能,host传nil即可 */
- (BOOL)isDNSDemote:(NSString *)host;

/* 禁用HTTPDNS */
- (void)dnsDemote;

/* 不禁用HTTPDNS */
- (void)unDNSDemote;

/* 是否禁用了HTTPS功能 */
- (BOOL)isHTTPSDemote;

/* 禁用HTTPS */
- (void)httpsDemote;

/* 不禁用HTTPS */
- (void)unHTTPSDemote;

// -----------------------------------------------------------------------------
// *****已经废弃不用的接口*****

//所有请求降级到http
- (void)demote2HTTP DEPRECATED_MSG_ATTRIBUTE("使用networkDemoteSPDY代替.");

//还原降级到http
- (void)unDemote2HTTP DEPRECATED_MSG_ATTRIBUTE("使用unDemoteSPDY代替.");

//是否降级到http
- (BOOL)isDemote2HTTP DEPRECATED_MSG_ATTRIBUTE("使用isDemoteSPDY代替.");

// 向老版本降级接口兼容，已经废弃不用的接口
- (void)alwaysSpdyDemote DEPRECATED_MSG_ATTRIBUTE("废弃的接口.");

// 向老版本降级接口兼容，已经废弃不用的接口
- (void)unAlwaysSpdyDemote DEPRECATED_MSG_ATTRIBUTE("废弃的接口.");

@end
