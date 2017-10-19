//
//  AKPAccessPoint.h
//  Alink Device Kit
//
//  Created by 文季 on 2017/1/20.
//  Copyright © 2017年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TBJSONModel/TBJSONModel.h>

/**
 * 热点信息
 */
@interface AKPAccessPoint : TBJSONModel

@property (nonatomic, copy) NSString *ssid;         ///< 热点SSID
@property (nonatomic, copy) NSString *xssid;        ///< 非UTF-8编码的SSID，通过`ssid`字段获取转译成UTF-8编码后的ssid
@property (nonatomic, copy) NSString *password;     ///< 热点密码
@property (nonatomic, copy) NSString *rssi;         ///< 范围 [-100, 0], 数值越大，信号越强
@property (nonatomic, copy) NSString *auth;         ///< 热点加密方式，0为Open，其他为加密

@property (nonatomic, copy) NSString *encrypted;    ///< 安全等级

@end
