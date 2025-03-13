Pod::Spec.new do |s|
  s.name             = 'CLogger'
  s.version          = '1.0.0'
  s.summary          = 'a Mobile NDK General Logging Library'

  s.description      = <<-DESC
                       a Mobile NDK General Logging Library
                       DESC

  s.homepage         = 'https://github.com/leftatrium2/CLogger'
  s.license          = 'MIT'
  s.author           = { 'leftatrium' => 'leftatrium@vip.qq.com' }
  s.source           = { :git => 'https://github.com/leftatrium2/CLogger.git', :tag => "v1.0.0" }
  s.vendored_frameworks = 'SNLogger/Frameworks/*.framework'
  s.requires_arc = true


  s.source_files = 'ios/Lib/**/*'
  user_header_paths = [
		'${PODS_ROOT}/CLogger/3rd/mbedtls/include',
		'${PODS_ROOT}/CLogger/3rd/Clogan',
		'${PODS_ROOT}/CLogger/include',
  ]
  s.pod_target_xcconfig = { 'USER_HEADER_SEARCH_PATHS' => user_header_paths.join(' ') }
  s.ios.deployment_target = '9.0'
end
