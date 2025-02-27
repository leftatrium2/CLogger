package com.ellaclub.clogger.impl;

import android.util.Log;

import com.ellaclub.clogger.ICLogger;
import com.ellaclub.clogger.CLoggerLevel;
import com.ellaclub.clogger.T;
import com.ellaclub.clogger.utils.CLoggerMethodInfo;
import com.ellaclub.clogger.utils.CLoggerUtils;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;


/**
 * Created by dongfang5 on 2019/7/26
 * <p>
 * 控制台打印log
 */

public class PrintLogImpl implements ICLogger {
    private boolean isEnable = false;

    @Override
    public boolean enable() {
        return isEnable;
    }

    public void setEnable(boolean isEnable) {
        this.isEnable = isEnable;
    }

    @Override
    public void onLog(T tag, CLoggerLevel logLevel, @NonNull String message, @Nullable Throwable tr, @Nullable CLoggerMethodInfo methodInfo) {
        switch (logLevel) {
            case v:
                Log.v(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case d:
                Log.d(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case i:
                Log.i(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case w:
                Log.w(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
            case e:
            case crash:
            case wtf:
                Log.e(CLoggerUtils.parseTAG(tag), CLoggerUtils.parseContent(message, methodInfo), tr);
                break;
        }
    }
}
