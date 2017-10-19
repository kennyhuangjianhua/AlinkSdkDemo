//
//  ABTScriptHandler
//  AlinkBluetooth
//
//  Created by 刘彦玮(玄彦)  on 16/5/5.
//  Copyright © 2016年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>
#import "SmurfsOperateScene.h"

/**
 Js脚本引擎
 */
@interface SmurfsRuntime : NSObject {
    
}

@property(nonatomic ,strong) JSContext *context;


@property(nonatomic ,strong) JSValue *ble;
@property(nonatomic ,weak) SmurfsOperateScene *scene;

@property(nonatomic ,copy) NSString *script;


/**
 初始化

 @param script 脚本描述
 @param scene 脚本使用的场景
 @return 对象实例
 */
- (instancetype)initWithScript:(NSString *)script scene:(SmurfsOperateScene *)scene;

/**
 是否存在指定方法

 @param method 方法名
 @return 返回值
 */
- (BOOL)hasMethod:(NSString *)method;


/**
 执行方法

 @param method 方法名
 */
- (void)executeMethod:(NSString *)method;


/**
 配置相关环境
 */
- (void)setup;

@end
