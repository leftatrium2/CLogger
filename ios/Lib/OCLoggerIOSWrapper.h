#import <Foundation/Foundation.h>
#import "OCLogger.h"

NS_ASSUME_NONNULL_BEGIN
@interface CLoggerIOSWrapper : NSObject

+ (instancetype) shareInstance;

- (void) savefileLogV:(id<T>)tag msg:(NSString *) msg;
- (void) savefileLogD:(id<T>)tag msg:(NSString *) msg;
- (void) savefileLogI:(id<T>)tag msg:(NSString *) msg;
- (void) savefileLogW:(id<T>)tag msg:(NSString *) msg;
- (void) savefileLogE:(id<T>)tag msg:(NSString *) msg;


- (void) loganLogV:(id<T>)tag msg:(NSString *) msg;
- (void) loganLogD:(id<T>)tag msg:(NSString *) msg;
- (void) loganLogI:(id<T>)tag msg:(NSString *) msg;
- (void) loganLogW:(id<T>)tag msg:(NSString *) msg;
- (void) loganLogE:(id<T>)tag msg:(NSString *) msg;

@end
NS_ASSUME_NONNULL_END
