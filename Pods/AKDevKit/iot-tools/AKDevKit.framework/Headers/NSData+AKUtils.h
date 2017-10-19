//
//  NSData+AKUtils.h
//  AKDevKit
//
//  Created by 文季 on 15/11/24.
//  Copyright © 2015年 Alink. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (AKUtils)

- (NSData *)ak_dataWithAes128Encrypt:(NSString *)key;
- (NSData *)ak_dataWithAes128Decrypt:(NSString *)key;

- (NSData *)ak_md5Data;
- (NSString *)ak_md5Str;
- (NSString *)ak_base64Md5;

- (NSString *)ak_ipString;

@end
