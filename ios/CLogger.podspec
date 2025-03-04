Pod::Spec.new do |s|
  s.name             = 'CLogger'
  s.version          = '1.0.0'
  s.summary          = 'CLogger'

  s.description      = <<-DESC
                       CLogger
                       DESC

  s.homepage         = 'https://github.com/leftatrium2/CLogger'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'leftatrium' => 'leftatrium@vip.qq.com' }
  s.source           = { :git => 'git@github.com:leftatrium2/CLogger.git', :tag => s.version.to_s }

  s.ios.deployment_target = '8.0'
  s.vendored_frameworks = 'SNLogger/Frameworks/*.framework'


  s.source_files = 'CLoggerDemo/Classes/**/*'
  s.swift_version = '5.0'
end
