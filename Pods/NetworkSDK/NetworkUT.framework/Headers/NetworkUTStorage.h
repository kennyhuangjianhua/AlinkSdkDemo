//
//  NSURLConnection+NetworkSDK.h
//  TBSDKNetworkSDK
//
//  Created by Roger.Mu on 8/6/14.
//  Copyright (c) 2014 taobao.com. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 * 该类的打点实现全部都移到 NWUTInternal 中，NetworkUTStorage 剩余部分未修改是外部有调用，故不能修改。
 */
@class TBSDKLinkedMutableDictionary;

@interface NetworkUTStorage : NSObject

@property (nonatomic, strong) TBSDKLinkedMutableDictionary *TB_STD_NET_DB;

// default init limite size is 80
+ (id)shareInstance;

// set network context
- (void)SET_NETWORK_DB:(NSDictionary *)db withObjectKey:(id)key;

// get network context
- (NSDictionary *)GET_NETWORK_DB:(id)key;

// delete network context
- (void)DELETE_NETWORK_DB:(id)key;

@end
