//
//  AKPDeviceAuthModels.h
//  Pods
//
//  Created by Wenji.lsl on 16/1/13.
//
//

#import <TBJSONModel/TBJSONModel.h>

extern NSString * __nonnull const AKPAuthServiceErrorDomain;

typedef NS_ENUM(NSInteger, AKPAuthServiceErrorCode) {
	AKPAuthServiceErrorFatal = 1,
	AKPAuthServiceErrorBadParameters,				//输入参数错误
	AKPAuthServiceErrorNotFindService,				//超时未查找到授权服务
	AKPAuthServiceErrorFindServiceFailed,			//明确的查找服务失败
	AKPAuthServiceErrorNoUuid,						//无法获取到设备uuid
	AKPAuthServiceErrorNoAuthToken,					//无法获取到BindingAuthToken
	AKPAuthServiceErrorSetAuthTokenFailed,			//设置AuthToken到设备失败
	AKPAuthServiceErrorBindingAuthorizeInProcess,	//另一人正在绑定授权中
	AKPAuthServiceErrorBindingFailed,				//其他绑定失败，设备端从服务端透传过来的
	AKPAuthServiceErrorNeedMgrAuthorize,			//需要管理员授权（分享绑定）
	AKPAuthServiceErrorCancelAuthFailed,			//取消绑定失败，已经绑定
};

@class LKPDeviceBrowseItem;
@interface AKPBindingItem : TBJSONModel
@property (nonatomic, strong, nullable) LKPDeviceBrowseItem *deviceBrowseItem;
@property (nonatomic, copy, nullable) NSString *hostName;
@property (nonatomic, copy, nullable) NSString *deviceIp;
@property (nonatomic, strong, nullable) NSData *deviceAddress;
@property (nonatomic, assign) NSInteger devicePort;
@property (nonatomic, copy, nullable) NSString *udid;
@property (nonatomic, copy, nullable) NSString *productModel;
@property (nonatomic, copy, nullable) NSString *authToken;
@property (nonatomic, copy, nullable) NSString *resultUdid;

@end



@interface TBJSONModel (ALExt)
+ (nullable NSArray *)arrayWithDictionaryArray:(nullable NSArray *)array;
+ (nullable instancetype)safeModelWithJSONDictionary:(nullable NSDictionary *)dict;
@end


/**
 * App <-> Dev json业务报文
 */
@interface AKPDeviceAuthJsonModel : TBJSONModel

@property (nonatomic, copy, nullable) NSString *method;

@end

/**
 * App -> Dev 请求
 */

@interface AKPDeviceAuthGetUuidModel : AKPDeviceAuthJsonModel

@end

@interface AKPDeviceAuthSetAuthTokenModel : AKPDeviceAuthJsonModel

@property (nonatomic, copy, nullable) NSString *authToken;

@end

@interface AKPDeviceAuthNotifyBindingResultResopnseModel : AKPDeviceAuthJsonModel

@property (nonatomic, assign) NSInteger code;

@end


/**
 * Dev -> App请求或响应
 */

@interface AKPDeviceAuthGetUuidResultModel : TBJSONModel

@property (nonatomic, assign) NSInteger code;
@property (nonatomic, copy, nullable) NSString *uuid;
@property (nonatomic, copy, nullable) NSString *desc;

@end

@interface AKPDeviceAuthSetAuthTokenResultModel : TBJSONModel

@property (nonatomic, assign) NSInteger code;
@property (nonatomic, assign, nullable) NSString *result;

@end

@interface AKPDeviceAuthNotifyBindingResultModel : TBJSONModel

@property (nonatomic, assign) NSInteger code;
@property (nonatomic, assign, nullable) NSString *desc;
@property (nonatomic, copy, nullable) NSString *mgrNick;
@property (nonatomic, copy, nullable) NSString *uuid;

@end
