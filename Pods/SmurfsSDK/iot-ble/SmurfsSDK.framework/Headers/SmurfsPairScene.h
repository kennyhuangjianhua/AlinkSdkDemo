//
//  ABTPairOperator.h
//  AlinkBLEProject
//
//  Created by 刘彦玮(玄彦)  on 16/5/26.
//  Copyright © 2016年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef void (^ABTPairBlockOnDiscoverPeripheral)(CBPeripheral *peripheral,NSDictionary *advertisementData, NSNumber *RSSI,NSString *localName, BOOL isAlinkAdvertisement,NSString *mac,NSString *version);

/**
 蓝牙设备发现和匹配场景
 */
@interface SmurfsPairScene : NSObject

/**
 初始化

 @param block 回调
 @return 场景对象
 */
- (instancetype)initWithDiscoverPeripheralBlock:(ABTPairBlockOnDiscoverPeripheral)block;

/**
 进入设备发现和匹配场景
 */
- (void)enter;

/**
 退出设备发现和匹配场景
 */
- (void)exit;

@end
