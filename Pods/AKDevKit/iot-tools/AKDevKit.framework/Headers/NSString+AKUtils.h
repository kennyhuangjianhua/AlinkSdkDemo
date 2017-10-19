//
//  NSString+AKUtils.h
//  AKDevKit
//
//  Created by 文季 on 15/11/24.
//  Copyright © 2015年 Alink. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (AKUtils)

- (NSData *)ak_dataWithAes128Encrypt:(NSString *)key;

- (NSString *)ak_md5;
- (NSString *)ak_base64Md5;
- (NSString *)ak_fileMd5;

+ (BOOL)ak_isBlank:(NSString *)str;

@end
