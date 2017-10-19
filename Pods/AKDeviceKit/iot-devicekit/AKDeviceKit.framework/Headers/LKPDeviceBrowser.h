//
//  AKNetBrowser.h
//  Pods
//
//  Created by 张光宇 on 12/10/15.
//
//

#import <UIKit/UIKit.h>
#import "LKUtilsDefine.h"
#import <TBJSONModel/TBJSONModel.h>


@class LKCandDeviceModel;
//@class AKDeviceModelInfo;
//@class LKPDeviceBrowseItem;
//@class AKProvisionResult;

/*
@protocol AKPLocalDeviceProvider <NSObject>

//! 在开始加载前准备注册 controller 和 tableView，用于导航和注册 tableview 注册 cell
- (void)prepareWithViewController:(UIViewController *)viewController tableView:(UITableView *)tableView;

//! 加载本地设备列表
- (void)loadDeviceWithCompletion:(void (^)(NSArray<LKPDeviceBrowseItem *> *list))completion;

//! 选中了一个设备
- (void)didSelectedDeviceItem:(LKPDeviceBrowseItem *)item;

@end
*/

@interface LKRouterInfo : TBJSONModel
@property(nonatomic,strong)NSString *brand;
@property(nonatomic,strong)NSString *devName;
@property(nonatomic,strong)NSString *macAddr;
@property(nonatomic,strong)NSString *manufacturer;
@property(nonatomic,strong)NSString *uuid;
@property(nonatomic,strong)NSString *sn;
@property(nonatomic, copy) NSString *model;
//brand = Tenda;
//devName = FH456;
//macAddr = "c8:3a:35:49:45:70";
//manufacturer = Tenda;

- (NSString *)composeModelName;
@end

@interface LKPDeviceBrowseItem : TBJSONModel

@property(nonatomic, strong) LKCandDeviceModel *deviceModel;	//产品model
@property(nonatomic, strong) NSString *mac;
@property(nonatomic, strong) NSString *model;					//设备model
@property(nonatomic, strong) NSString *sn;
@property(nonatomic, strong) NSString *serviceName;
@property(nonatomic, strong) NSString *version;
@property(nonatomic, strong) LKRouterInfo *routerInfo;
@property(nonatomic, assign) BOOL isAlreadyBinded;
@property(nonatomic, copy)   NSString *hostName;
@property(nonatomic, assign) BOOL blocked;                    //白名单选项
@property(nonatomic,assign)BOOL isTemplateModel;//是否为公版
@property(nonatomic, strong) NSString * tmplateModel;					//设备model
@property (nonatomic, copy) NSString    *reuseCellIdentifier;
//@property (nonatomic, weak) id<AKPLocalDeviceProvider>  provider;

+ (instancetype)buildFromTextData:(NSData *)data service:(NSNetService *)service;
+ (instancetype)buildFromRouterInfo:(LKRouterInfo *)router;
+ (instancetype)deepCopy:(LKPDeviceBrowseItem *)item;

//- (AKProvisionResult *)buildProvisionResult;//delete by difeng
- (BOOL)isVersionGreaterOrEqual1_1;

@end

extern NSString * const LKPDeviceInfoErrorDomain;

typedef NS_ENUM(NSInteger, AKPDeviceInfoErrorCode) {
	AKPDeviceInfoErrorFatal = 1,
	AKPDeviceInfoErrorTimeoutFindDevice,	//超时未查到设备
};

/**
 1. 本地发现设备：发广播路由器发现，mdns本地发现
 2. 重复设备去重
 */
@interface LKPDeviceBrowser : NSObject

+ (instancetype)sharedBrowser;

//! 搜索所有alink设备（支持mdns的设备和路由器设备）
- (void)startDiscoverWithBlock:(AKArrayResultBlock)didFoundBlock;
//! 停止搜索
- (void)stopDiscover:(AKBooleanResultBlock)completionHandler;

#pragma mark - utils

//! 获取当前连接的阿里智能路由器信息
- (LKRouterInfo *)connectedAlinkRouter;

//! 获取已发现的设备列表
- (NSArray<LKPDeviceBrowseItem *> *)discoveredItems;

//! 匹配指定model指定mac地址的设备
- (LKPDeviceBrowseItem *)matchedItemWithModelInfo:(NSString *)modelInfo
                                    templateModel:(NSString*)templateModel andMacAddress:(NSString *)mac;

//! 在超时时间范围内搜索指定model指定mac地址的设备
- (void)startDiscoverWithModelInfo:(NSString *)modelInfo
                       templateModel:(NSString*)templateModel
						macAddress:(NSString *)mac
						   timeout:(NSTimeInterval)ti
				   completionBlock:(AKObjectResultBlock)resultBlock;

////TODO
/**
//! 注册本地设备提供者，用于自定义设备插入到添加设备界面
- (void)registerLocalDeviceProvider:(id<AKPLocalDeviceProvider>)provider;

- (void)prepareLocalDeviceProviderWithController:(UIViewController *)controller tableView:(UITableView *)tableView;
 */

@end
