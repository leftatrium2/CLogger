Pod::Spec.new do |s|
  s.name             = 'CLogger'
  s.version          = '1.0.0'
  s.summary          = 'a Mobile NDK General Logging Library'

  s.description      = <<-DESC
                       CLogger
                       DESC

  s.homepage         = 'https://github.com/leftatrium2/CLogger'
  s.license          = 'MIT'
  s.author           = { 'leftatrium' => 'leftatrium@vip.qq.com' }
  s.source           = { :git => 'git@github.com:leftatrium2/CLogger.git', :tag => s.version.to_s }

  s.ios.deployment_target = '9.0'
  s.vendored_frameworks = 'SNLogger/Frameworks/*.framework'
  s.requires_arc = true


  s.source_files = 'Lib/**/*'
end
