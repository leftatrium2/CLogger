//
//  LoganLogImpl.h
//  CLoggerDemo
//
//  Created by xiao sun on 2025/3/5.
//

#import <Foundation/Foundation.h>
#import "OCLogger.h"

NS_ASSUME_NONNULL_BEGIN

@interface LoganLogImpl : NSObject<ICLogger>

- (void) setEnable:(BOOL) isEnable;

@end

NS_ASSUME_NONNULL_END
