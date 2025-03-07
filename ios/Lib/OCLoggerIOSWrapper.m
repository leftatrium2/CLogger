//
//  ios implementation of clogger
//

#import <Foundation/Foundation.h>
#import <stdarg.h>
#import <string.h>
#import "clogger.h"
#import "clogger_print.h"
#import "clogger_platform.h"
#import "clogger_const.h"
#import "clogger_print.h"
#import "clogger_ref.h"

#define CLOGGER_INTERNAL_TAG "CLOGGER"

int is_main_thread(void)
{
    BOOL isMainThread = [[NSThread currentThread] isMainThread];
    return isMainThread?1:0;
}

int is_can_write_sdcard(const char *path)
{
    int64_t freeSize = 0;
    NSURL *fileUrl = [NSURL fileURLWithPath:NSHomeDirectory()];
    if(@available(iOS 11.0,*)){
        NSDictionary *spaceDict = [fileUrl resourceValuesForKeys:@[NSURLVolumeAvailableCapacityForImportantUsageKey] error:nil];
        freeSize = [spaceDict[NSURLVolumeAvailableCapacityForImportantUsageKey] longLongValue];
    }else{
        NSError *err = nil;
        NSDictionary *attrs = [[NSFileManager defaultManager] attributesOfFileSystemForPath:NSHomeDirectory() error:&err];
        if(err) return -1;
        freeSize = [[attrs objectForKey:NSFileSystemFreeSize] longLongValue];
    }
    
    return freeSize>MIN_SDCARD;
}

void clogger_internal_e(const char *fmt, ...)
{
#ifdef DEBUG
    va_list ap;
    va_start(ap, fmt);
    char buf[CLOGGER_SIZE];
    vsnprintf(buf, CLOGGER_SIZE-1, fmt, ap);
    NSLog(@"%s",buf);
    va_end(ap);
#endif
}

void clogger_print_logv(const clogger_ref *ref)
{
    NSLog(@"VERBOSE\t%s\t%s",ref->tag,ref->log);
}

void clogger_print_logd(const clogger_ref *ref)
{
    NSLog(@"DEBUG\t%s\t%s",ref->tag,ref->log);
}

void clogger_print_logi(const clogger_ref *ref)
{
    NSLog(@"INFO\t%s\t%s",ref->tag,ref->log);
}

void clogger_print_logw(const clogger_ref *ref)
{
    NSLog(@"WARN\t%s\t%s",ref->tag,ref->log);
}

void clogger_print_loge(const clogger_ref *ref)
{
    NSLog(@"ERROR\t%s\t%s",ref->tag,ref->log);
}

void clogger_print_init(void)
{
    callback_list[PRINT_INDEX].verbose_callback = clogger_print_logv;
    callback_list[PRINT_INDEX].debug_callback = clogger_print_logd;
    callback_list[PRINT_INDEX].info_callback = clogger_print_logi;
    callback_list[PRINT_INDEX].warning_callback = clogger_print_logw;
    callback_list[PRINT_INDEX].error_callback = clogger_print_loge;
}
