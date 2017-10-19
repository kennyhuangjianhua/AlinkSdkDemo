//
//  AKPHotspotService.h
//  Alink Device Kit
//
//  Created by 文季 on 2017/1/20.
//  Copyright © 2017年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AKAccessibleDeviceItem;

/**
 * 热点配网服务
 */
@interface AKPHotspotService : NSObject

/**
 是否支持起热点，检测是否为iPhone

 @return YES则支持起热点
 */
+ (BOOL)isSupportedHotspot;

/**
 发现（搜索）支持手机热点配网服务的设备列表，每隔2s发送一次发现请求，有新增会有多次回调

 @param completionHandler 回调（发现的设备列表）
 */
- (void)discoverDevices:(void (^)(NSArray<AKAccessibleDeviceItem *> *devices, NSError *error))completionHandler;

/**
 停止发现
 */
- (void)stopDiscover;

@end


