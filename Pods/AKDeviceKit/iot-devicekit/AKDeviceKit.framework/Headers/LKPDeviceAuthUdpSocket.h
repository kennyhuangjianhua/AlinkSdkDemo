//
//  LKPDeviceAuthUdpSocket.h
//  Pods
//
//  Created by Wenji.lsl on 16/1/12.
//
//

#import <Foundation/Foundation.h>
#import "AKPDeviceAuthModels.h"

typedef void (^LKPAuthServiceNotifyBindingResultBlock)(BOOL success, NSDictionary *dict);
typedef void (^LKPAuthServiceDeviceResponseBlock)(BOOL success, NSDictionary *dict);


@interface LKPDeviceAuthUdpSocket : NSObject

@property (nonatomic, strong) AKPBindingItem *bindItem;
@property (atomic, copy) LKPAuthServiceNotifyBindingResultBlock notifyBindingResultBlock;

- (void)getUuidWithCompletionHandler:(LKPAuthServiceDeviceResponseBlock)completionHandler;
- (void)setAuthToken:(NSString *)authToken completionHandler:(LKPAuthServiceDeviceResponseBlock)completionHandler;

@end
