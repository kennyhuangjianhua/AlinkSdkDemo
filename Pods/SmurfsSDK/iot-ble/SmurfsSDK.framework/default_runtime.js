
/*
	//js runtime script，作用是
	优点：
	1：可以规范蓝牙行为
	2：逻辑清晰
	3：安全性
	4：动态性（动态修改业务逻辑，填平版本差异）
	5：动态扩充api功能 connect`write`read`notify`原子自由组合
 */
(function(ble,runtime){
 
 //example
	// runtime.fetchHistory = function(){
	//     ble.write("fff2","aGVs")
	// };
 // runtime.startClean = function(){
 // 	ble.write("fff1","MTA=")
 // }
 // runtime.getBatteryLevel = function(){
 // ble.write("fff1","NDN2")
 // }
 // runtime.spotClean = function(){
 // 	ble.write("fff1","AC16")
 // }
 // runtime.getRobotRegistered = function(){
 // 	ble.write("fff1","#34=")
 // }
 });

