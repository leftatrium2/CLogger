#import "AppDelegate.h"
#import "OCLogger.h"
#import "OCLoggerConfig.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void) initDir:(NSString *) path
{
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if(![fileManager fileExistsAtPath:path])
    {
        [fileManager createDirectoryAtPath:path attributes:nil];
    }
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *cachePath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *loganPath = [documentPath stringByAppendingPathComponent:@"logan"];
    NSString *savefilePath = [documentPath stringByAppendingPathComponent:@"savefile"];
    NSString *loganCachePath = [cachePath stringByAppendingPathComponent:@"logan"];
    [self initDir:loganPath];
    [self initDir:loganCachePath];
    [self initDir:savefilePath];
    NSLog(@"loganPath: %@, loganCachePath: %@, savefilePath: %@",loganPath,loganCachePath,savefilePath);
    
    CLoggerConfig *config = [[CLoggerConfig alloc] init];
    config.logan = TRUE;
    config.loganDir = loganPath;
    config.loganCache = loganCachePath;
    config.loganIsDebug = TRUE;
    config.loganUseFakeTime = TRUE;
    config.loganMaxDay = 10;
    config.loganMaxFile = 10 * 1024 * 1024;
    config.printable = TRUE;
    config.saveToDisk = TRUE;
    config.saveToDiskLog = savefilePath;
    [[CLogger shareInstance] initWithConfig:config];
    return YES;
}


#pragma mark - UISceneSession lifecycle


- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options {
    return [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
}

- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions {
}


@end
