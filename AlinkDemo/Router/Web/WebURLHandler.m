//
//  WebURLHandler.m
//  Router
//
//  Created by Hager Hu on 2/8/17.
//  Copyright © 2017 Hager Hu. All rights reserved.
//

#import "WebURLHandler.h"
#import "WebViewController.h"
#import <GHKit/GHKit.h>

@implementation WebURLHandler

+ (BOOL)canHandle:(NSURL *)url params:(NSDictionary *)params {
    if ([url.absoluteString hasSuffix:@".js"]) {
        return NO;
    }
    
    
    NSString *scheme = url.scheme;
    if (scheme && ([scheme isEqualToString:@"http"] || [scheme isEqualToString:@"https"])) {
        return YES;
    }
    
    return NO;
}


+ (UIViewController *)controllerWithURL:(NSURL *)url params:(NSDictionary<NSString *, id> *)params {
    UIStoryboard *main = [UIStoryboard storyboardWithName:@"Router" bundle:nil];
    WebViewController *controller = (WebViewController *)[main instantiateViewControllerWithIdentifier:@"WebViewController"];
    
    NSString *newURL = [url absoluteString];
    
    if (params) {
        if ([url query]) {
            newURL = [NSString stringWithFormat:@"%@&%@", url, [params gh_queryString]];
        } else {
            newURL = [NSString stringWithFormat:@"%@?%@", url, [params gh_queryString]];
        }
    }

    controller.url = [NSURL URLWithString:newURL];
    return controller;
}

@end
