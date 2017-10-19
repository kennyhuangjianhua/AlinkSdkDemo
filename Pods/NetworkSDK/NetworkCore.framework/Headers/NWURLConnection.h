//
//  NWURLConnection.h
//  ALINetworkSDK
//
//  Created by wuchen.xj on 3/31/16.
//  Copyright © 2016 wuchen.xj. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NWURLConnection;


NS_ASSUME_NONNULL_BEGIN

/**
 * 请求类型
 */
typedef enum {
    kNWHttp,                                                                // 强制短连
    kNWTnet,                                                                // 强制长连
    kNWTnetWithDegradable,                                                  // 强制长连，若失败自动降级到短连重试
    kNWAuto                                                                 // 网络库自己判断，默认选项
} NWConnectionType;


/**
 * 短连请求底层是使用NSURLConnection, 还是NSURLSession
 * 如果使用NSURLProtocol hook的方式，则默认保持与上层一致
 */
typedef enum {
    kNWNSURLConnection,
    kNWNSURLSession
} NWHttpConnectionType;


/**
 * 请求的控制参数
 */
@interface NWConnectionOption : NSObject
@property (nonatomic, assign)   NWConnectionType        connectionType;          // 默认 kNWAuto
@property (nonatomic, assign)   NWHttpConnectionType    httpConnectionType;      // 默认 kNWNSURLSession
@property (nonatomic, assign)   BOOL                    isForceLocalDNS;         // 默认 NO
@end


/**
 * NWConnectionProtocol 的回调
 */
@protocol NWURLConnectionDelegate <NSObject>

@optional

- (void)connection:(nullable NWURLConnection *)connection
didReceiveResponse:(nullable NSHTTPURLResponse *)response;

- (void)connection:(nullable NWURLConnection *)connection
    didReceiveData:(nullable NSData *)data;

- (void)connection:(nullable NWURLConnection *)connection
  didFailWithError:(nullable NSError *)error;

- (void)connection:(nullable NWURLConnection *)connection
   didSendBodyData:(NSInteger)bytesWritten
 totalBytesWritten:(NSInteger)totalBytesWritten
totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite;

- (void)connection:(nullable NWURLConnection *)connection
wasRedirectedToRequest:(nullable NSURLRequest *)redirectRequest
  redirectResponse:(nullable NSHTTPURLResponse *)response;

- (void)connectionDidFinishLoading:(nullable NWURLConnection *)connection;

@end


/**
 * 自定义 HTTPS 证书校验回调
 *
 * 如果业务方需要自己处理证书校验，比如app只信任内置安全证书，则可以通过该回调来处理.
 * 因为 NSURLConnection 与 NSURLSession 调用的方式不同，这个protocol同时提供两个
 * 函数，业务方根据自己是使用 NSURLConnection 还是 NSURLSession 来填充不同的回调。
 */
@protocol NWHttpAuthenticationChallengeDelegate <NSObject>

@optional

/**
 * NSURLConnection 的 https 证书校验回调
 */
- (BOOL)connection:(nullable NWURLConnection *)connection
   nsurlConnection:(NSURLConnection *)nsurlConnection
willSendRequestForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;


/**
 * NSURLSession 的 https 证书校验回调
 */
- (BOOL)connection:(nullable NWURLConnection *)connection
      nsurlSession:(NSURLSession *)nsurlSession
didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
 completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition, NSURLCredential *))completionHandler;

@end



/**
 * 网络库的请求的显式调用接口。
 */
@interface NWURLConnection : NSObject

+ (BOOL)existAccelerateConnection:(nonnull NSString *)host withScheme:(nonnull NSString *)scheme;

- (nullable instancetype)initWithRequest:(nonnull NSURLRequest *)request
                                delegate:(nullable id<NWURLConnectionDelegate>)delegate;

- (void)setCustomAuthenticationChallenge:(nullable id<NWHttpAuthenticationChallengeDelegate>)delegate;

- (BOOL)isAccelerated;

- (void)startWithOption:(nonnull NWConnectionOption *)option;

- (void)start;

- (void)cancel;

@end

NS_ASSUME_NONNULL_END
