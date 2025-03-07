#import "LoganLogImpl.h"
#import "clogger_ref.h"
#import "clogger.h"
#import "clogger_logan.h"
#import "CLoggerIOSUtils.h"

@interface LoganLogImpl()

@property (nonatomic,assign) BOOL isEnable;

@end

@implementation LoganLogImpl

- (BOOL)enable
{
    return TRUE;
}

- (void) setEnable:(BOOL) isEnable
{
    self.isEnable = isEnable;
}

- (void) onLog:(id<T>)tag level:(CLoggerLevel) level message:(NSString *) message exception:(NSException *) exception
{
    NSMutableString *messStr = [NSMutableString string];
    if(exception)
    {
        [messStr appendFormat:@"%@,%@",message,exception.reason];
        
    }else{
        [messStr appendFormat:@"%@",message];
    }
    NSString *str = [NSString stringWithFormat:@"%s",LOGTYPE_DEBUG];
    switch (level) {
        case Verbose:
            clogger_logan_logv(create_ios_ref([str UTF8String], Verbose, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
            
        case Debug:
            clogger_logan_logd(create_ios_ref([str UTF8String], Debug, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
            
        case Info:
            clogger_logan_logi(create_ios_ref([str UTF8String], Info, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
        
        case Warn:
            clogger_logan_logw(create_ios_ref([str UTF8String], Warn, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
        
        case Error:
            clogger_logan_loge(create_ios_ref([str UTF8String], Error, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
        case Crash:
            clogger_logan_loge(create_ios_ref([str UTF8String], Crash, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
        case Wtf:
            clogger_logan_loge(create_ios_ref([str UTF8String], Wtf, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
            
        default:
            break;
    }
}

@end
