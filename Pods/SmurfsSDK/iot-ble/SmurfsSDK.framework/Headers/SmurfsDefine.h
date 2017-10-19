//
//  ABTDefine.h
//  AlinkBluetooth
//
//  Created by 刘彦玮(玄彦)  on 16/5/4.
//  Copyright © 2016年 alibaba. All rights reserved.
//

#ifndef ABTDefine_h
#define ABTDefine_h

//ABT log
#define ABTLog(fmt, ...) if(ABT_IS_SHOW_LOG) { NSLog(fmt,##__VA_ARGS__); }
//ABT if show log 是否打印日志，默认打印
#define ABT_IS_SHOW_LOG 1


//蓝牙系统通知
//centralManager status did change notification
#define ABTNotificationAtCentralManagerDidUpdateState @"ABTNotificationAtCentralManagerDidUpdateState"
//did discover peripheral notification
#define ABTNotificationAtDidDiscoverPeripheral @"ABTNotificationAtDidDiscoverPeripheral"
//did connection peripheral notification
#define ABTNotificationAtDidConnectPeripheral @"ABTNotificationAtDidConnectPeripheral"
//did filed connect peripheral notification
#define ABTNotificationAtDidFailToConnectPeripheral @"ABTNotificationAtDidFailToConnectPeripheral"
//did disconnect peripheral notification
#define ABTNotificationAtDidDisconnectPeripheral @"ABTNotificationAtDidDisconnectPeripheral"
//did discover service notification
#define ABTNotificationAtDidDiscoverServices @"ABTNotificationAtDidDiscoverServices"
//did discover characteristics notification
#define ABTNotificationAtDidDiscoverCharacteristicsForService @"ABTNotificationAtDidDiscoverCharacteristicsForService"
//did read or notify characteristic when received value  notification
#define ABTNotificationAtDidUpdateValueForCharacteristic @"ABTNotificationAtDidUpdateValueForCharacteristic"
//did write characteristic and response value notification
#define ABTNotificationAtDidWriteValueForCharacteristic @"ABTNotificationAtDidWriteValueForCharacteristic"
//did change characteristis notify status notification
#define ABTNotificationAtDidUpdateNotificationStateForCharacteristic @"ABTNotificationAtDidUpdateNotificationStateForCharacteristic"
//did read rssi and receiced value notification
#define ABTNotificationAtDidReadRSSI @"ABTNotificationAtDidReadRSSI"

//常量定义

#define ABTUserDefaultsKeyForPeripheralIdentifiers @"AlinkBLE.peripheralIdentifiers"

//蓝牙解析脚本名称
#define ABTBleDelegateScriptFileName @"ble-config.js"

//通知js的event类型
#define ABTJSNotifyEventOfPowerOff @"powerOff"
#define ABTJSNotifyEventOfPowerOn  @"powerOn"
#define ABTJSNotifyEventOfConnected @"connected"
#define ABTJSNotifyEventOfDisconnect @"disconnect"
#define ABTJSNotifyEventOfDiscover @"discover"
#define ABTJSNotifyEventOfDidWrite @"didWrite"
#define ABTJSNotifyEventOfNotifyStatus @"notifyStatus"

#define ABTJSNotifyDelegateOfOnReady @"onReady"
#define ABTJSNotifyDelegateOfOnLog @"onLog"
#define ABTJSNotifyDelegateOnReceived @"onReceived"


#endif /* ABTDefine_h */
