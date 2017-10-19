//
//  DeviceOperateViewController.h
//  sds_bt_demo
//
//  Created by xuanyan.lyw on 2017/4/20.
//  Copyright © 2017年 coolnameismy. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SmurfsSDK/SmurfsSDK.h>

@interface BLEOperateViewController : UITableViewController<SmurfsOperateSceneDelegate>

@property(nonatomic,strong) NSString *mac;

@end
