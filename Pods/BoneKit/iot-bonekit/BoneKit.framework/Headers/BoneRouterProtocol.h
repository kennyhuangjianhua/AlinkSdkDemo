//
//  BoneRouterProtocol.h
//  Pods
//
//  Created by Hager Hu on 2/20/17.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@protocol BoneRouter <NSObject>


+ (BOOL)canHandle:(NSURL *_Nonnull)url params:(NSDictionary *_Nullable)params;

/**
 返回指定URL和参数对应的视图控制器实例

 @param url 对应的url内容，不包含业务参数
 @param params 对应业务参数
 @return 返回对应的视图控制器实例，不应该返回nil
 */
+ (nonnull UIViewController *)controllerWithURL:(NSURL *_Nonnull)url params:(NSDictionary *_Nullable)params;

@end


@protocol BoneRouterLoading <NSObject>

/**
 返回指定URL和参数对应的加载页面对应的视图控制器实例

 @param url 当前正在路由查询的url
 @param params 当前正在路由查询的url对应的参数
 @return 返回对应的页面实现视图控制器实例，不应该返回nil
 */
+ (nonnull UIViewController *)controllerWithURL:(NSURL *_Nonnull)url params:(NSDictionary *_Nullable)params;

@end
