#include <jni.h>
#include <android/looper.h>
#include <string.h>
#include <stddef.h>
#include "clogger_const.h"
#include "clogger_platform.h"
#include "clogger_android_string.h"
#include "clogger_jni.h"
#include "clogger_print.h"
#include "clogger_utils.h"

int is_main_thread(void)
{
    JNIEnv *env = snlogger_attach_env();
    // Thread.currentThread().getId()
    jclass a_thread_cls = (*env)->FindClass(env, "java/lang/Thread");
    jmethodID a_currentThread_id = (*env)->GetStaticMethodID(env, a_thread_cls, "currentThread", "()Ljava/lang/Thread;");
    jobject a_currentThread_obj = (*env)->CallStaticObjectMethod(env, a_thread_cls, a_currentThread_id);
    jmethodID a_getId_id = (*env)->GetMethodID(env, a_thread_cls, "getId", "()J");
    jlong a_currentThread_get_id = (*env)->CallLongMethod(env, a_currentThread_obj, a_getId_id);
    // Looper.getMainLooper().getThread().getId()
    jclass b_looper_cls = (*env)->FindClass(env, "android/os/Looper");
    jmethodID b_getMainLooper_id = (*env)->GetStaticMethodID(env, b_looper_cls, "getMainLooper", "()Landroid/os/Looper;");
    jobject b_getMainLooper_obj = (*env)->CallStaticObjectMethod(env, b_looper_cls, b_getMainLooper_id);
    jclass b_thread_cls = (*env)->FindClass(env, "java/lang/Thread");
    jmethodID b_getThread_id = (*env)->GetMethodID(env, b_looper_cls, "getThread", "()Ljava/lang/Thread;");
    jobject b_getThread_obj = (*env)->CallObjectMethod(env, b_getMainLooper_obj, b_getThread_id);
    jmethodID b_getId_id = (*env)->GetMethodID(env, b_thread_cls, "getId", "()J");
    jlong b_getid_obj = (*env)->CallLongMethod(env, b_getThread_obj, b_getId_id);
    // release
    (*env)->DeleteLocalRef(env, a_thread_cls);
    (*env)->DeleteLocalRef(env, a_currentThread_obj);
    (*env)->DeleteLocalRef(env, b_looper_cls);
    (*env)->DeleteLocalRef(env, b_getMainLooper_obj);
    (*env)->DeleteLocalRef(env, b_thread_cls);
    (*env)->DeleteLocalRef(env, b_getThread_obj);
    return a_currentThread_get_id == b_getid_obj;
}

static jclass g_stat_cls;
static jmethodID g_stat_construct_id;
static jmethodID g_get_block_size_id;
static jmethodID g_get_available_block_id;

int is_can_write_sdcard(const char *path)
{
    if (path == NULL)
    {
        clogger_internal_e("is_sdcard_can_write,the path is NULL");
        return 0;
    }
    JNIEnv *env = snlogger_attach_env();
    /*
    StatFs stat = new StatFs(this.mPath);
            long blockSize = (long)stat.getBlockSize();
            long availableBlocks = (long)stat.getAvailableBlocks();
            long total = availableBlocks * blockSize;
            if (total > this.mMinSDCard) {
                item = true;
            }
    */
    int len = strlen(path);
    if (len == 0)
    {
        clogger_internal_e("the path is empty!");
        return 0;
    }
    jstring str_path = clogger_string_to_jstring(env, path);
    if (g_stat_cls == NULL)
    {
        g_stat_cls = (*env)->FindClass(env, "android/os/StatFs");
    }
    if (g_stat_construct_id == NULL)
    {
        g_stat_construct_id = (*env)->GetMethodID(env, g_stat_cls, "<init>", "(Ljava/lang/String;)V");
    }
    jobject stat_obj = (*env)->NewObject(env, g_stat_cls, g_stat_construct_id, str_path);
    if (g_get_block_size_id == NULL)
    {
        g_get_block_size_id = (*env)->GetMethodID(env, g_stat_cls, "getBlockSize", "()I");
    }
    jlong block_size = (jlong)(*env)->CallIntMethod(env, stat_obj, g_get_block_size_id);
    if (g_get_available_block_id == NULL)
    {
        g_get_available_block_id = (*env)->GetMethodID(env, g_stat_cls, "getAvailableBlocks", "()I");
    }
    jlong available_block_size = (jlong)(*env)->CallIntMethod(env, stat_obj, g_get_available_block_id);
    long long total_size = available_block_size * block_size;
    clogger_internal_e("is_sdcard_can_write,total_size:%lld,MIN_SDCARD:%d", total_size, MIN_SDCARD);
    // release
    (*env)->DeleteLocalRef(env, stat_obj);
    (*env)->DeleteLocalRef(env, str_path);
    return (total_size > MIN_SDCARD);
}