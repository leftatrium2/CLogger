package com.ellaclub.clogger.utils;


import com.ellaclub.clogger.CLogger;
import com.ellaclub.clogger.T;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;


public class CLoggerUtils {
    public static String parseContent(@NonNull String content, @Nullable CLoggerMethodInfo methodInfo) {
        if (methodInfo != null) {
            return "[" +
                    Thread.currentThread().getId() +
                    "](" +
                    methodInfo.clsName +
                    ":" +
                    methodInfo.lineNumber +
                    ")" +
                    methodInfo.methodName +
                    ": " +
                    content;
        }
        return content;
    }

    public static String parseTAG(T appTag) {
        return CLogger.TAG + "::" + appTag.toString();
    }
}
