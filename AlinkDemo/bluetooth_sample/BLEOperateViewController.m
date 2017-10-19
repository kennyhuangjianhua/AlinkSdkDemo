//
//  DeviceOperateViewController.m
//  sds_bt_demo
//
//  Created by xuanyan.lyw on 2017/4/20.
//  Copyright © 2017年 coolnameismy. All rights reserved.
//

#import "BLEOperateViewController.h"

@interface BLEOperateViewController () {
    SmurfsOperateScene *operateScene;
    NSMutableArray *msgs;
}

@end

@implementation BLEOperateViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //ble start
    [self bleStart];
    //ui and function config
    [self UIConfig];
}
-(void)viewDidDisappear:(BOOL)animated {
    //退出连接
    [operateScene exit];
}


- (void)bleStart {
    operateScene = [Smurfs createOperateScene:@"model" mac:self.mac script:nil];
    operateScene.delegate = self;
    //建立连接
    [operateScene enter];
}

- (void)UIConfig {
    
    msgs = [NSMutableArray array];
    
    [self.view setBackgroundColor:[UIColor whiteColor]];\
    //导航右侧菜单
    UIBarButtonItem *refreshBtn = [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(interactiveBtnClick:)];
    self.navigationItem.rightBarButtonItem = refreshBtn;
    [self setTitle:@"正在连接设备..."];
}

- (void) interactiveBtnClick:(id)sender {
    __weak __typeof(self) weakSelf = self;
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"与外设交互" message:@"" preferredStyle:UIAlertControllerStyleActionSheet];
    UIAlertAction *act1 = [UIAlertAction actionWithTitle:@"写入数据1e0701010203" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [weakSelf writeTestData];
    }];

    UIAlertAction *act2 = [UIAlertAction actionWithTitle:@"清空list" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [weakSelf clearMsgs];
    }];
    UIAlertAction *act3 = [UIAlertAction actionWithTitle:@"fetchHistory" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        SmurfsCmdModel *cmd = [SmurfsCmdModel makeFromMothed:@"fetchHistory"];
        [operateScene cmdProcess:cmd];
    }];

    [alert addAction:act1];
    [alert addAction:act2];
    [alert addAction:act3];
    [self presentViewController:alert animated:YES completion:^{}];
 
}

#pragma mark - ble delegate

- (void)onReady {
    
    NSLog(@">>> onReady");

    //[self xiangshan_987v3_scale];
    [self aliyun_iot_bt_virtual_device];
    [self insertMsgWithColor:@"green" main:@"onReady" detail:nil];
}

- (void)onReceived:(CBUUID *)uuid data:(NSData *)data {
    NSLog(@">>> onReceived uuid:%@, data:%@",uuid,data.description);
    //读取系统时间
    if ([[uuid UUIDString] isEqualToString:@"2A08"]) {
        NSLog(@">>> 系统时间:%@",data.description);
    }
    [self insertMsg:[NSString stringWithFormat:@">>> onReceived uuid:%@",uuid]  detail:[NSString stringWithFormat:@"%@",data]];
}

- (void)onMessage:(NSString *)event uuid:(CBUUID *)uuid data:(NSString *)data {
    NSLog(@">>> onMessage event:%@, uuid:%@,data:%@",event,uuid,data);
    [self insertMsg:[NSString stringWithFormat:@">>> onMessage event:%@",event]  detail:[NSString stringWithFormat:@"uuid:%@,data:%@",uuid,data]];
    if ([event isEqualToString:@"connected"]) {
        [self setTitle:@"已连接设备"];
    }
    if ([event isEqualToString:@"disconnect"]) {
        [self setTitle:@"连接设备断开，正在重连"];
    }
}

- (void)notifyJsLog:(NSString *)msg {
    NSLog(@">>> msg msg:%@",msg);
    [self insertMsg:msg detail:nil];
}

#pragma mark - 测试业务


//iot 蓝牙虚拟设备
- (void)aliyun_iot_bt_virtual_device {
    
    Byte buff[] =  {0x1e,0x07,0x12,0x11,0x01,0x02,0x03};
    NSData *data = [NSData dataWithBytes:buff length:7];
    
    [operateScene openNotify:@"fff3"];

    
    [operateScene read:@"fff1"];
    [operateScene write:@"fff2" value:data];
}

//香山987v3 体脂称
- (void)xiangshan_987v3_scale {
    //订阅消息
    [operateScene openNotify:@"2A9C"];
    
    //写入系统时间 2A19
    Byte buff[] =  {0x1e,0x07,0x12,0x11,0x01,0x02,0x03};
    NSData *data = [NSData dataWithBytes:buff length:7];
    
    [operateScene write:@"2A08" value:data];//071e0c0b010101
    
    //读取电量
    [operateScene read:@"2A19"];
    
    //读取时间
    [operateScene read:@"2A08"];
}

#pragma mark - ali sdk utils

- (void)insertMsg:(NSString *)main detail:(NSString *)detail {
    [self insertMsgWithColor:@"gray" main:main detail:detail];
}

- (void)insertMsgWithColor:(NSString *)color main:(NSString *)main detail:(NSString *)detail{
    
    NSMutableArray *indexPaths = [[NSMutableArray alloc] init];
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:msgs.count inSection:0];
    [indexPaths addObject:indexPath];
    
    if ([detail isEqualToString:@""] || detail == nil) {
        detail = [self dateTimeNow];
    }
    NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithObjectsAndKeys:main,@"main",detail,@"detail", nil];
    if (color) {
        [dic setValue:color forKey:@"color"];
    }
    [msgs addObject:dic];
    
    [self.tableView insertRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
}

- (NSString *)dateTimeNow{
    
    NSDateFormatter * formatter = [[NSDateFormatter alloc ] init];
    [formatter setDateFormat:@"YYYY-MM-dd hh:mm:ss:SSS"];
    NSString *date =  [formatter stringFromDate:[NSDate date]];
    NSString *timeLocal = [[NSString alloc] initWithFormat:@"%@", date];
    //    NSLog(@"%@", timeLocal);
    return timeLocal;
}

- (void)writeTestData {
    Byte datatime[] = {0x1e,0x07,0x01,0x01,0x02,0x03}; //2017-01-01 2:03 <07010102 0300>
    NSData *data = [NSData dataWithBytes:datatime length:6];
    [operateScene write:@"fff2" value:data];
}
- (void)clearMsgs {
    msgs  = [[NSMutableArray alloc]init];
    [self.tableView reloadData];
}

#pragma mark - Table view data source


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return msgs.count;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    //    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"mgscell" forIndexPath:indexPath];
    UITableViewCell *cell;
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"cell"];
        cell.accessoryType = UITableViewCellSelectionStyleNone;
    }
    
    //数据
    NSDictionary *item = [msgs objectAtIndex:indexPath.row];
    cell.textLabel.text = [item objectForKey:@"main"];
    cell.detailTextLabel.text = [item objectForKey:@"detail"];
    NSString *color = [item objectForKey:@"color"];
    if ([color isEqualToString:@"red"]) {
        cell.textLabel.textColor = [UIColor redColor];
    }
    if ([color isEqualToString:@"gray"]) {
        cell.textLabel.textColor = [UIColor grayColor];
    }
    if ([color isEqualToString:@"green"]) {
        cell.textLabel.textColor = [UIColor greenColor];
    }
    if ([color isEqualToString:@"yellow"]) {
        cell.textLabel.textColor = [UIColor yellowColor];
    }
    return cell;
}



@end
