Pod::Spec.new do |s|
	s.authors =  'alink'
  	s.homepage = 'http://yun.taobao.com'
  	s.summary = 's.name'
  	s.source = { 'path' => s.name }
	s.name = File.basename(__FILE__,".*")
	s.version  = '1.0.208'
	s.description = 'OpenSSL 本地镜像，加速打包'
	s.platform     =  :ios, '8.0'
	s.requires_arc = true
	#s.vendored_frameworks = "#{s.name}/*.framework"
	s.vendored_libraries = "#{s.name}/**/*.a"
	s.source_files = "#{s.name}/**/*.h"
end
