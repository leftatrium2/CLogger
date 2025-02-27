package com.ellaclub.clogger.utils;

import android.text.TextUtils;
import android.util.Log;

public class CLoggerJNIHelper {

    public static native void nativeCLoggerLoganInit(String cachePath, String dirPath, int maxFile, int maxDay, boolean isDebug, boolean loganUseFakeTime);

    public static native void nativeCLoggerSaveFileInit(String path);

    public static native void nativeCLoggerPrintInit();

    public static native void nativeCLoggerLoganDestroy();

    public static native void nativeCLoggerFileDestroy();

    public static native void nativeSaveFileEnable(boolean enable);

    public static native void nativeLoganEnable(boolean enable);

    public static native void nativeSavefileLogV(@LogType String type, String tag, String msg);

    public static native void nativeSavefileLogD(@LogType String type, String tag, String msg);

    public static native void nativeSavefileLogI(@LogType String type, String tag, String msg);

    public static native void nativeSavefileLogW(@LogType String type, String tag, String msg);

    public static native void nativeSavefileLogE(@LogType String type, String tag, String msg);

    public static native void nativeLoganLogV(@LogType String type, String tag, String msg);

    public static native void nativeLoganLogD(@LogType String type, String tag, String msg);

    public static native void nativeLoganLogI(@LogType String type, String tag, String msg);

    public static native void nativeLoganLogW(@LogType String type, String tag, String msg);

    public static native void nativeLoganLogE(@LogType String type, String tag, String msg);

    public static native void nativeLoganFlush();

    static {
        System.loadLibrary("clogger");
    }

    public static void logLoganInit(String cachePath, String dirPath, int maxFile, int maxDay, boolean isDebug, boolean loganUseFakeTime) {
        CLoggerJNIHelper.nativeCLoggerLoganInit(cachePath, dirPath, maxFile, maxDay, isDebug, loganUseFakeTime);
    }

    public static void logSaveFileInit(String path) {
        CLoggerJNIHelper.nativeCLoggerSaveFileInit(path);
    }

    public static void logPrintInit() {
        CLoggerJNIHelper.nativeCLoggerPrintInit();
    }

    public static void logLoganDestroy() {
        CLoggerJNIHelper.nativeCLoggerLoganDestroy();
    }

    public static void logSaveFileDestroy() {
        CLoggerJNIHelper.nativeCLoggerFileDestroy();
    }

    public static void savefileEnable(boolean enable) {
        CLoggerJNIHelper.nativeSaveFileEnable(enable);
    }

    public static void loganEnable(boolean enable) {
        CLoggerJNIHelper.nativeLoganEnable(enable);
    }

    private static String parse(String msg, Throwable tr) {
        StringBuilder sb = new StringBuilder();
        if (!TextUtils.isEmpty(msg)) {
            sb.append(msg);
        }
        sb.append("\n");
        if (tr != null) {
            sb.append(Log.getStackTraceString(tr));
            sb.append("\n");
        }
        return sb.toString();
    }

    public static void savefileLogV(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogV(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogD(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogD(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogI(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogI(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogW(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogW(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogE(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogE(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogV_S(@LogType String type, String tag, String msg, Throwable
            tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogV(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogD_S(@LogType String type, String tag, String msg, Throwable
            tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogD(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogI_S(@LogType String type, String tag, String msg, Throwable
            tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogI(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogW_S(@LogType String type, String tag, String msg, Throwable
            tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogW(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void savefileLogE_S(@LogType String type, String tag, String msg, Throwable
            tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeSavefileLogE(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogV(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogV(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogD(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogD(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogI(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogI(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogW(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogW(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogE(String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogE(LogType.DEBUG, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogV_S(@LogType String type, String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogV(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogD_S(@LogType String type, String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogD(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogI_S(@LogType String type, String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogI(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogW_S(@LogType String type, String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogW(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }

    public static void loganLogE_S(@LogType String type, String tag, String msg, Throwable tr) {
        if (TextUtils.isEmpty(tag)) {
            tag = "DEBUG";
        }
        CLoggerJNIHelper.nativeLoganLogE(type, tag, CLoggerJNIHelper.parse(msg, tr));
    }
}
