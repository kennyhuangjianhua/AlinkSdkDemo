//
//  BoneRCTUtils.h
//  Pods
//
//  Created by OHSC on 2017/2/20.
//
//

#import <Foundation/Foundation.h>

//! 版本号, e.g 3.0.0
NSString *BoneAppShortVersion();

//! 设置 CDN 环境
void BoneRCTSetCDNEnvironment(NSString *cdnEnv);

//! 获取 CDN 环境
NSString *BoneRCTGetCDNEnvironment();

//! 设置 Server 环境
void BoneRCTSetServerEnvironment(NSString *serverEnv);

//! 获取 Server 环境
NSString *BoneRCTGetServerEnvironment();

//! 设置 Base 地址
void BoneRCTSetBaseURLString(NSString *baseURLString);

//! 获取 Base 地址
NSString *BoneRCTGetBaseURLString();

//! 判断 URL 是否为本地调试 URL
BOOL BoneRCTIsDebugURL(NSURL *url);

//! 获取当前总内存
extern double BoneRCTTotalMemory(void);

//! 获取已使用内存
extern double BoneRCTUsedMemory(void);


#if BONE_IN_OPENSDK
//! 设置 BoneKey
void BoneRCTSetBoneKey(NSString *boneKey);

//! 获取 BoneKey
NSString *BoneRCTGetBoneKey();

#endif
