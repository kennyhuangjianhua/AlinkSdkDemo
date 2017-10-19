//
//  LKUtilsDefine.h
//  Pods
//
//  Created by 张光宇 on 9/7/15.
//
//


#import <Foundation/Foundation.h>

typedef void (^AKBooleanResultBlock)(BOOL succeeded, NSError *error);
typedef void (^AKArrayResultBlock)(NSArray *result, NSError *error);
typedef void (^AKObjectResultBlock)(id object, NSError *error);
typedef void (^AKProgressBlock)(int progress, NSString *progressInfo);
typedef void (^AKEmptyBlock)();


typedef AKBooleanResultBlock	ALBooleanResultBlock;
typedef AKArrayResultBlock		ALArrayResultBlock;
typedef AKObjectResultBlock		ALObjectResultBlock;
typedef AKProgressBlock			ALProgressBlock;
typedef AKEmptyBlock			ALEmptyBlock;

