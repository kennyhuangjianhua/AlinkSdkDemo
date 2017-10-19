//
//  BoneRCTDefines.h
//  Pods
//
//  Created by OHSC on 2017/2/20.
//
//

#ifndef BoneRCTDefines_h
#define BoneRCTDefines_h

#define kBoneReactNativeVersion @"2.0.0"
#define kBoneRCTBridgeModuleName @"Bone"
#define kBoneUTEventId 19999

#ifndef BONE_IN_OPENSDK
#define BONE_IN_OPENSDK 1
#endif

#if BONE_IN_OPENSDK
    #define kOpenSDKVersion @"1.0.0"
#endif

#if BONE_IN_OPENSDK
    #define kBoneReactNativeBaseUrl @"https://gaic.alicdn.com/market/h5/{cdnEnv}/bone-base/base.ios.js"
#else
    #define kBoneReactNativeBaseUrl @"https://gaic.alicdn.com/aic/h5/{cdnEnv}/bone-base/base.ios.js"
#endif


#endif /* BoneRCTDefines_h */
