//
//  ViewController.m
//  AlinkDemo
//
//  Created by Dong on 2016/12/28.
//  Copyright © 2016年 aliyun. All rights reserved.
//

#import "ViewController.h"
#import "BLEDiscoverController.h"

#import <AKDevKit/AKOpenDevKit.h>
#import <AlinkSDK/AlinkOpenSDK.h>
#import <BoneKit/BoneKit.h>

#import <ALBBOpenAccountSDK/ALBBOpenAccountSDK.h>
#import <UTDID/UTDevice.h>

#import <AKDebugDashboard/AKDebugDashboard.h>

#import <CocoaLumberjack/CocoaLumberjack.h>
#import "LBXScanPermissions.h"
#import "LBXScanViewStyle.h"
#import "LBXScanViewController.h"
#import "StyleDIY.h"

static NSString * const kRNTestAlertMessage = @"请输入ip地址";

extern DDLogLevel ddLogLevel;

@interface ViewController ()

@property (nonatomic,strong) UITableView *table;
@property (nonatomic,strong) NSMutableArray *data;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.table=[[UITableView alloc] initWithFrame:self.view.frame];
    self.table.dataSource=self;
    self.table.delegate=self;
    [self.view addSubview:self.table];
    
    [self createHeader];
    self.view.backgroundColor=[UIColor colorWithWhite:1 alpha:0.5];
    
    
}


-(void)fetchData{
    
    NSURLSession *session = [NSURLSession sharedSession];
    __weak __typeof(self) weakSelf = self;
    
    NSURLSessionDataTask *dataTask = [session dataTaskWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"https://gaic.alicdn.com/tms/boneDemoConfig.json"]] completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        
        if (!error) {
            
            NSError *err;
            NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data
                                                                options:NSJSONReadingMutableContainers
                                                                  error:&err];
            NSLog(@"tmsResult: %@",dic);
            //deviceConfigURL  title = "Bone"; url = "";
            if ([[dic objectForKey:@"boneAppList"] isKindOfClass:[NSArray class]]) {
                weakSelf.data=[dic objectForKey:@"boneAppList"];
                dispatch_async(dispatch_get_main_queue(), ^{
                    [weakSelf.table reloadData];
                });
                
            }
        }else{
            
            
        }
        
    }];
    
    
    [dataTask resume];
    

}




-(void)createHeader{
    

    NSArray *buttons = [[NSArray alloc] initWithObjects:@"登录",
                        @"登出", @"蓝牙发现",
                        @"设备配网",@"扫一扫",
                        @"BoneKit测试", @"调试日志",@"BoneRouter",
                        nil];
    
    
    int btnWidth = self.view.frame.size.width/3;
    int btnHeight = 40;
    int topMargin=88;
    
    UIView*header=[[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, topMargin+20+(btnHeight+10)*ceil([buttons count]/2.0))];
    UIColor*c1=[UIColor colorWithRed:0.0/256 green:199.0/255 blue:178.0/255 alpha:1];
    for(int i = 0; i < [buttons count]; i++){
        UIButton *btn;
        int f = i % 2;
        int top = 25;
        
        if (f == 0) {
            btn=[[UIButton alloc] initWithFrame:CGRectMake(20, topMargin+top*i, btnWidth, btnHeight)];
        }
        
        if (f == 1) {
            btn=[[UIButton alloc] initWithFrame:CGRectMake(self.view.frame.size.width-20 - btnWidth  , topMargin+top*(i-1), btnWidth, btnHeight)];
        }
        
        
        
        btn.tag = i;
        [btn setTitle:[buttons objectAtIndex:i] forState:UIControlStateNormal];
        [btn addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchDown];
        
        [btn.layer setMasksToBounds:YES];
        [btn.layer setCornerRadius:3.0];
        [btn.layer setBorderWidth:1];
        btn.layer.borderColor=c1.CGColor;
        [btn setTitleColor:c1 forState:UIControlStateNormal];
        
        [header addSubview:btn];
    }
    
    self.table.tableHeaderView=header;
    self.table.tableFooterView=[[UIView alloc]init];
    
    UIImageView*img=[[UIImageView alloc] initWithFrame:CGRectMake((self.view.frame.size.width-160)/2, 5, 78, 76)];
    img.image=[UIImage imageNamed:@"alismart"];
    [header addSubview:img];
    
    
    UILabel*info=[[UILabel alloc] initWithFrame:CGRectMake(img.frame.origin.x+img.frame.size.width+8, 17, 120, 44)];
    info.text=@"IoT 开发工具\nDemoApp";
    info.numberOfLines=2;
    [header addSubview:info];
    info.textColor=c1;
    info.font=[UIFont boldSystemFontOfSize:14];
    
}



- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return self.data.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    //复用标志
    static NSString * cellId = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellId];
    
    if (cell == nil) {
        
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellId] ;
        
    }
    
    NSDictionary*dict=self.data[indexPath.row];
    cell.textLabel.text=[dict objectForKey:@"title"]?:@"";
    UIColor*c2=[UIColor colorWithRed:153.0/256 green:153.0/255 blue:153.0/255 alpha:1];
    cell.textLabel.textColor=c2;
    cell.accessoryType=UITableViewCellAccessoryDisclosureIndicator;
    cell.textLabel.font=[UIFont boldSystemFontOfSize:16];
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    NSDictionary*dict=self.data[indexPath.row];
    NSURL *url = [NSURL URLWithString:[@"alink://" stringByAppendingString:[dict objectForKey:@"url"]?:@""]];
    [[BoneRouter defaultRouter] open:url completionHandler:^(BOOL success) {
        NSLog(@"open:%@ %d", url, success);
        if (!success) {
            UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"提示" message:@"无法打开指定URL" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
            [alert show];
        }
    }];
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
}

- (void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    
    [self.navigationController setNavigationBarHidden:NO animated:NO];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    [self fetchData];
}


-(void)click:(UIButton*)button{
    NSLog(@"%ld",button.tag);
    switch (button.tag) {
            case 0:{
                [self startLogin];
            }
            
            break;
            case 1:{
                [self startLogOut:button];
            }
            break;
            
            case 2:{
                //蓝牙入口
                BLEDiscoverController *vc = [[BLEDiscoverController alloc]init];
                [self.navigationController pushViewController:vc animated:YES];
            }
            break;
			case 3: {
                [self startConfigure];
			}
			break;
            case 4:{

                [self startScan];
            }
            break;
			case 5:{
                [self onDebugReactNative];
			}
			break;
			case 6:{
                [self openLog];
			}
			break;
			case 7: {
                NSURL *url = [NSURL URLWithString:@"https://www.aliyun.com"];
                [[BoneRouter defaultRouter] open:url completionHandler:^(BOOL success) {
                    NSLog(@"open:%@ %d", url, success);
                    if (!success) {
                        UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"提示" message:@"无法打开指定URL" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
                        [alert show];
                    }
                }];
			} break;
        default:
            break;
    }
}

typedef void(^AKRouterCompletionHandler)(NSError *error, NSDictionary *info);

- (void)startConfigure {
    BoneRouterCompletionHandler handler = ^(NSError *error, NSDictionary *info) {
        NSString *str = [NSString stringWithFormat:@"配网成功：%@", info];
        UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"提示" message:str ?: @"" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [alert show];
    };
    
    NSDictionary *options = @{BoneRouterCompletionHandlerKey : handler};
    [[BoneRouter defaultRouter] openCode:@"deviceConfig" options:options completionHandler:^(BOOL success) {
        if (!success) {
            UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"提示" message:@"无法打开指定URL" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
            [alert show];
        }
    }];
}

-(void)startScan{
    
    LBXScanViewController *vc = [LBXScanViewController new];
    vc.style = [StyleDIY ZhiFuBaoStyle];
    vc.isOpenInterestRect = YES;
    self.navigationController.navigationBarHidden=NO;
    [self.navigationController pushViewController:vc animated:YES];


}

-(void)openLog{
    [AKDebugDashboard sharedDashboard].fullScreen = YES;
}

- (void)alertWithTitle:(NSString *)title msg:(NSString *)msg
{
	UIAlertController *alertViewController = [UIAlertController alertControllerWithTitle:title ?: @"" message:msg ?: @"" preferredStyle:UIAlertControllerStyleAlert];
	[alertViewController addAction:[UIAlertAction actionWithTitle:@"ok" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
		
	}]];
	
	[self presentViewController:alertViewController animated:YES completion:^{
		
	}];
	
}

- (void)startLogin {
    if([[AlinkAccount sharedInstance] isLogin]){
        UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"提示" message:@"已经登录过" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [alert show];
    }else{
        [[AlinkAccount sharedInstance] loginWithViewController:nil completionHandler:^(BOOL isSuccessful, NSDictionary *loginResult) {
            DDLogInfo(@"Alink login success: %@, result: %@", @(isSuccessful), loginResult);
            
            [kAlinkSDK invokeWithMethod:@"mtop.openalink.user.channel.bind" params:@{@"type":@"AGOO",@"deviceId":[UTDevice utdid]} completionHandler:^(AlinkResponse *response) {
                
                if (response.successed) {
                    DDLogInfo(@"push 绑定成功");
                }
                else {
                    DDLogInfo(@"push 绑定失败 %@",response.responseError);
                }
            }];
        } cancelationHandler:^{
            DDLogInfo(@"Alink login canceled!");
        }];

    }
}

-(void)startLogOut:(UIButton *)btn {
    __weak typeof(self)weakSelf = self;
    if([[AlinkAccount sharedInstance] isLogin]){
        //防止多次点击
        btn.enabled = NO;
        // 调用 logout 之前必须先调用mtop.openalink.user.channel.unbind
        [kAlinkSDK invokeWithMethod:@"mtop.openalink.user.channel.unbind" params:@{@"type":@"AGOO",@"deviceId":[UTDevice utdid]} completionHandler:^(AlinkResponse *response) {
            if (response.successed) {
                    DDLogInfo(@"push 解除绑定成功");
                [[AlinkAccount sharedInstance] logout:^(NSError * _Nonnull error) {
                    btn.enabled = YES;
                    DDLogInfo(@"logout --err %@",error);
                    NSString *msg = error ? [NSString stringWithFormat:@"登出失败：%@", error] : @"登出成功";
                    [weakSelf alertWithTitle:@"提示" msg:msg];
                }];
            }
            else {
                btn.enabled = YES;
                DDLogInfo(@"push 解除绑定 --err %@",response.responseError);
                NSString *msg = [NSString stringWithFormat:@"AGOO解绑失败：%@", response.responseError];
                [weakSelf alertWithTitle:@"提示" msg:msg];
            }
        }];
    }else{
        UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"提示" message:@"已经处于登出状态" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [alert show];
    }
}

- (void)onDebugReactNative {
    __weak typeof(self) wSelf = self;
    
    NSString *boneDebugIPCache = [[NSUserDefaults standardUserDefaults] objectForKey:@"boneDebugIP"];
    
    NSString *msg = kRNTestAlertMessage;
    
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil
                                                                             message:msg
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        textField.placeholder = @"ip address";
        textField.text = boneDebugIPCache ?: @"";
    }];
    [alertController addAction:[UIAlertAction actionWithTitle:@"确认" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        NSString *host = alertController.textFields.firstObject.text;
        NSString *trimmedHost = [host stringByTrimmingCharactersInSet:
                                 [NSCharacterSet whitespaceAndNewlineCharacterSet]];

        if (trimmedHost.length > 0) {
            [wSelf requestRNLinkWithHost:trimmedHost];
            [[NSUserDefaults standardUserDefaults] setObject:trimmedHost forKey:@"boneDebugIP"];
        }
    }]];
    [alertController addAction:[UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
    }]];
    [self presentViewController:alertController animated:true completion:^{
        
    }];
}

- (void)requestRNLinkWithHost:(NSString *)theHost {
    NSString *link = [NSString stringWithFormat:@"http://%@:8081/boneDebugUrl?platform=ios&ip=%@", theHost, theHost];
    NSURL *url = [NSURL URLWithString:link];
    __weak typeof(self) wSelf = self;
    
    NSURLSession *session = [NSURLSession sharedSession];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    NSURLSessionDataTask *dataTask = [session dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        
        if(error){
            [wSelf showErrorAlert:error];
            return ;
        }
        NSError *parseError = nil;
        NSDictionary *responseObject = [NSJSONSerialization JSONObjectWithData:data
                                                                       options:NSJSONReadingAllowFragments
                                                                         error:&parseError];
        if (parseError) {
            [wSelf showErrorAlert:parseError];
            return;
        }
        
        int code = [[responseObject objectForKey:@"code"] intValue];
        if ( code == 200) {
            NSDictionary *dataObject = [responseObject objectForKey:@"data"];
            NSString *urlString = dataObject[@"url"];
            urlString = [urlString stringByReplacingOccurrencesOfString:@"http:" withString:@"react:"];
            dispatch_async(dispatch_get_main_queue(), ^{
                
                BoneRouterCompletionHandler handler = ^(NSError *error, NSDictionary *info) {
                    NSLog(@"%s error:%@ info:%@", __FUNCTION__, error, info);
                };
                
                NSMutableDictionary *options = [dataObject mutableCopy];
                options[BoneRouterCompletionHandlerKey] = handler;
                
                [[BoneRouter defaultRouter] open:[NSURL URLWithString:urlString] options:options completionHandler:^(BOOL success) {
                    
                }];
            });
        } else {
            NSLog(@"error: %@", error.description);
        }
    }];
    [dataTask resume];
}

- (void)showErrorAlert:(NSError *)error {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil
                                                                             message:[error localizedDescription]
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    
    [alertController addAction:[UIAlertAction actionWithTitle:@"确认" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
    }]];
    
    [self presentViewController:alertController animated:true completion:^{
        
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
