#import "SaveFileLogImpl.h"
#import "clogger_ref.h"
#import "clogger.h"
#import "clogger_savefile.h"
#import "CLoggerIOSUtils.h"

@interface SaveFileLogImpl()

@property (nonatomic,assign) BOOL isEnable;

@end

@implementation SaveFileLogImpl

- (instancetype)init
{
    self.isEnable = FALSE;
    return [super init];
}

- (void) setEnable:(BOOL) isEnable
{
    self.isEnable = isEnable;
}


- (BOOL) enable
{
    return self.isEnable;
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
            clogger_savefile_logv(create_ios_ref([str UTF8String], Verbose, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
            
        case Debug:
            clogger_savefile_logd(create_ios_ref([str UTF8String], Debug, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
            
        case Info:
            clogger_savefile_logi(create_ios_ref([str UTF8String], Info, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
        
        case Warn:
            clogger_savefile_logw(create_ios_ref([str UTF8String], Warn, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
        
        case Error:
            clogger_savefile_loge(create_ios_ref([str UTF8String], Error, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
        case Crash:
            clogger_savefile_loge(create_ios_ref([str UTF8String], Crash, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
        case Wtf:
            clogger_savefile_loge(create_ios_ref([str UTF8String], Wtf, [[tag tag] UTF8String], [messStr UTF8String]));
            break;
            
        default:
            break;
    }
}

@end
