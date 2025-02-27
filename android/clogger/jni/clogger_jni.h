#ifndef _SNLOGGER_JNI_H_
#define _SNLOGGER_JNI_H_

#include <jni.h>

typedef struct
{
    JavaVM *vm;
} snlogger_jni_data_t;

JNIEnv *snlogger_attach_env();

#endif