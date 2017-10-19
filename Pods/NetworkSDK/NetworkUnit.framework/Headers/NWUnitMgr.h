//
//  NWUnitMgr.h
//  Pods
//
//  Created by zhishui.lcq on 15/7/15.
//
//  说明：管理用户的单元化信息


#import <Foundation/Foundation.h>

@interface NWUnitMgr : NSObject

+ (NWUnitMgr *)sharedInstance;

- (NSString *)currentUserId;

- (NSString *)getUserUnit:(NSString *)userId;

- (void)updateUserId:(NSString *)userId;

- (void)updateUserUnit:(NSString *)unit userId:(NSString *)userId;

@end
