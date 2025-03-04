#import "CLogger.h"
#import "CLoggerConfig.h"

@interface CLogger()

@property (nonatomic,strong) CLoggerConfig *config;

@end

@implementation CLogger

- (void) initWithConfig:(CLoggerConfig *) config
{
    if(config == nil){
        return;
    }
    self.config = config;
}

- (void) releaseNow
{
    
}

@end
