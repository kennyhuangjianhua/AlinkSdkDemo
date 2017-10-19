//
//  FirstViewController.m
//  sds_bt_demo
//
//  Created by xuanyan.lyw on 2017/4/19.
//  Copyright © 2017年 coolnameismy. All rights reserved.
//

#import "BLEDiscoverController.h"
#import "BLEOperateViewController.h"

#import <SmurfsSDK/SmurfsSDK.h>

@interface BLEDiscoverController () {
    NSMutableArray *devices;
    SmurfsPairScene *pairScene;
}

@end

@implementation BLEDiscoverController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //初始化蓝牙模块和功能
    pairScene = [Smurfs createPairSceneWithBlock:^(CBPeripheral *peripheral, NSDictionary *advertisementData, NSNumber *RSSI, NSString *localName, BOOL isAlinkAdvertisement, NSString *mac, NSString *version) {
        
        //过滤了非alink协议的设备
        //if (!isAlinkAdvertisement || [version isEqualToString:@"20"]) {return;}
        
        NSLog(@"peripheral:%@,advertisementData:%@, RSSI:%@, localName:%@, isAlinkAdvertisement:%d, mac:%@, version:%@",peripheral,advertisementData, RSSI, localName,isAlinkAdvertisement, mac, version);
        
        //只显示可以识别出mac地址的设备 alink协议默认可以解析出mac地址，如果非alink协议，请在这里补充得到mac地址的方式,例如：
        //mac = [self.parseMac:peripheral];
        if(![mac isEqualToString:@""] && mac != nil){
            [self insertTableView:peripheral mac:mac advertisementData:advertisementData RSSI:RSSI];
        }
    }];
    
    //开始启动蓝牙扫描使用 [pairScene enter];方法，结束使用[pairScene exit]方法;
    
    //设置ui样式
    [self setTitle:@"scanfor alink devices"];
    UIBarButtonItem *refreshBtn = [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh target:self action:@selector(refreshBtnClick:)];
    
    self.navigationItem.rightBarButtonItem = refreshBtn;
    //初始化数组
    devices = [[NSMutableArray alloc]init];
}


-(void)viewDidAppear:(BOOL)animated {
    [pairScene enter];
}

-(void)viewDidDisappear:(BOOL)animated {
    [pairScene exit];
}

- (void) refreshBtnClick:(id)sender {
    //清空数据
    devices = [[NSMutableArray alloc]init];
    [self.tableView reloadData];
    [pairScene enter];
}

//插入table数据
-(void)insertTableView:(CBPeripheral *)peripheral mac:(NSString *)mac advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI{
    
    NSArray *peripherals = [devices valueForKey:@"peripheral"];
    if(![peripherals containsObject:peripheral]) {
        NSMutableArray *indexPaths = [[NSMutableArray alloc] init];
        NSIndexPath *indexPath = [NSIndexPath indexPathForRow:peripherals.count inSection:0];
        [indexPaths addObject:indexPath];
        
        NSMutableDictionary *item = [[NSMutableDictionary alloc] init];
        [item setValue:peripheral forKey:@"peripheral"];
        [item setValue:mac forKey:@"mac"];
        [item setValue:RSSI forKey:@"RSSI"];
        [item setValue:advertisementData forKey:@"advertisementData"];
        [devices addObject:item];
        
        [self.tableView insertRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
    }
}

#pragma mark -table委托 table delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return devices.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    UITableViewCell *cell = [self.tableView dequeueReusableCellWithIdentifier:@"cell"];
    NSDictionary *item = [devices objectAtIndex:indexPath.row];
    CBPeripheral *peripheral = [item objectForKey:@"peripheral"];
    //    NSDictionary *advertisementData = [item objectForKey:@"advertisementData"];
    NSNumber *RSSI = [item objectForKey:@"RSSI"];
    NSString *mac = [item objectForKey:@"mac"];
    NSString *peripheralName = peripheral.name;
    
    
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"cell"];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    cell.textLabel.text = peripheralName;
    //信号和服务
    cell.detailTextLabel.text = [NSString stringWithFormat:@"mac: %@ | RSSI:%@",mac,RSSI];
    
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
    BLEOperateViewController *vc = [[BLEOperateViewController alloc]init];
    vc.mac = [[devices objectAtIndex:indexPath.row] valueForKey:@"mac"];
    [self.navigationController pushViewController:vc animated:YES];
}

@end
