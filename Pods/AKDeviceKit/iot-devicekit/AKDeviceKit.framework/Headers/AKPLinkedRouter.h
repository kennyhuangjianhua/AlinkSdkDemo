//
// AKPLinkedRouter.h
//  Pods
//
//  Created by Hager Hu on 8/1/16.
//
//

#import <Foundation/Foundation.h>

typedef void(^LKPAlinkCallback)(NSDictionary *dict);

@interface AKPLinkedRouter : NSObject

+sharedInstance;

// 路由器
-(void)requestRouterNameInfoWithCallback:(LKPAlinkCallback)callback;
-(void)requestRouterUUIDWithCallback:(LKPAlinkCallback)callback password:(NSString *)pw;

@end
