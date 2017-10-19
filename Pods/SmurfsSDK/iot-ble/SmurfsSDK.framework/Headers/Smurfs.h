//
//  AlinkBLE.h
//  AlinkBLEProject
//
//  Created by 刘彦玮(玄彦)  on 16/5/9.
//  Copyright © 2016年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SmurfsOperateScene.h"
#import "SmurfsPairScene.h"

/**
 工具类，用于创建基本情景
 */
@interface Smurfs : NSObject


#pragma mark - native api


/**
 本地缓存的场景对象
 */
@property(nonatomic ,strong) NSMutableArray *operateScenes;

/**
 预加载可以提前初始化CBCentralManager，使蓝牙执行速度更快
 */
+(void)preload;

/**
 创建蓝牙入网场景，实现扫描匹配蓝牙设备功能

 @param block 回调
 @return 场景对象
 */
+ (SmurfsPairScene *)createPairSceneWithBlock:(void (^)(CBPeripheral *peripheral,NSDictionary *advertisementData, NSNumber *RSSI,NSString *localName, BOOL isAlinkAdvertisement,NSString *mac,NSString *version))block;


/**
 创建蓝牙操作场景，实现蓝牙的基本通信功能

 @param model 设备model值
 @param mac 设备蓝牙mac地址
 @param script 自动化脚本
 @return 场景对象
 */
+ (SmurfsOperateScene *)createOperateScene:(NSString *)model mac:(NSString *)mac script:(NSString *)script;
@end
