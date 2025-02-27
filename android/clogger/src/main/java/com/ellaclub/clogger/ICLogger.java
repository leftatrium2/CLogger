package com.ellaclub.clogger;


import com.ellaclub.clogger.utils.CLoggerMethodInfo;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;


public interface ICLogger {
    /**
     * 设置什么情况下可用
     *
     * @return true&false
     */
    boolean enable();

    /**
     * 日志记录
     *
     * @param tag        enum T或者继承类
     * @param logLevel   enum CLoggerLevel
     * @param message    message
     * @param tr         Throwable,传递异常信息
     * @param methodInfo cls跟踪类
     */
    void onLog(T tag, CLoggerLevel logLevel, @NonNull String message, @Nullable Throwable tr, @Nullable CLoggerMethodInfo methodInfo);
}
