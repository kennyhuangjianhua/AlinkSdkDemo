//
//  AKAccessibleDeviceItem.h
//  Alink Device Kit
//
//  Created by 文季 on 2017/1/20.
//  Copyright © 2017年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TBJSONModel/TBJSONModel.h>

/**
 * 安全等级
 */
typedef NS_ENUM(NSInteger, AKAccessibleDeviceSecurityLevel) {
    AKAccessibleDeviceSecurityLevelPlain = 0,       ///< 未加密
    AKAccessibleDeviceSecurityLevelAES256CBC = 1,   ///< AES256CBC加密
    AKAccessibleDeviceSecurityLevelAES128CBC = 2,   ///< AES128CBC加密
};

/**
 * 可访问的设备节点
 */
@interface AKAccessibleDeviceItem : TBJSONModel

@property (nonatomic, copy) NSString *model;    ///< 设备model
@property (nonatomic, copy) NSString *sn;       ///< 设备唯一标示

@property (nonatomic, copy) NSString *host;     ///< host
@property (nonatomic, copy) NSString *port;     ///< 端口

@property (nonatomic, copy) NSString *security; ///< 支持的安全等级

@end
