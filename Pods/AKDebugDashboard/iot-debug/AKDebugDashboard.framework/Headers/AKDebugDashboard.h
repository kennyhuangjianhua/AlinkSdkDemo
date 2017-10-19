//
//  AKDebugDashboard.h
//  AlinkApp
//
//  Created by Wenji.lsl on 15/11/25.
//  Copyright © 2015年 Alink. All rights reserved.
//

#import <UIKit/UIKit.h>

/*
 - 单例
 - 控制面板永远前置
 - 顶部有logo按钮，点击最大化/最小化控制面板（最小化时只有logo按钮）
 - 可获取默认日志面板，并定制logFormatter/shortLogFormatter
	+ 默认日志面板（包含，搜索过滤，日志等级过滤，添加标记，清除日志）
 - 可在组件面板插入自定义面板
 - 当组件面板大于或等于2个时显示segmentedControl
 */
@protocol AKDebugDashboardDelegate;

@interface AKDebugDashboard : UIView

/*
 全屏或最小化显示
 */
@property (nonatomic, getter=isFullScreen) BOOL fullScreen;
@property (nonatomic, weak) id<AKDebugDashboardDelegate> delegate;

/*
 单例构建Debug控制板
 */
+ (instancetype)sharedDashboard;

/*
 segmentedControl类似于searchBar里面的scopeBar
 当组件面板大于或等于2个时会显示该segmentedControl
 */

/*
 范围条个数
 @return 当前范围条个数
 */
- (NSUInteger)numberOfSegments;

/*
 选择并显示对应的组件面板
 @param segment 范围条索引
 @return 被选择的面板
 */
- (UIView *)selectSegmentAtIndex:(NSUInteger)segment;
/*
 插入一个组件面板到控制板容器中
 @param title 范围条title
 @param view 自定义面板
 @param segment 范围条索引
 @return 无
 */
- (void)insertSegmentWithTitle:(NSString *)title view:(UIView *)view atIndex:(NSUInteger)segment;
/*
 移除控制板容器中的一个面板
 @param segment 范围条索引
 @return 无
 */
- (void)removeSegmentAtIndex:(NSUInteger)segment;

@end

/*
 控制板代理
 */
@protocol AKDebugDashboardDelegate <NSObject>

@optional

/*
 点击上传日志按钮
 @param dashboard 控制板
 @param messageArray 日志列表
 */
- (void)dashboard:(AKDebugDashboard *)dashboard onUploadLogClicked:(NSArray *)messageArray;

@end
