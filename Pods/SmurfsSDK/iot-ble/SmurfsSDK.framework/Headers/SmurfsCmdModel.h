//
//  CmdModel.h
//  Pods
//
//  Created by xuanyan.lyw on 16/6/30.
//
//

#import <Foundation/Foundation.h>

/**
 命令数据模型类
 */
@interface SmurfsCmdModel : NSObject

@property(nonatomic ,copy)NSDictionary *dict;
@property(nonatomic ,readonly, copy)NSString *mac;

@property(nonatomic ,readonly, copy)NSString *model;
@property(nonatomic ,readonly, copy)NSString *script;
@property(nonatomic, readonly, copy) NSString *scriptUrl;
@property(nonatomic ,readonly, copy)NSString *method;
@property(nonatomic ,readonly, copy)NSString *uuid;
@property(nonatomic ,readonly, copy)NSString *data;
@property(nonatomic ,readonly, copy)NSString *version;
@property(nonatomic ,readonly, copy)NSString *json;


/**
 从字典生成命令对象

 @param dict 字典参数
 @return 对象实例
 */
+ (SmurfsCmdModel *)makeFromDict:(NSDictionary *)dict;


/**
 从方法名生成命令对象

 @param method 方法名
 @return 对象实例
 */
+ (SmurfsCmdModel *)makeFromMothed:(NSString *)method;
@end
