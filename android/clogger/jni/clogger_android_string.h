#ifndef _CLOGGER_ANDROID_STRING_H_
#define _CLOGGER_ANDROID_STRING_H_
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
char *clogger_jstring_to_string(JNIEnv *env, jstring jstr);
jstring clogger_string_to_jstring(JNIEnv *env, const char *str);
#endif