//
//  AlinkSDK+Util.h
//  Pods
//
//  Created by 张光宇 on 10/23/15.
//
//

#import <Foundation/Foundation.h>

//! 版本号, e.g 3.0.0
NSString *AKBundleShortVersion();

//! 综合版本号, e.g 3.0.0.2222
NSString *AKVersionString();

/**
 * 版本号比较
 *
 * AKVersionCompare(@"3.0.1",@"3.0.0") => 1
 *
 * AKVersionCompare(@"3.0.1.1133",@"3.0.2") => -1
 *
 * AKVersionCompare(@"3.0.1",@"3.0.1") => 0
 *
 */
NSComparisonResult AKVersionCompare(NSString *versionA, NSString *versionB);
