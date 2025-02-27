package com.ellaclub.clogger.impl;

import com.ellaclub.clogger.ICLogger;
import com.ellaclub.clogger.CLoggerLevel;
import com.ellaclub.clogger.T;
import com.ellaclub.clogger.utils.CLoggerJNIHelper;
import com.ellaclub.clogger.utils.CLoggerMethodInfo;
import com.ellaclub.clogger.utils.CLoggerUtils;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class LoganLogImpl implements ICLogger {
    private boolean isEnable = false;

    @Override
    public boolean enable() {
        return isEnable;
    }


    public void setEnable(boolean isEnable) {
        this.isEnable = isEnable;
        CLoggerJNIHelper.loganEnable(isEnable);
    }

    @Override
    public void onLog(T tag, CLoggerLevel logLevel, @NonNull String message, @Nullable Throwable tr, @Nullable CLoggerMethodInfo methodInfo) {
        switch (logLevel) {
            case v:
                CLoggerJNIHelper.loganLogV(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case d:
                CLoggerJNIHelper.loganLogD(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case i:
                CLoggerJNIHelper.loganLogI(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case w:
                CLoggerJNIHelper.loganLogW(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case e:
            case crash:
            case wtf:
                CLoggerJNIHelper.loganLogE(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
        }
    }
}
