#import "PrintLogImpl.h"
#import "clogger_print.h"
#import "clogger_ref.h"

@interface PrintLogImpl()

@property (nonatomic,assign) BOOL isEnable;

@end

@implementation PrintLogImpl

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
    NSMutableString *str = [NSMutableString string];
    if(exception)
    {
        [str appendFormat:@"%@,%@",message,exception.reason];
        
    }else{
        [str appendFormat:@"%@",message];
    }
    switch (level) {
        case Verbose:
            NSLog(@"VERBOSE\t%@\t%@",[tag tag],str);
            break;
        case Debug:
            NSLog(@"DEBUG\t%@\t%@",[tag tag],str);
            break;
        case Info:
            NSLog(@"INFO\t%@\t%@",[tag tag],str);
            break;
        case Warn:
            NSLog(@"WARN\t%@\t%@",[tag tag],str);
            break;
        case Error:
            NSLog(@"ERROR\t%@\t%@",[tag tag],str);
            break;
        case Crash:
            NSLog(@"CRASH\t%@\t%@",[tag tag],str);
            break;
        case Wtf:
            NSLog(@"WTF\t%@\t%@",[tag tag],str);
            break;
        default:
            break;
    }
}

@end
