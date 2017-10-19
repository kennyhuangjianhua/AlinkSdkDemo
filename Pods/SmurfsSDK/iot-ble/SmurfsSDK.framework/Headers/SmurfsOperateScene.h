//
//  ABTOperator.h
//  AlinkBluetooth
//
//  Created by 刘彦玮(玄彦)  on 16/5/4.
//  Copyright © 2016年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SmurfsCmdModel.h"
#import <CoreBluetooth/CoreBluetooth.h>

/**
 蓝牙操作场景回调类
 */
@protocol SmurfsOperateSceneDelegate <NSObject>

@required

/**
 通知蓝牙准备完毕
 */
- (void)onReady;

/**
通知收到蓝牙设备上行数据

 @param uuid 蓝牙设备UUID
 @param data 上行数据
 */
- (void)onReceived:(CBUUID *)uuid data:(NSData *)data;

/**
 通知蓝牙设备事件变化

 @param event 事件类型：connected disconnect failToConnect didWrite notifyStatus(1是订阅，0是取消订阅) powerOn, powerOff
 @param uuid 蓝牙设备UUID
 @param data 通知数据
 */
- (void)onMessage:(NSString *)event uuid:(CBUUID *)uuid data:(NSString *)data;
@optional


/**
 通知Js日志

 @param msg 消息数据
 */
- (void)notifyJsLog:(NSString *)msg;
@end

/**
 蓝牙基本操作场景
 */
@interface SmurfsOperateScene : NSObject {
    
}

@property(nonatomic, copy, readonly) NSString *model;
@property(nonatomic, copy, readonly) NSString *mac;


@property(nonatomic, assign, readonly) BOOL isConnected;
@property BOOL isReady;

@property(nonatomic, copy) NSString *localname;

@property(nonatomic, strong) CBPeripheral *peripheral;
@property(nonatomic, weak) id<SmurfsOperateSceneDelegate> delegate;


/**
 初始化

 @param model 蓝牙设备model
 @param mac 蓝牙设备mac地址
 @param script 脚本
 @return 对象实例
 */
- (instancetype)initWithModel:(NSString *)model mac:(NSString *)mac script:(NSString *)script;

/**
 进入蓝牙基本操作场景
 */
- (void)enter;

/**
 退出蓝牙基本操作场景
 */
- (void)exit;

/**
 打开通知

 @param uuid characteristic uuid
 */
- (void)openNotify:(NSString *)uuid;

/**
 关闭通知

 @param uuid characteristic uuid
 */
- (void)closeNotify:(NSString *)uuid;


/**
 读取指定characteristic数据

 @param uuid characteristic uuid
 */
- (void)read:(NSString *)uuid;


/**
 向指定characteristic写数据，使用WriteWithResponse模式

 @param uuid characteristic uuid
 @param data 数据
 */
- (void)write:(NSString *)uuid value:(NSData *)data;

/**
 向指定characteristic写数据，使用WriteWithoutResponse模式

 @param uuid characteristic uuid
 @param data 数据
 */
- (void)pass:(NSString *)uuid value:(NSData *)data;

/**
 命令处理

 @param cmdModel 命令相关信息
 */
- (void)cmdProcess:(SmurfsCmdModel *)cmdModel;
@end
