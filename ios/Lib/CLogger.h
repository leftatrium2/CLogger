//
//  Main entrance
//
//  Created by leftatrium on 2025/3/4.
//

#import <Foundation/Foundation.h>
#import "CLoggerConfig.h"

NS_ASSUME_NONNULL_BEGIN

@interface CLogger : NSObject
- (void) initWithConfig:(CLoggerConfig *) config;
- (void) releaseNow;
@end

NS_ASSUME_NONNULL_END
