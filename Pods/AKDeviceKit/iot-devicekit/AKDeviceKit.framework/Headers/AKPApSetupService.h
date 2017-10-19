//
//  AKPApSetupService.h
//  Alink Device Kit
//
//  Created by 文季 on 2017/1/22.
//  Copyright © 2017年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AKAccessibleDeviceItem;
@class AKPAccessPoint;

/**
 * 设备切换Ap服务
 */
@interface AKPApSetupService : NSObject

/**
 根据对端 ip 和 port 进行连接

 @param device 可访问设备节点
 @return 设备切换Ap服务
 */
+ (instancetype)setupServiceForDevice:(AKAccessibleDeviceItem *)device;


/**
 拿到当前正在使用的Service
 */
+ (instancetype)runningService;

/**
 发送单播 并 开启监听，搜索设备周边 Wi-Fi 列表，可能有多次回调

 @param completionHandler 回调（WiFi列表）
 */
- (void)searchWifiList:(void (^)(NSArray<AKPAccessPoint *> *wifiList, NSError *error))completionHandler;

/**
 停止搜索设备周边 Wi-Fi 列表
 */
- (void)stopSearchWifiList;

/**
 控制设备 切换热点

 @param apItem 待切换到的热点
 @param completionHandler 回调
 */
- (void)switchToAccessPoint:(AKPAccessPoint *)apItem completion:(void (^)(BOOL success, NSError *error))completionHandler;



/**
 控制设备 切换热点
 
 @param ssid 待切换到的热点
 @param pwd 待切换到的热点密码
 @param completionHandler 回调
 */
- (void)switchToAccessPoint:(NSString *)ssid password: (NSString *)pwd
                 completion:(void (^)(id result, NSError *error))completionHandler;


-(AKAccessibleDeviceItem *)getAccessibleDeviceItem;
@end

