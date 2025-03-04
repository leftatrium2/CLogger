#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>
#include <jni.h>
#include <android/log.h>
#include "clogger.h"
#include "clogger_android_string.h"
#include "clogger_print.h"
#include "clogger_logan.h"
#include "clogger_savefile.h"
#include "clogger_message_queue.h"
#include "clogger_jni.h"
#include "clogger_ref.h"

#define CLASS_CLOGGER_JNI_HELPER "com/ellaclub/clogger/utils/CLoggerJNIHelper"
#define ARRAY_SIZEOF(a) (sizeof(a) / sizeof(a[0]))

snlogger_jni_data_t jni_ctx;

clogger_ref *create_logan_ref(const char *type, int level, const char *tag, const char *log)
{
    int tag_len = strlen(tag) + 1;
    char *tag_copy = malloc(tag_len);
    memset(tag_copy, 0, tag_len);
    strcpy(tag_copy, tag);

    int log_len = strlen(log) + 1;
    char *log_copy = malloc(log_len);
    memset(log_copy, 0, log_len);
    strcpy(log_copy, log);

    int type_len = strlen(type) + 1;
    char *type_copy = malloc(type_len);
    memset(type_copy, 0, type_len);
    strcpy(type_copy, type);

    return clogger_ref_create(type_copy, level, tag_copy, log_copy, free_log_ref);
}

static void jni_clogger_logan_init(JNIEnv *env, jobject thiz, jstring cachePath, jstring dirPath, jint maxFile, jint maxDay, jboolean isDebug, jboolean loganUseFakeTime)
{
    clogger_internal_e("jni_clogger_logan_init start...\n");
    const char *c_logan_cache_path = (*env)->GetStringUTFChars(env, cachePath, 0);
    clogger_internal_e("jni_clogger_logan_init cache path: %s\n", c_logan_cache_path);
    const char *c_logan_dir_path = (*env)->GetStringUTFChars(env, dirPath, 0);
    clogger_internal_e("jni_clogger_logan_init file path: %s\n", c_logan_dir_path);
    int max_file = (int)maxFile;
    clogger_internal_e("jni_clogger_logan_init maxFile: %d\n", max_file);
    int max_day = (int)maxDay;
    clogger_internal_e("jni_clogger_logan_init maxDay: %d\n", max_day);
    int is_debug = isDebug == JNI_TRUE ? 1 : 0;
    clogger_internal_e("jni_clogger_logan_init is_debug: %d\n", is_debug);
    int use_faketime = loganUseFakeTime == JNI_TRUE ? 1 : 0;
    clogger_internal_e("jni_clogger_logan_init use_faketime: %d\n", use_faketime);
    clogger_logan_init(c_logan_cache_path, c_logan_dir_path, max_file, max_day, is_debug, use_faketime);
    (*env)->ReleaseStringUTFChars(env, cachePath, c_logan_cache_path);
    (*env)->ReleaseStringUTFChars(env, dirPath, c_logan_dir_path);
}

static void jni_clogger_savefile_init(JNIEnv *env, jobject thiz, jstring path)
{
    clogger_internal_e("jni_clogger_savefile_init start...\n");
    jboolean isCopy = JNI_TRUE;
    const char *c_savefile_path = (*env)->GetStringUTFChars(env, path, &isCopy);
    clogger_internal_e("jni_clogger_savefile_init log path: %s\n", c_savefile_path);
    clogger_savefile_init(c_savefile_path);
    (*env)->ReleaseStringUTFChars(env, path, c_savefile_path);
}

static void jni_clogger_print_init(JNIEnv *env, jobject thiz)
{
    clogger_print_init();
}

static void jni_savefile_log_v(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *log_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("savefile log verbose: [%s] %s\n", tag_str, log_str);
    clogger_ref *ref = create_logan_ref(CLOGGER_TYPE_DEBUG, CLOGGER_LEVEL_VERBOSE, tag_str, log_str);
    clogger_savefile_logv(ref);
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, log_str);
}

static void jni_savefile_log_d(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *log_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("savefile log debug: [%s] %s\n", tag_str, log_str);
    clogger_ref *ref = create_logan_ref(CLOGGER_TYPE_DEBUG, CLOGGER_LEVEL_DEBUG, tag_str, log_str);
    clogger_savefile_logd(ref);
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, log_str);
}

static void jni_savefile_log_i(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *log_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("savefile log info: [%s] %s\n", tag_str, log_str);
    clogger_ref *ref = create_logan_ref(CLOGGER_TYPE_DEBUG, CLOGGER_LEVEL_INFO, tag_str, log_str);
    clogger_savefile_logi(ref);
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, log_str);
}

static void jni_savefile_log_w(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *log_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("savefile log warning: [%s] %s\n", tag_str, log_str);
    clogger_ref *ref = create_logan_ref(CLOGGER_TYPE_DEBUG, CLOGGER_LEVEL_WARNING, tag_str, log_str);
    clogger_savefile_logw(ref);
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, log_str);
}

static void jni_savefile_log_e(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *log_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("savefile log error: [%s] %s\n", tag_str, log_str);
    clogger_ref *ref = create_logan_ref(CLOGGER_TYPE_DEBUG, CLOGGER_LEVEL_ERROR, tag_str, log_str);
    clogger_savefile_loge(ref);
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, log_str);
}

static void jni_logan_log_v(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *type_str = (*env)->GetStringUTFChars(env, type, 0);
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *fmt_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("logan s_log verbose: [%s] %s\n", tag_str, fmt_str);
    clogger_logan_logv(create_logan_ref(type_str, CLOGGER_LEVEL_VERBOSE, tag_str, fmt_str));
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, fmt_str);
}

static void jni_logan_log_i(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *type_str = (*env)->GetStringUTFChars(env, type, 0);
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *fmt_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("logan s_log info: [%s] %s\n", tag_str, fmt_str);
    clogger_logan_logv(create_logan_ref(type_str, CLOGGER_LEVEL_INFO, tag_str, fmt_str));
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, fmt_str);
}

static void jni_logan_log_d(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *type_str = (*env)->GetStringUTFChars(env, type, 0);
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *fmt_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("logan s_log debug: [%s] %s\n", tag_str, fmt_str);
    clogger_logan_logd(create_logan_ref(type_str, CLOGGER_LEVEL_DEBUG, tag_str, fmt_str));
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, fmt_str);
}

static void jni_logan_log_w(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *type_str = (*env)->GetStringUTFChars(env, type, 0);
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *fmt_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("logan s_log warning: [%s] %s\n", tag_str, fmt_str);
    clogger_logan_logw(create_logan_ref(type_str, CLOGGER_LEVEL_WARNING, tag_str, fmt_str));
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, fmt_str);
}

static void jni_logan_log_e(JNIEnv *env, jobject thiz, jstring type, jstring tag, jstring msg)
{
    const char *type_str = (*env)->GetStringUTFChars(env, type, 0);
    const char *tag_str = (*env)->GetStringUTFChars(env, tag, 0);
    const char *fmt_str = (*env)->GetStringUTFChars(env, msg, 0);
    clogger_internal_e("logan s_log error: [%s] %s\n", tag_str, fmt_str);
    clogger_logan_loge(create_logan_ref(type_str, CLOGGER_LEVEL_ERROR, tag_str, fmt_str));
    (*env)->ReleaseStringUTFChars(env, tag, tag_str);
    (*env)->ReleaseStringUTFChars(env, msg, fmt_str);
}

static void jni_clogger_logan_destroy(JNIEnv *env, jobject thiz)
{
    clogger_logan_destroy();
}

static void jni_clogger_savefile_destroy(JNIEnv *env, jobject thiz)
{
    clogger_savefile_destroy();
}

static void jni_logan_flush(JNIEnv *env, jobject thiz)
{
    clogger_logan_flush();
}

static void jni_savefile_enable(JNIEnv *env, jobject thiz, jboolean enable)
{
    int savefile_enable = enable == JNI_TRUE ? 1 : 0;
    clogger_internal_e("jni_savefile_enable enable:%d", savefile_enable);
    clogger_savefile_enable(savefile_enable);
}

static void jni_logan_enable(JNIEnv *env, jobject thiz, jboolean enable)
{
    int logan_enable = enable == JNI_TRUE ? 1 : 0;
    clogger_internal_e("jni_logan_enable enable:%d", logan_enable);
    clogger_logan_enable(logan_enable);
}

static JNINativeMethod methods_clogger[] = {
    {"nativeCLoggerLoganDestroy", "()V", (void *)jni_clogger_logan_destroy},
    {"nativeCLoggerFileDestroy", "()V", (void *)jni_clogger_savefile_destroy},
    {"nativeCLoggerLoganInit", "(Ljava/lang/String;Ljava/lang/String;IIZZ)V", (void *)jni_clogger_logan_init},
    {"nativeCLoggerSaveFileInit", "(Ljava/lang/String;)V", (void *)jni_clogger_savefile_init},
    {"nativeCLoggerPrintInit", "()V", (void *)jni_clogger_print_init},
    {"nativeLoganFlush", "()V", (void *)jni_logan_flush},
    {"nativeSaveFileEnable", "(Z)V", (void *)jni_savefile_enable},
    {"nativeSavefileLogV", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_savefile_log_v},
    {"nativeSavefileLogD", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_savefile_log_d},
    {"nativeSavefileLogI", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_savefile_log_i},
    {"nativeSavefileLogW", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_savefile_log_w},
    {"nativeSavefileLogE", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_savefile_log_e},
    {"nativeLoganLogV", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_logan_log_v},
    {"nativeLoganLogD", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_logan_log_d},
    {"nativeLoganLogI", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_logan_log_i},
    {"nativeLoganLogW", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_logan_log_w},
    {"nativeLoganLogE", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *)jni_logan_log_e},
    {"nativeLoganEnable", "(Z)V", (void *)jni_logan_enable}};

JNIEnv *snlogger_attach_env()
{
    int status;
    JNIEnv *env = NULL;
    status = (*jni_ctx.vm)->GetEnv(jni_ctx.vm, (void **)&env, JNI_VERSION_1_4);
    if (status < 0)
    {
        status = (*jni_ctx.vm)->AttachCurrentThread(jni_ctx.vm, &env, NULL);
        if (status < 0)
        {
            return NULL;
        }
    }
    return env;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    int ret = 0;
    JNIEnv *env;
    if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_4) != JNI_OK)
    {
        return JNI_ERR;
    }
    jni_ctx.vm = vm;

    (*env)->PushLocalFrame(env, 128);
    jclass cls_clogger_jni_helper = (*env)->FindClass(env, CLASS_CLOGGER_JNI_HELPER);
    if (!cls_clogger_jni_helper)
    {
        clogger_internal_e("1");
        goto ON_LOAD_ERROR;
    }
    ret = (*env)->RegisterNatives(env, cls_clogger_jni_helper, methods_clogger, ARRAY_SIZEOF(methods_clogger));
    if (ret < 0)
    {
        clogger_internal_e("2,ret=%d", ret);
        goto ON_LOAD_ERROR;
    }
    (*env)->NewGlobalRef(env, cls_clogger_jni_helper);
    clogger_init();
    (*env)->PopLocalFrame(env, 0);
    return JNI_VERSION_1_4;
ON_LOAD_ERROR:
    (*env)->PopLocalFrame(env, 0);
    return JNI_ERR;
}

void JNI_OnUnload(JavaVM *vm, void *reserved)
{
    clogger_savefile_destroy();
    clogger_logan_destroy();
}