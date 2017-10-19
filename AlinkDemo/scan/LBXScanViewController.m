//
//
//  
//
//  Created by lbxia on 15/10/21.
//  Copyright © 2015年 lbxia. All rights reserved.
//

#import "LBXScanViewController.h"
#import "Global.h"
#import <BoneKit/BoneKit.h>

@interface LBXScanViewController ()


@end

@implementation LBXScanViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    if ([self respondsToSelector:@selector(setEdgesForExtendedLayout:)]) {
        
        self.edgesForExtendedLayout = UIRectEdgeNone;
    }
    
    self.view.backgroundColor = [UIColor blackColor];
    

    switch ([Global sharedManager].libraryType) {
        case SLT_Native:
            self.title = @"native";
            break;
        case SLT_ZXing:
            self.title = @"ZXing";
            break;
        case SLT_ZBar:
            self.title = @"ZBar";
            break;
        default:
            break;
    }
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    [self drawScanView];
    
    //不延时，可能会导致界面黑屏并卡住一会
    [self performSelector:@selector(startScan) withObject:nil afterDelay:0.2];
}

//绘制扫描区域
- (void)drawScanView
{
    if (!_qRScanView)
    {
        CGRect rect = self.view.frame;
        rect.origin = CGPointMake(0, 0);
        
        self.qRScanView = [[LBXScanView alloc]initWithFrame:rect style:_style];
        
        [self.view addSubview:_qRScanView];
    }
    [_qRScanView startDeviceReadyingWithText:@"相机启动中"];
}

- (void)reStartDevice
{
    switch ([Global sharedManager].libraryType) {
        case SLT_Native:
        {
#ifdef LBXScan_Define_Native
            [_scanObj startScan];
#endif
        }
            break;
        case SLT_ZXing:
        {
#ifdef LBXScan_Define_ZXing
            [_zxingObj start];
#endif
        }
            break;
        case SLT_ZBar:
        {
#ifdef LBXScan_Define_ZBar
            [_zbarObj start];
#endif
        }
            break;
        default:
            break;
    }
    
}

//启动设备
- (void)startScan
{
    if ( ![LBXScanPermissions cameraPemission] )
    {
        [_qRScanView stopDeviceReadying];
        
        [self showError:@"   请到设置隐私中开启本程序相机权限   "];
        return;
    }
    
    UIView *videoView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, CGRectGetWidth(self.view.frame), CGRectGetHeight(self.view.frame))];
    videoView.backgroundColor = [UIColor clearColor];
    [self.view insertSubview:videoView atIndex:0];
    __weak __typeof(self) weakSelf = self;
    
    switch ([Global sharedManager].libraryType) {
        case SLT_Native:
        {

            
#ifdef LBXScan_Define_Native
            
            if (!_scanObj )
            {
                CGRect cropRect = CGRectZero;
                
                if (_isOpenInterestRect) {
                    
                    //设置只识别框内区域
                    cropRect = [LBXScanView getScanRectWithPreView:self.view style:_style];
                }

                NSString *strCode = AVMetadataObjectTypeQRCode;
                if ([Global sharedManager].scanCodeType != SCT_BarCodeITF ) {
                    
                    strCode = [[Global sharedManager]nativeCodeType];
                }
                
                //AVMetadataObjectTypeITF14Code 扫码效果不行,另外只能输入一个码制，虽然接口是可以输入多个码制
                self.scanObj = [[LBXScanNative alloc]initWithPreView:videoView ObjectType:@[strCode] cropRect:cropRect success:^(NSArray<LBXScanResult *> *array) {
                    
                    [weakSelf scanResultWithArray:array];
                }];
                [_scanObj setNeedCaptureImage:_isNeedScanImage];
            }
            [_scanObj startScan];
#endif

        }
            break;
        case SLT_ZXing:
        {

#ifdef LBXScan_Define_ZXing
            if (!_zxingObj) {
                
                self.zxingObj = [[ZXingWrapper alloc]initWithPreView:videoView block:^(ZXBarcodeFormat barcodeFormat, NSString *str, UIImage *scanImg) {
                    
                    LBXScanResult *result = [[LBXScanResult alloc]init];
                    result.strScanned = str;
                    result.imgScanned = scanImg;
                    result.strBarCodeType = [self convertZXBarcodeFormat:barcodeFormat];
                    
                    [weakSelf scanResultWithArray:@[result]];
                    
                }];
                
                if (_isOpenInterestRect) {
                    
                    //设置只识别框内区域
                    CGRect cropRect = [LBXScanView getZXingScanRectWithPreView:videoView style:_style];
                                        
                     [_zxingObj setScanRect:cropRect];
                }               
            }
            [_zxingObj start];
#endif
        }
            break;
        case SLT_ZBar:
        {
#ifdef LBXScan_Define_ZBar
            if (!_zbarObj) {
                
                self.zbarObj = [[LBXZBarWrapper alloc]initWithPreView:videoView barCodeType:ZBAR_I25 block:^(NSArray<LBXZbarResult *> *result) {
                    
                    //测试，只使用扫码结果第一项
                    LBXZbarResult *firstObj = result[0];
                    
                    LBXScanResult *scanResult = [[LBXScanResult alloc]init];
                    scanResult.strScanned = firstObj.strScanned;
                    scanResult.imgScanned = firstObj.imgScanned;
                    scanResult.strBarCodeType = [LBXZBarWrapper convertFormat2String:firstObj.format];
                    
                    [weakSelf scanResultWithArray:@[scanResult]];
                }];
            }
            [_zbarObj start];
#endif
        }
            break;
        default:
            break;
    }
    
#ifdef LBXScan_Define_UI
    [_qRScanView stopDeviceReadying];
    [_qRScanView startScanAnimation];
#endif
    
    self.view.backgroundColor = [UIColor clearColor];
}


-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];

    self.navigationController.navigationBarHidden=NO;
}



- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [NSObject cancelPreviousPerformRequestsWithTarget:self];
 
    [self stopScan];
    
    [_qRScanView stopScanAnimation];
}

- (void)stopScan
{
    switch ([Global sharedManager].libraryType) {
        case SLT_Native:
        {
#ifdef LBXScan_Define_Native
            [_scanObj stopScan];
#endif
        }
            break;
        case SLT_ZXing:
        {
#ifdef LBXScan_Define_ZXing
            [_zxingObj stop];
#endif
        }
            break;
        case SLT_ZBar:
        {
#ifdef LBXScan_Define_ZBar
            [_zbarObj stop];
#endif
        }
            break;
        default:
            break;
    }

}

#pragma mark -实现类继承该方法，作出对应处理

- (void)scanResultWithArray:(NSArray<LBXScanResult*>*)array
{
    if (!array ||  array.count < 1)
    {
        [self popAlertMsgWithScanResult:nil];
        
        return;
    }
    
    //经测试，可以同时识别2个二维码，不能同时识别二维码和条形码
//    for (LBXScanResult *result in array) {
//        
//        NSLog(@"scanResult:%@",result.strScanned);
//    }
    
    LBXScanResult *scanResult = array[0];
    
    NSString*strResult = scanResult.strScanned;
    
    self.scanImage = scanResult.imgScanned;
    
    if (!strResult) {
        
        [self popAlertMsgWithScanResult:nil];
        
        return;
    }
    
    //震动提醒
    // [LBXScanWrapper systemVibrate];
    //声音提醒
    //[LBXScanWrapper systemSound];
    
    [self showNextVCWithScanResult:scanResult];
    
}

- (void)popAlertMsgWithScanResult:(NSString*)strResult
{
    if (!strResult) {
        
        strResult = @"识别失败";
    }
    
    __weak __typeof(self) weakSelf = self;
    
    /*
    [LBXAlertAction showAlertWithTitle:@"扫码内容" msg:strResult buttonsStatement:@[@"知道了"] chooseBlock:^(NSInteger buttonIdx) {
        
        [weakSelf reStartDevice];
    }];*/
}

- (void)showNextVCWithScanResult:(LBXScanResult*)strResult
{
    
    
    if (strResult.strScanned) {
        NSURL *url = [NSURL URLWithString:strResult.strScanned];
        [[BoneRouter defaultRouter] open:url completionHandler:^(BOOL success) {
            NSLog(@"open:%@ %d", url, success);
            if (!success) {
                UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"提示" message:@"无法打开指定URL" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
                [alert show];
            }
        }];
    }else{
        [self showError:@"不是有效 ReactNative 服务端地址"];
    }
    
    /*
    ScanResultViewController *vc = [ScanResultViewController new];
    vc.imgScan = strResult.imgScanned;
    
    vc.strScan = strResult.strScanned;
    
    vc.strCodeType = strResult.strBarCodeType;
    
    [self.navigationController pushViewController:vc animated:YES];
     */
}


//开关闪光灯
- (void)openOrCloseFlash
{
    
    switch ([Global sharedManager].libraryType) {
        case SLT_Native:
        {
#ifdef LBXScan_Define_Native
            [_scanObj changeTorch];
#endif
        }
            break;
        case SLT_ZXing:
        {
#ifdef LBXScan_Define_ZXing
            [_zxingObj openOrCloseTorch];
#endif
        }
            break;
        case SLT_ZBar:
        {
#ifdef LBXScan_Define_ZBar
            [_zbarObj openOrCloseFlash];
#endif
        }
            break;
        default:
            break;
    }
    self.isOpenFlash =!self.isOpenFlash;
}


#pragma mark --打开相册并识别图片

/*!
 *  打开本地照片，选择图片识别
 */
- (void)openLocalPhoto
{
    UIImagePickerController *picker = [[UIImagePickerController alloc] init];
    
    picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    
    picker.delegate = self;
   
    //部分机型有问题
//    picker.allowsEditing = YES;
    
    
    [self presentViewController:picker animated:YES completion:nil];
}



//当选择一张图片后进入这里

-(void)imagePickerController:(UIImagePickerController*)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    [picker dismissViewControllerAnimated:YES completion:nil];    
    
    __block UIImage* image = [info objectForKey:UIImagePickerControllerEditedImage];
    
    if (!image){
        image = [info objectForKey:UIImagePickerControllerOriginalImage];
    }
    
    __weak __typeof(self) weakSelf = self;
        
    switch ([Global sharedManager].libraryType) {
        case SLT_Native:
        {
#ifdef LBXScan_Define_Native
            if ([[[UIDevice currentDevice]systemVersion]floatValue] >= 8.0)
            {
                [LBXScanNative recognizeImage:image success:^(NSArray<LBXScanResult *> *array) {
                    [weakSelf scanResultWithArray:array];
                }];
            }
            else
            {
                [self showError:@"native低于ios8.0系统不支持识别图片条码"];
            }
#endif
        }
            break;
        case SLT_ZXing:
        {
#ifdef LBXScan_Define_ZXing
            
            [ZXingWrapper recognizeImage:image block:^(ZXBarcodeFormat barcodeFormat, NSString *str) {
                
                LBXScanResult *result = [[LBXScanResult alloc]init];
                result.strScanned = str;
                result.imgScanned = image;
                result.strBarCodeType = [self convertZXBarcodeFormat:barcodeFormat];
                
                [weakSelf scanResultWithArray:@[result]];
            }];
#endif
            
        }
            break;
        case SLT_ZBar:
        {
#ifdef LBXScan_Define_ZBar
            [LBXZBarWrapper recognizeImage:image block:^(NSArray<LBXZbarResult *> *result) {
                
                //测试，只使用扫码结果第一项
                LBXZbarResult *firstObj = result[0];
                
                LBXScanResult *scanResult = [[LBXScanResult alloc]init];
                scanResult.strScanned = firstObj.strScanned;
                scanResult.imgScanned = firstObj.imgScanned;
                scanResult.strBarCodeType = [LBXZBarWrapper convertFormat2String:firstObj.format];
                
                [weakSelf scanResultWithArray:@[scanResult]];
                
            }];
#endif
            
        }
            break;
            
        default:
            break;
    }
}
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    NSLog(@"cancel");
    
    [picker dismissViewControllerAnimated:YES completion:nil];
}

//子类继承必须实现的提示
- (void)showError:(NSString*)str
{
    [[UIAlertView alloc] initWithTitle:str message:nil delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil,nil];
     //[LBXAlertAction showAlertWithTitle:@"提示" msg:str buttonsStatement:@[@"知道了"] chooseBlock:nil];
}
@end
