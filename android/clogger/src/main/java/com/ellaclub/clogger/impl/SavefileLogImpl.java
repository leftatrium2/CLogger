package com.ellaclub.clogger.impl;

import com.ellaclub.clogger.ICLogger;
import com.ellaclub.clogger.CLoggerLevel;
import com.ellaclub.clogger.T;
import com.ellaclub.clogger.utils.CLoggerJNIHelper;
import com.ellaclub.clogger.utils.CLoggerMethodInfo;
import com.ellaclub.clogger.utils.CLoggerUtils;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class SavefileLogImpl implements ICLogger {
    private boolean isEnable = false;

    @Override
    public boolean enable() {
        return isEnable;
    }

    public void setEnable(boolean isEnable) {
        this.isEnable = isEnable;
        CLoggerJNIHelper.savefileEnable(isEnable);
    }

    @Override
    public void onLog(T tag, CLoggerLevel logLevel, @NonNull String message, @Nullable Throwable tr, @Nullable CLoggerMethodInfo methodInfo) {
        switch (logLevel) {
            case v:
                CLoggerJNIHelper.savefileLogV(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case d:
                CLoggerJNIHelper.savefileLogD(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case i:
                CLoggerJNIHelper.savefileLogI(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case w:
                CLoggerJNIHelper.savefileLogW(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case e:
            case crash:
            case wtf:
                CLoggerJNIHelper.savefileLogE(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
        }
    }
}
