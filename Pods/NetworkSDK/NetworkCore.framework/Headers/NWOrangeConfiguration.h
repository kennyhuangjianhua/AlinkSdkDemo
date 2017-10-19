//
//  NWOrangeConfiguration.h
//  ALINetworkSDK
//
//  Created by wuchen.xj on 8/18/16.
//  Copyright © 2016 wuchen.xj. All rights reserved.
//

#import <Foundation/Foundation.h>

#define NW_ORANGE_KEY_BACKGOUND_DISCONNECT_INTERVAL     @"network_background_disconnect_interval"
#define NW_ORANGE_KEY_EMPTY_SCHEME_HTTPS_SWITCH         @"network_empty_scheme_https_switch"
#define NW_ORANGE_KEY_NETWORK_CACHE_ENABLED_SWITCH      @"network_cache_enabled_switch"
#define NW_ORANGE_KEY_NETWORK_FORCE_HTTPS_SWITCH        @"network_force_https_switch"
#define NW_ORANGE_KEY_NETWORK_HTTPS_PROXY_SWITCH        @"network_https_proxy_switch"
#define NW_ORANGE_KEY_NETWORK_USE_CFNETWORK_ECODES      @"network_use_cfnetwork_ecodes"
#define NW_ORANGE_KEY_NETWORK_CFNETWK_HTTP_SWITCH       @"network_cfnetwork_http_switch"
#define NW_ORANGE_KEY_NETWORK_CFNETWK_HTTP_BLACKLIST    @"network_cfnetwork_http_blacklist"
#define NW_ORANGE_KEY_NETWORK_OFF_SWITCH                @"network_off"

@interface NWOrangeConfiguration : NSObject

+ (NWOrangeConfiguration *)sharedInstance;

- (void)setDefaultValue:(NSString *)value forKey:(NSString *)key;

- (void)updateNotification:(NSNotification *)notification;

- (BOOL)isAutoCompleteSchemeHttps;

- (BOOL)isCacheEnabled;

- (BOOL)isNetworkOff;

- (BOOL)isForce2Https;

- (BOOL)isHttpsProxyEnabled;

- (BOOL)isCFNetworkHttpEnabled:(NSString *)host;

- (BOOL)isDispatch2CFNetworkWhenError:(NSError *)error;

- (NSInteger)backgroundDisconnectInterval;

@end
