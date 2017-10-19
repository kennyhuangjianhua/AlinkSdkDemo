//
//  BoneKit.h
//  BoneKit
//
//  Created by 培岩 on 2017/1/18.
//  Copyright © 2017年 王培岩. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for BoneKit.
FOUNDATION_EXPORT double BoneKitVersionNumber;

//! Project version string for BoneKit.
FOUNDATION_EXPORT const unsigned char BoneKitVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <BoneKit/PublicHeader.h>

#import <BoneKit/BoneRCTUtils.h>
#import <BoneKit/BoneRCTDefines.h>

#if BONE_IN_OPENSDK
#import <BoneKit/BoneRouter.h>
#import <BoneKit/BoneRouterProtocol.h>
#else
#import <BoneKit/BoneRCTViewController.h>
#endif
