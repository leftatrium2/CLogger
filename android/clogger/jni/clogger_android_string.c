#include "clogger_android_string.h"

char *clogger_jstring_to_string(JNIEnv *env, jstring jstr)
{
	if (NULL == jstr)
		return NULL;
	char *rtn = NULL;
	static jmethodID mid = NULL;

	jstring strencode = (*env)->NewStringUTF(env, "utf-8");

	if (NULL == mid)
	{
		jclass j_string = (*env)->FindClass(env, "java/lang/String");
		if (NULL == j_string)
		{
			return NULL;
		}
		mid = (*env)->GetMethodID(env, j_string, "getBytes", "(Ljava/lang/String;)[B");
		if (mid == NULL)
			return NULL;
	}

	jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode);
	(*env)->DeleteLocalRef(env, strencode);
	if (NULL == barr)
		return NULL;
	jsize alen = (*env)->GetArrayLength(env, barr);
	jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = (char *)malloc(alen + 1);
		if (!rtn)
			return rtn;
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	(*env)->ReleaseByteArrayElements(env, barr, ba, 0);
	(*env)->DeleteLocalRef(env, barr);
	return rtn;
}

jstring clogger_string_to_jstring(JNIEnv *env, const char *str)
{
	jclass strClass = (*env)->FindClass(env, "java/lang/String");
	jmethodID ctorID = (*env)->GetMethodID(env, strClass, "<init>", "([BLjava/lang/String;)V");
	int str_len = strlen(str);
	jbyteArray bytes = (*env)->NewByteArray(env, str_len);
	(*env)->SetByteArrayRegion(env, bytes, 0, str_len, (jbyte *)str);
	jstring encoding = (*env)->NewStringUTF(env, "utf-8");
	jstring ret = (jstring)(*env)->NewObject(env, strClass, ctorID, bytes, encoding);
	(*env)->DeleteLocalRef(env, encoding);
	(*env)->DeleteLocalRef(env, bytes);
	(*env)->DeleteLocalRef(env, strClass);
	return ret;
}
