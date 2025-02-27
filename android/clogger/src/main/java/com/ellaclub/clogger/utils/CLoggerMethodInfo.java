package com.ellaclub.clogger.utils;


import android.text.TextUtils;

import com.ellaclub.clogger.CLogger;

import androidx.annotation.Nullable;

public class CLoggerMethodInfo {
    public String clsName = "<unknown>";
    public int lineNumber = 0;
    public String methodName = "<unknown>";

    /**
     * dont use this constructor
     */
    private CLoggerMethodInfo() {

    }

    public CLoggerMethodInfo(String clsName, int lineNumber, String methodName) {
        this.clsName = clsName;
        this.lineNumber = lineNumber;
        this.methodName = methodName;
    }

    @Nullable
    public static CLoggerMethodInfo methodInfo() {
        return methodInfo(CLogger.class);
    }

    @Nullable
    public static CLoggerMethodInfo methodInfo(Class cls) {
        StackTraceElement[] trace = new Throwable().fillInStackTrace().getStackTrace();

        CLoggerMethodInfo info = new CLoggerMethodInfo();
        boolean isCLogger = false;
        for (int i = 1; i < trace.length; i++) {
            if (trace[i].getClassName().equals(CLogger.class.getName())) {
                isCLogger = true;
            }
            if (isCLogger && !trace[i].getClassName().equals(CLogger.class.getName())) {
                String callingClass = trace[i].getClassName();
                callingClass = callingClass.substring(callingClass.lastIndexOf('.') + 1);
                if (!TextUtils.isEmpty(callingClass) && callingClass.contains("$")) {
                    callingClass = callingClass.substring(0, callingClass.indexOf("$"));
                }
                // make the link which could press
                info.clsName = callingClass + ".java";
                info.lineNumber = trace[i].getLineNumber();
                info.methodName = trace[i].getMethodName();
                break;
            }
        }
        return info;
    }
}
