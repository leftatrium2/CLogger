#include <stdio.h>
#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <dlfcn.h>
#include "clogger.h"
#include "my_jni_util.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define NATIVE_PATH_LEN 20
#define TAG "MyJNI"

    static void *_fp;
    static void (*func)(const char *src_type, int level, const char *src_tag, const char *fmt);
    static char *_c_path;

    static void call_log(const char *src_type, int level, const char *src_tag, const char *msg)
    {
        if (!_fp)
        {
            _fp = dlopen(_c_path, RTLD_NOW);
            if (!_fp)
            {
                __android_log_print(ANDROID_LOG_ERROR, TAG, "dlopen error, error no:%s", dlerror());
                return;
            }
            func = dlsym(_fp, "clogger_log");
            const char *err_msg = dlerror();
            if (!err_msg)
            {
                __android_log_print(ANDROID_LOG_ERROR, TAG, "dlopen error, msg:%s", err_msg);
                return;
            }
        }
        func(src_type, level, src_tag, msg);
    }

    static void clogger_debug(const char *tag, const char *msg)
    {
        call_log(CLOGGER_TYPE, CLOGGER_LEVEL_DEBUG, tag, msg);
    }

    static void clogger_info(const char *tag, const char *msg)
    {
        call_log(CLOGGER_TYPE, CLOGGER_LEVEL_INFO, tag, msg);
    }

    static void clogger_verbose(const char *tag, const char *msg)
    {
        call_log(CLOGGER_TYPE, CLOGGER_LEVEL_VERBOSE, tag, msg);
    }

    static void clogger_warning(const char *tag, const char *msg)
    {
        call_log(CLOGGER_TYPE, CLOGGER_LEVEL_WARNING, tag, msg);
    }

    static void clogger_error(const char *tag, const char *msg)
    {
        call_log(CLOGGER_TYPE, CLOGGER_LEVEL_ERROR, tag, msg);
    }

    static void clogger_wtf(const char *tag, const char *msg)
    {
        call_log(CLOGGER_TYPE, CLOGGER_LEVEL_WTF, tag, msg);
    }

    JNIEXPORT void JNICALL Java_com_ellaclub_clogger_MyJNI_testPrint(JNIEnv *env, jobject thiz)
    {
        jstring path = get_application_path(env);
        const char *dir_path = (*env)->GetStringUTFChars(env, path, 0);
        int len = strlen(dir_path) + NATIVE_PATH_LEN;
        _c_path = malloc(len);
        memset(_c_path, 0, len);
        snprintf(_c_path, len - 1, "%s/libclogger.so", dir_path);
        clogger_debug(TAG, "hello debug log!");
        clogger_info(TAG, "hello info log!");
        clogger_verbose(TAG, "hello verbose log!");
        clogger_warning(TAG, "hello warning log!");
        clogger_error(TAG, "hello error log!");
        clogger_wtf(TAG, "hello wtf log!");
        (*env)->ReleaseStringUTFChars(env, path, dir_path);
        (*env)->DeleteLocalRef(env, path);
        free(_c_path);
        _c_path = NULL;
    }

#ifdef __cplusplus
}
#endif