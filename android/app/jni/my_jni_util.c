#include <android/log.h>
#include "my_jni_util.h"

#define TAG "MyJNI"

jstring get_application_path(JNIEnv *env)
{
    jclass activityThread = (*env)->FindClass(env, "android/app/ActivityThread");
    jmethodID currentActivityThread = (*env)->GetStaticMethodID(env, activityThread, "currentActivityThread", "()Landroid/app/ActivityThread;");
    jobject at = (*env)->CallStaticObjectMethod(env, activityThread, currentActivityThread);
    //获取Application，也就是全局的Context
    jmethodID getApplication = (*env)->GetMethodID(env, activityThread, "getApplication", "()Landroid/app/Application;");
    jobject context = (*env)->CallObjectMethod(env, at, getApplication);
    //获取getApplicationInfo
    jclass ContextWrapper = (*env)->FindClass(env, "android/content/ContextWrapper");
    jmethodID getApplicationInfo = (*env)->GetMethodID(env, ContextWrapper, "getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;");
    jobject applicationInfo = (*env)->CallObjectMethod(env, context, getApplicationInfo);
    //获取nativeLibraryDir
    jclass ApplicationInfo = (*env)->FindClass(env, "android/content/pm/ApplicationInfo");
    jfieldID nativeLibraryDirID = (*env)->GetFieldID(env, ApplicationInfo, "nativeLibraryDir", "Ljava/lang/String;");
    jstring nativeLibraryDir = (jstring)(*env)->GetObjectField(env, applicationInfo, nativeLibraryDirID);
    //销毁
    (*env)->DeleteLocalRef(env, activityThread);
    (*env)->DeleteLocalRef(env, at);
    (*env)->DeleteLocalRef(env, context);
    (*env)->DeleteLocalRef(env, ContextWrapper);
    (*env)->DeleteLocalRef(env, applicationInfo);
    (*env)->DeleteLocalRef(env, ApplicationInfo);
    return nativeLibraryDir;
}