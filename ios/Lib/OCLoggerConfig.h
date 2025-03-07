//
//  CLogger Config Class
//
//  Created by xiao sun on 2025/3/4.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CLoggerConfig : NSObject

@property (nonatomic,assign) BOOL saveToDisk;
@property (nonatomic,strong) NSString *saveToDiskLog;
@property (nonatomic,assign) BOOL logan;
@property (nonatomic,strong) NSString *loganCache;
@property (nonatomic,strong) NSString *loganDir;
@property (nonatomic,assign) int loganMaxFile;
@property (nonatomic,assign) int loganMaxDay;
@property (nonatomic,assign) BOOL loganUseFakeTime;
@property (nonatomic,assign) BOOL loganIsDebug;
@property (nonatomic,assign) BOOL printable;

@end

NS_ASSUME_NONNULL_END
