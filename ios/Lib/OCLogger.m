#import "OCLogger.h"
#import "OCLoggerConfig.h"
#import "impl/PrintLogImpl.h"
#import "impl/LoganLogImpl.h"
#import "impl/SaveFileLogImpl.h"
#import "clogger.h"
#import "clogger_print.h"
#import "clogger_savefile.h"
#import "clogger_logan.h"

#define CLOGGER_PRINTABLE_KEY @"CLOGGER_PRINTABLE"
#define CLOGGER_SAVEFILE_KEY @"CLOGGER_SAVEFILE"
#define CLOGGER_LOGAN_KEY @"CLOGGER_LOGAN"



@interface CLoggerSDKT : NSObject<T>

@end

@implementation CLoggerSDKT

- (NSString *) tag
{
    return @"CODE";
}

@end

@interface LogExecuteD : NSObject<LogExecute>

@end

@implementation LogExecuteD

- (void) execute:(id<ICLogger>) log tag:(id<T>) tag content:(NSString *) content exception:(NSException *) exception
{
    [log onLog:tag level:Debug message:content exception:exception];
}

@end

@interface LogExecuteI : NSObject<LogExecute>

@end

@implementation LogExecuteI

- (void) execute:(id<ICLogger>) log tag:(id<T>) tag content:(NSString *) content exception:(NSException *) exception
{
    [log onLog:tag level:Info message:content exception:exception];
}

@end

@interface LogExecuteV : NSObject<LogExecute>

@end

@implementation LogExecuteV

- (void) execute:(id<ICLogger>) log tag:(id<T>) tag content:(NSString *) content exception:(NSException *) exception
{
    [log onLog:tag level:Verbose message:content exception:exception];
}

@end

@interface LogExecuteW : NSObject<LogExecute>

@end

@implementation LogExecuteW

- (void) execute:(id<ICLogger>) log tag:(id<T>) tag content:(NSString *) content exception:(NSException *) exception
{
    [log onLog:tag level:Warn message:content exception:exception];
}

@end

@interface LogExecuteE : NSObject<LogExecute>

@end

@implementation LogExecuteE

- (void) execute:(id<ICLogger>) log tag:(id<T>) tag content:(NSString *) content exception:(NSException *) exception
{
    [log onLog:tag level:Error message:content exception:exception];
}

@end

@interface LogExecuteCrash : NSObject<LogExecute>

@end

@implementation LogExecuteCrash

- (void) execute:(id<ICLogger>) log tag:(id<T>) tag content:(NSString *) content exception:(NSException *) exception
{
    [log onLog:tag level:Crash message:content exception:exception];
}

@end

@interface LogExecuteWtf: NSObject<LogExecute>

@end

@implementation LogExecuteWtf

- (void) execute:(id<ICLogger>) log tag:(id<T>) tag content:(NSString *) content exception:(NSException *) exception
{
    [log onLog:tag level:Wtf message:content exception:exception];
}

@end

@interface CLogger()

@property (nonatomic,strong) CLoggerConfig *config;

@property (nonatomic,strong) PrintLogImpl *printLogImpl;
@property (nonatomic,strong) SaveFileLogImpl *saveFileLogImpl;
@property (nonatomic,strong) LoganLogImpl *loganLogImpl;

@property (nonatomic,strong) NSMutableDictionary *cLoggerInstanceDict;

@property (nonatomic,strong) LogExecuteD *logExecuteD;
@property (nonatomic,strong) LogExecuteI *logExecuteI;
@property (nonatomic,strong) LogExecuteV *logExecuteV;
@property (nonatomic,strong) LogExecuteW *logExecuteW;
@property (nonatomic,strong) LogExecuteE *logExecuteE;
@property (nonatomic,strong) LogExecuteCrash *logExecuteCrash;
@property (nonatomic,strong) LogExecuteWtf *logExecuteWtf;

@end

@implementation CLogger

static CLogger *_sharedInstance = nil;

+ (instancetype) shareInstance
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedInstance = [[self alloc] init];
    });
    return _sharedInstance;
}

- (void) initWithConfig:(CLoggerConfig *) config
{
    
    self.isLogan = FALSE;
    self.isSaveFile = FALSE;
    self.isPrintable = TRUE;
    
    self.printLogImpl = [[PrintLogImpl alloc] init];
    self.saveFileLogImpl = [[SaveFileLogImpl alloc] init];
    self.loganLogImpl = [[LoganLogImpl alloc] init];
    
    self.logExecuteD = [[LogExecuteD alloc] init];
    self.logExecuteI = [[LogExecuteI alloc] init];
    self.logExecuteV = [[LogExecuteV alloc] init];
    self.logExecuteW = [[LogExecuteW alloc] init];
    self.logExecuteE = [[LogExecuteE alloc] init];
    self.logExecuteCrash = [[LogExecuteCrash alloc] init];
    self.logExecuteWtf = [[LogExecuteWtf alloc] init];
    
    self.cLoggerInstanceDict = [NSMutableDictionary dictionaryWithCapacity:1];
    if(config == nil){
        return;
    }
    self.config = config;
    clogger_init();
    [self initPrintable:self.config];
    [self initSaveDisk:self.config];
    [self initLogan:self.config];
}

- (void) initLogan:(CLoggerConfig *) config
{
    if(config)
    {
        self.isLogan = config.logan;
        [self.loganLogImpl setEnable:self.isLogan];
        if(self.isLogan)
        {
            [self addLogImpl:CLOGGER_LOGAN_KEY log:self.loganLogImpl];
            const char *dir_path = [config.loganDir UTF8String];
            const char *cache_path = [config.loganCache UTF8String];
            int max_file = config.loganMaxFile;
            int max_day = config.loganMaxDay;
            BOOL use_fake_time = config.loganUseFakeTime;
            BOOL is_debug = config.loganIsDebug;
            clogger_logan_init(cache_path, dir_path, max_file, max_day, is_debug, use_fake_time);
        }
    }
}

- (void) initSaveDisk:(CLoggerConfig *) config
{
    if(config)
    {
        self.isSaveFile = config.saveToDisk;
        [self.saveFileLogImpl setEnable:self.isSaveFile];
        if(self.isSaveFile)
        {
            [self addLogImpl:CLOGGER_SAVEFILE_KEY log:self.saveFileLogImpl];
            const char *save_path = [config.saveToDiskLog UTF8String];
            clogger_savefile_init(save_path);
        }
    }
}

- (void) initPrintable:(CLoggerConfig *) config
{
    if(config)
    {
        self.isPrintable = config.printable;
        [self.printLogImpl setEnable:self.isPrintable];
        if(self.isPrintable)
        {
            [self addLogImpl:CLOGGER_PRINTABLE_KEY log:self.printLogImpl];
            clogger_print_init();
        }
    }
}

- (void) addLogImpl:(NSString *)key log:(id<ICLogger>) log
{
    if(log)
    {
        [self.cLoggerInstanceDict setValue:log forKey:key];
    }
}

- (void) releaseNow
{
    
}

- (void) log:(id<LogExecute>)logExecute tag:(id<T>) tag message:(NSString *) message exception:(NSException *) exception
{
    if(!logExecute)
    {
        return;
    }
    if(!self.cLoggerInstanceDict)
    {
        return;
    }
    for (id key in self.cLoggerInstanceDict)
    {
        id<ICLogger> log = [self.cLoggerInstanceDict valueForKey:key];
        if(!log || !log.enable)
        {
            continue;
        }
        [logExecute execute:log tag:tag content:message exception:exception];
    }
}


- (void) debug:(NSString *) message
{
    [self debug:[[CLoggerSDKT alloc] init] message:message exception:nil];
}

- (void) debug:(id<T>) tag message:(NSString *) message
{
    [self debug:tag message:message exception:nil];
}

- (void) debug:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception;
{
    [self log:self.logExecuteD tag:tag message:message exception:exception];
}

- (void) info:(NSString *) message
{
    [self info:[[CLoggerSDKT alloc] init] message:message exception:nil];
}
- (void) info:(id<T>) tag message:(NSString *) message
{
    [self info:tag message:message exception:nil];
}

- (void) info:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception
{
    [self log:self.logExecuteI tag:tag message:message exception:exception];
}

- (void) verbose:(NSString *) message
{
    [self verbose:[[CLoggerSDKT alloc] init] message:message exception:nil];
}
- (void) verbose:(id<T>) tag message:(NSString *) message
{
    [self verbose:tag message:message exception:nil];
}

- (void) verbose:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception
{
    [self log:self.logExecuteV tag:tag message:message exception:exception];
}

- (void) warn:(NSString *) message
{
    [self warn:[[CLoggerSDKT alloc] init] message:message exception:nil];
}

- (void) warn:(id<T>) tag message:(NSString *) message
{
    [self warn:tag message:message exception:nil];
}

- (void) warn:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception
{
    [self log:self.logExecuteW tag:tag message:message exception:exception];
}

- (void) error:(NSString *) message
{
    [self error:[[CLoggerSDKT alloc] init] message:message exception:nil];
}
- (void) error:(id<T>) tag message:(NSString *) message
{
    [self error:tag message:message exception:nil];
}

- (void) error:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception
{
    [self log:self.logExecuteE tag:tag message:message exception:exception];
}

- (void) crash:(NSString *) message
{
    [self crash:[[CLoggerSDKT alloc] init] message:message exception:nil];
}
- (void) crash:(id<T>) tag message:(NSString *) message
{
    [self crash:tag message:message exception:nil];
}

- (void) crash:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception
{
    [self log:self.logExecuteCrash tag:tag message:message exception:exception];
}

- (void) wtf:(NSString *) message
{
    [self wtf:[[CLoggerSDKT alloc] init] message:message exception:nil];
}
- (void) wtf:(id<T>) tag message:(NSString *) message
{
    [self wtf:tag message:message exception:nil];
}

- (void) wtf:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception
{
    [self log:self.logExecuteWtf tag:tag message:message exception:exception];
}

@end
