//
//  BoneRouter.h
//  Pods
//
//  Created by Hager Hu on 2/20/17.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#import "BoneRouterProtocol.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString * const BoneRouterPresentTypeKey;
extern NSString * const BoneRouterLoadingClassKey;
extern NSString * const BoneRouterCompletionHandlerKey;
extern NSString * const BoneRouterNavigationControllerKey;


typedef void(^BoneRouterCompletionHandler)(NSError * _Nullable error, NSDictionary *info);

@interface BoneRouter : NSObject

/**
 设备开放平台对应的boneKey; 必须设置，否则无法使用
 */
@property (nonatomic, strong) NSString *boneKey;

/**
 默认统一路由实例

 @return 默认的路由实例实现
 */
+ (instancetype)defaultRouter;


/**
 判断能否打开指定的url
 此处仅判断url符合开放平台规则和自定义路由能否打开

 @param url 要判断的url
 @return 能够打开返回YES，否则返回NO。
 */
- (BOOL)isValidURL:(NSURL *)url;

/**
 打开指定的url

 @param url 要打开的url
 */
- (void)open:(NSURL *)url completionHandler:(void (^)(BOOL success))completion;

/**
 打开指定的url
 
 @param url 要打开的url
 @param options 指定的参数
 */
- (void)open:(NSURL *)url options:(NSDictionary * _Nullable)options completionHandler:(void (^)(BOOL success))completion;

/**
 打开指定的url
 
 @param code 开放平台对应的code
 @param options 指定的参数
 */
- (void)openCode:(NSString *)code options:(NSDictionary * _Nullable)options completionHandler:(void (^)(BOOL success))completion;

/**
 获得指定url对应的视图控制器

 @param url 需要获取视图控制器的url
 @return 返回指定url对应的视图控制器实例，找不到时返回默认路由找不到视图控制器
 */
- (nonnull UIViewController *)controllerWithURL:(NSURL *)url;


/**
 设置默认导航控制器
 基于当前显示页面找不到导航控制器时使用

 @param controller 要设置的默认导航栏控制器实例
 @return 设置成功返回YES，否则返回NO。
 */
- (BOOL)setDefaultNavigationController:(UINavigationController *)controller;


/**
 注册自定义路由

 @param router 实现BoneRouter协议的自定义路由类
 @return 注册成功返回YES，否则返回NO。
 */
- (BOOL)registerSubRouter:(Class<BoneRouter>)router;


/**
 自定义加载页面显示

 @param router 实现BoneRouterLoading协议的自定义加载页面实现类
 @return 注册成功返回YES，否则返回NO。
 */
- (BOOL)registerLoadingHandler:(Class<BoneRouterLoading>)router;

/**
 注册自定义默认加载页面
 默认支持多个加载页面实现类，但只能有1个默认加载页面
 不调用此方法时，默认返回第一个注册的加载页面实现类；如果没有注册过，则使用统一路由内部默认加载页面
 
 @param handler 实现BoneRouterLoading协议的自定义默认加载页面实现类
 @return 注册成功返回YES，否则返回NO。
 */
- (BOOL)registerDefaultLoadingHandler:(Class<BoneRouterLoading>)handler;


@end

NS_ASSUME_NONNULL_END
