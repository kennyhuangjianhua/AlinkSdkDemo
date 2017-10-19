//
//  AlinkResponse.h
//  AlinkSDK
//
//  Created by 文季 on 2016/12/20.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Alink响应对象
 */
@interface AlinkResponse : NSObject

@property (nonatomic, assign) BOOL successed;                   ///< 是否成功
@property (nonatomic, strong, nullable) id dataObject;          ///< 服务端返回的json的data字段
@property (nonatomic, strong, nullable) NSError *responseError; ///< 错误 @see NSError (AlinkUtils)


+ (instancetype)responseWithDataObject:(id)dataObject;

+ (instancetype __nullable)responseWithDataObject:(id __nullable)dataObject error:(NSError * __nullable)error;

@end

NS_ASSUME_NONNULL_END
