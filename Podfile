source 'https://github.com/CocoaPods/Specs.git'
source 'https://github.com/aliyun/aliyun-specs.git'
source 'http://repo.baichuan-ios.taobao.com/baichuanSDK/AliBCSpecs.git'

target "AlinkDemo" do
    # OpenSDK
    # 必选，账号&连接SDK及依赖库
    pod 'AlinkSDK', '~> 1.0.1'
    pod 'mtop', '2.0.3'
    pod 'BCUserTrack', '5.2.0.1-appkeys'
    pod 'SGSecurityBody', '5.1.29'
    pod 'Reachability', '3.2'
    #pod 'OpenSSL', '1.0.208'
    pod 'OpenSSL', :path => 'LocalPods/OpenSSL.podspec'  #Local镜像(1.0.208)，加速打包

    # 可选，百川OpenAccount账号SDK
    pod 'ALBBOpenAccountSDK','2.5.0.1'

    # 可选，蓝牙SDK
    pod 'SmurfsSDK', '~> 1.0.0'

    # 可选，Bone开发框架及依赖库
    pod 'BoneKit', '~> 1.0.1'
    if !ENV['USE_RN_RELEASE']
        #默认使用Debug版本，方便开发调试，上线前请记得切换成release版本
        pod 'AKReactNative', '0.41.2-debug'
    else
        #想使用Release版本， env USE_RN_RELEASE=1 pod update
        pod 'AKReactNative', '~> 0.41.2'
    end
    pod 'CocoaAsyncSocket', '7.4.3'
    pod 'GHKit', '2.0.3'
    pod 'MJRefresh', '3.1.12'
    pod 'HexColors', '4.0.0'
    pod 'ZipArchive', '1.4.0'
    pod 'NSURL+QueryDictionary', '1.1.0'

    # 可选，APNS推送
    pod 'AKAgooPush', '~> 1.0.0'
    pod 'NetworkSDK', '~> 6.0.0.22'

    # 可选，Debug面板及依赖库
    pod 'AKDebugDashboard', '~> 0.0.1'
    pod 'CocoaLumberjack', '2.2.0'

    # 仅Demo使用到的外部依赖
    pod 'LBXScan/LBXNative','2.0'
    pod 'LBXScan/UI','2.0'
end
