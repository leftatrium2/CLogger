//
//  Main entrance
//
//  Created by leftatrium on 2025/3/4.
//

#import <Foundation/Foundation.h>
#import "OCLoggerConfig.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum _CLoggerLevel
{
    Verbose=0,
    Debug,
    Info,
    Warn,
    Error,
    Crash,
    Wtf
} CLoggerLevel;

@protocol T <NSObject>

- (NSString *) tag;

@end

@protocol ICLogger <NSObject>

- (BOOL) enable;
- (void) onLog:(id<T>)tag level:(CLoggerLevel) level message:(NSString *) message exception:(NSException *) exception;

@end

@protocol LogExecute <NSObject>

- (void) execute:(id<ICLogger>) log tag:(id<T>) tag content:(NSString *) content exception:(NSException *) exception;

@end

@interface CLogger : NSObject
+ (instancetype) shareInstance;
- (void) initWithConfig:(CLoggerConfig *) config;
- (instancetype) init NS_UNAVAILABLE;
- (void) releaseNow;

- (void) debug:(NSString *) message;
- (void) debug:(NSString *) tag message:(NSString *) message;
- (void) debug:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception;

- (void) info:(NSString *) message;
- (void) info:(NSString *) tag message:(NSString *) message;
- (void) info:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception;

- (void) verbose:(NSString *) message;
- (void) verbose:(NSString *) tag message:(NSString *) message;
- (void) verbose:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception;

- (void) warn:(NSString *) message;
- (void) warn:(NSString *) tag message:(NSString *) message;
- (void) warn:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception;

- (void) error:(NSString *) message;
- (void) error:(NSString *) tag message:(NSString *) message;
- (void) error:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception;

- (void) crash:(NSString *) message;
- (void) crash:(NSString *) tag message:(NSString *) message;
- (void) crash:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception;

- (void) wtf:(NSString *) message;
- (void) wtf:(NSString *) tag message:(NSString *) message;
- (void) wtf:(id<T>) tag message:(NSString *) message exception:(NSException *__nullable) exception;
@end

NS_ASSUME_NONNULL_END
