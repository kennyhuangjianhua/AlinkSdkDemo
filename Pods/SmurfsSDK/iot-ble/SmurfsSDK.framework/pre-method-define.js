//初始化ble for js接口方法
(function(ble){
	//版本管理
	// ble.req =  ble.v01;
 
    //执行Scene的init方法，开始启动蓝牙场景
    ble.enter = function(){
         ble.request({
                     "cmd":"enter",
                     "args":{
                     },
                     "cb":{}
                     });
         return ble;
    }
 
    //结束蓝牙操作场景
    ble.exit = function(){
         ble.request({
                     "cmd":"exit",
                     "args":{
                     },
                     "cb":{}
                     });
         return ble;
     }

	//执行命令方法
	ble.connect = function(){
		ble.request({
			"cmd":"connect",
			"args":{
			},
			"cb":{}
		});
		return ble;
	}

	//写的方法，成功收到回应
	ble.write = function(uuid,data){
		ble.request({
			"cmd":"write",
			"args":{
				uuid:uuid,
				data:data
			},
			"cb":{}
		});
		return ble;
	}

	//写的方法,没有回应
	ble.pass = function(uuid,data){
		ble.request({
			"cmd":"pass",
			"args":{
				uuid:uuid,
				data:data
			},
			"cb":{}
		});
		return ble;
	}

	//读的方法
	ble.read = function(uuid){
		ble.request({
			"cmd":"read",
			"args":{
				uuid:uuid
			},
			"cb":{}
		});
		return ble;
	}

	//订阅的方法
	ble.notify = function(uuid){
		ble.request({
			"cmd":"notify",
			"args":{
				uuid:uuid
			},
			"cb":{}
		});
		return ble;
	}

	//取消订阅的方法
	ble.stopNotity = function(uuid){
		ble.request({
			"cmd":"stopNotify",
			"args":{
				uuid:uuid
			},
			"cb":{}
		});
		return ble;
	}

	//deug 
	ble.debug = {};
	ble.debug.bleInfo = function(){
		ble.request({
			"cmd":"debug",
			"args":{
				data:"bleInfo"
			},
			"cb":{}
		});
	}
	ble.debug.peripheralInfo = function(){
		ble.request({
			"cmd":"debug",
			"args":{
				data:"peripheralInfo"
			},
			"cb":{}
		});
	}
});

