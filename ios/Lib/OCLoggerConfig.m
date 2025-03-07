#import "OCLoggerConfig.h"

@interface CLoggerConfig()

@end

@implementation CLoggerConfig

- (instancetype)init
{
    self.logan = FALSE;
    self.loganMaxDay = 10;
    self.loganMaxDay = 10 * 1024 * 1024;
    self.loganIsDebug = FALSE;
    self.loganUseFakeTime = FALSE;

    self.printable = TRUE;
    
    self.saveToDisk = FALSE;
    
    return [super init];
}

@end
