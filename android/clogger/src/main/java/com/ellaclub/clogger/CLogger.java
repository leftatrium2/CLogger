package com.ellaclub.clogger;


import android.content.Context;
import android.util.Log;

import com.ellaclub.clogger.impl.LoganLogImpl;
import com.ellaclub.clogger.impl.PrintLogImpl;
import com.ellaclub.clogger.impl.SavefileLogImpl;
import com.ellaclub.clogger.utils.LocalLogUtils;
import com.ellaclub.clogger.utils.CLoggerJNIHelper;
import com.ellaclub.clogger.utils.CLoggerMethodInfo;
import com.ellaclub.clogger.utils.CLoggerSDKT;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * main entrance
 */
public class CLogger {
    public final static String TAG = "CLOGGER";

    private static List<ICLogger> cLoggerInstanceList = Collections.synchronizedList(new ArrayList<ICLogger>());

    private static LogExecute sLogExeI, sLogExeD, sLogExeV, sLogExeW, sLogExeE, sLogExeCrash, sLogExeWTF;

    private static boolean isMethodInfo = true;

    public static void setIsMethodInfo(boolean isMethodInfo) {
        CLogger.isMethodInfo = isMethodInfo;
    }

    public static void setPrintable(boolean isPrintable) {
        CLogger.isPrintable = isPrintable;
    }

    public static void setSaveToDisk(boolean isSaveFile) {
        CLogger.isSaveFile = isSaveFile;
        if (CLogger.savefileLog != null) {
            CLogger.savefileLog.setEnable(isSaveFile);
        }
    }

    public static void setLogan(boolean isLogan) {
        CLogger.isLogan = isSaveFile;
        if (CLogger.loganLog != null) {
            CLogger.loganLog.setEnable(isLogan);
        }
    }

    private static boolean isLogan = false;
    private static boolean isSaveFile = false;
    private static boolean isPrintable = false;
    private static PrintLogImpl printLog;
    private static SavefileLogImpl savefileLog;
    private static LoganLogImpl loganLog;

    public static void init(Context context, CLoggerConfig config) {
        isSaveFile = config.isSaveToDisk();
        File saveFilePath = config.getSaveToDiskLog();
        if (saveFilePath == null || !saveFilePath.exists()) {
            Log.e("CLOGGER", "saveFilePath is null or saveFilePath is not exists!");
            saveFilePath = LocalLogUtils.getSaveFileLogDirectory(context);
        }
        if (isSaveFile) {
            savefileLog = new SavefileLogImpl();
            savefileLog.setEnable(true);
            addLogImpl(savefileLog);
            CLoggerJNIHelper.logSaveFileInit(saveFilePath.getAbsolutePath());
        }
        isLogan = config.isLogan();
        File loganCache = config.getLoganCache();
        if (loganCache == null || !loganCache.exists()) {
            Log.e("CLOGGER", "loganFilePath is null or loganFilePath is not exists!");
            loganCache = context.getFilesDir().getAbsoluteFile();
        }
        File loganDir = config.getLoganDir();
        if (loganDir == null || !loganDir.exists()) {
            Log.e("CLOGGER", "loganDir is null or loganFilePath is not exists!");
            loganDir = LocalLogUtils.getLoganDirectory(context);
        }
        int maxFile = config.getLoganMaxFile();
        int maxDay = config.getLoganMaxDay();
        setIsMethodInfo(config.ismethodinfo());
        boolean isDebug = config.getLoganIsDebug();
        boolean loganUseFakeTime = config.loganUseFakeTime();
        if (isLogan) {
            loganLog = new LoganLogImpl();
            loganLog.setEnable(true);
            addLogImpl(loganLog);
            CLoggerJNIHelper.logLoganInit(loganCache.getAbsolutePath(), loganDir.getAbsolutePath(), maxFile, maxDay, isDebug, loganUseFakeTime);
        }
        isPrintable = config.isPrintable();
        if (isPrintable) {
            printLog = new PrintLogImpl();
            printLog.setEnable(isPrintable);
            addLogImpl(printLog);
            CLoggerJNIHelper.logPrintInit();
        }

        sLogExeD = new LogExecute() {
            @Override
            public void execute(ICLogger log, T tag, Throwable tr, String content, CLoggerMethodInfo info) {
                if (info == null && isMethodInfo) {
                    info = CLoggerMethodInfo.methodInfo();
                }
                log.onLog(tag, CLoggerLevel.d, content, tr, info);
            }
        };
        sLogExeI = new LogExecute() {
            @Override
            public void execute(ICLogger log, T tag, Throwable tr, String content, CLoggerMethodInfo info) {
                if (info == null && isMethodInfo) {
                    info = CLoggerMethodInfo.methodInfo();
                }
                log.onLog(tag, CLoggerLevel.i, content, tr, info);
            }
        };
        sLogExeV = new LogExecute() {
            @Override
            public void execute(ICLogger log, T tag, Throwable tr, String content, CLoggerMethodInfo info) {
                if (info == null && isMethodInfo) {
                    info = CLoggerMethodInfo.methodInfo();
                }
                log.onLog(tag, CLoggerLevel.v, content, tr, info);
            }
        };
        sLogExeW = new LogExecute() {
            @Override
            public void execute(ICLogger log, T tag, Throwable tr, String content, CLoggerMethodInfo info) {
                if (info == null && isMethodInfo) {
                    info = CLoggerMethodInfo.methodInfo();
                }
                log.onLog(tag, CLoggerLevel.w, content, tr, info);
            }
        };
        sLogExeE = new LogExecute() {
            @Override
            public void execute(ICLogger log, T tag, Throwable tr, String content, CLoggerMethodInfo info) {
                if (info == null && isMethodInfo) {
                    info = CLoggerMethodInfo.methodInfo();
                }
                log.onLog(tag, CLoggerLevel.e, content, tr, info);
            }
        };
        sLogExeCrash = new LogExecute() {
            @Override
            public void execute(ICLogger log, T tag, Throwable tr, String content, CLoggerMethodInfo info) {
                if (info == null) {
                    //在crash以及WTF情况下，不管是否打开ismethodinfo，都默认上报当前class信息
                    info = CLoggerMethodInfo.methodInfo();
                }
                log.onLog(tag, CLoggerLevel.crash, content, tr, info);
            }
        };
        sLogExeWTF = new LogExecute() {
            @Override
            public void execute(ICLogger log, T tag, Throwable tr, String content, CLoggerMethodInfo info) {
                if (info == null) {
                    //在crash以及WTF情况下，不管是否打开ismethodinfo，都默认上报当前class信息
                    info = CLoggerMethodInfo.methodInfo();
                }
                log.onLog(tag, CLoggerLevel.wtf, content, tr, info);
            }
        };
    }

    public static void destroy() {
        if (isLogan) {
            CLoggerJNIHelper.logLoganDestroy();
        }
        if (isSaveFile) {
            CLoggerJNIHelper.logSaveFileDestroy();
        }
    }

    //**********************debug级别log日志************************
    @Deprecated
    public static void d(String content) {
        log(sLogExeD, CLoggerSDKT.CODE, null, content, null);
    }

    @Deprecated
    public static void d(String tag, String content) {
        log(sLogExeD, CLoggerSDKT.CODE, null, content, null);
    }

    public static void d(T tag, String content) {
        log(sLogExeD, tag, null, content, null);
    }

    public static void d(T tag, Throwable tr, String content) {
        log(sLogExeD, tag, tr, content, null);
    }

    public static void d(T tag, String content, String clsName, int lineNumber, String methodName) {
        log(sLogExeD, tag, null, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    public static void d(T tag, Throwable tr, String content, String clsName, int lineNumber, String methodName) {
        log(sLogExeD, tag, tr, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    //**********************info级别log日志*************************
    @Deprecated
    public static void i(String content) {
        log(sLogExeI, CLoggerSDKT.CODE, null, content, null);
    }

    @Deprecated
    public static void i(String tag, String content) {
        log(sLogExeI, CLoggerSDKT.CODE, null, content, null);
    }

    public static void i(T tag, String content) {
        log(sLogExeI, tag, null, content, null);
    }

    public static void i(T tag, Throwable tr, String content) {
        log(sLogExeI, tag, tr, content, null);
    }

    public static void i(T tag, String content, String clsName, int lineNumber, String methodName) {
        log(sLogExeI, tag, null, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    public static void i(T tag, Throwable tr, String content, String clsName, int lineNumber, String methodName) {
        log(sLogExeI, tag, tr, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    //*********************verbose级别log日志***********************
    @Deprecated
    public static void v(String content) {
        log(sLogExeV, CLoggerSDKT.CODE, null, content, null);
    }

    @Deprecated
    public static void v(String tag, String content) {
        log(sLogExeV, CLoggerSDKT.CODE, null, content, null);
    }

    public static void v(T tag, String content) {
        log(sLogExeV, tag, null, content, null);
    }

    public static void v(T tag, Throwable tr, String content) {
        log(sLogExeV, tag, tr, content, null);
    }

    public static void v(T tag, String content, String clsName, int lineNumber, String methodName) {
        log(sLogExeV, tag, null, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    public static void v(T tag, Throwable tr, String content, String clsName, int lineNumber, String methodName) {
        log(sLogExeV, tag, tr, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    //**********************warn级别log日志*************************
    @Deprecated
    public static void w(String content) {
        log(sLogExeW, CLoggerSDKT.CODE, null, content, null);
    }

    @Deprecated
    public static void w(final Throwable tr, String content) {
        log(sLogExeW, CLoggerSDKT.CODE, null, content, null);
    }

    @Deprecated
    public static void w(String tag, final Throwable tr, String content) {
        log(sLogExeW, CLoggerSDKT.CODE, tr, content, null);
    }

    public static void w(T tag, String content) {
        log(sLogExeW, tag, null, content, null);
    }

    public static void w(T tag, final Throwable tr, String content) {
        log(sLogExeW, tag, tr, content, null);
    }

    public static void w(T tag, String content, String clsName, int lineNumber, String methodName) {
        log(sLogExeW, tag, null, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    public static void w(T tag, final Throwable tr, String content, String clsName, int lineNumber, String methodName) {
        log(sLogExeW, tag, tr, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    //***********************error级别日志**************************
    @Deprecated
    public static void e(String content) {
        log(sLogExeE, CLoggerSDKT.CODE, null, content, null);
    }

    @Deprecated
    public static void e(final Throwable tr, String content) {
        log(sLogExeE, CLoggerSDKT.CODE, null, content, null);
    }

    @Deprecated
    public static void e(String tag, final Throwable tr, String content) {
        log(sLogExeE, CLoggerSDKT.CODE, tr, content, null);
    }

    public static void e(T tag, String content) {
        log(sLogExeE, tag, null, content, null);
    }

    public static void e(T tag, final Throwable tr, String content) {
        log(sLogExeE, tag, tr, content, null);
    }

    public static void e(T tag, String content, String clsName, int lineNumber, String
            methodName) {
        log(sLogExeE, tag, null, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    public static void e(T tag, final Throwable tr, String content, String clsName,
                         int lineNumber, String methodName) {
        log(sLogExeE, tag, tr, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    //***********************crash异常日志**************************
    @Deprecated
    public static void crash(String tag, final Throwable tr, String content) {
        log(sLogExeCrash, CLoggerSDKT.CODE, null, content, null);
    }

    public static void crash(T tag, String content) {
        log(sLogExeCrash, tag, null, content, null);
    }

    public static void crash(T tag, final Throwable tr) {
        log(sLogExeCrash, tag, tr, "", null);
    }

    public static void crash(T tag, final Throwable tr, String content) {
        log(sLogExeCrash, tag, tr, content, null);
    }

    public static void crash(T tag, String content, String clsName, int lineNumber, String
            methodName) {
        log(sLogExeCrash, tag, null, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    public static void crash(T tag, final Throwable tr, String clsName, int lineNumber, String
            methodName) {
        log(sLogExeCrash, tag, tr, "", new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    public static void crash(T tag, final Throwable tr, String content, String clsName,
                             int lineNumber, String methodName) {
        log(sLogExeCrash, tag, tr, content, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    //***********************非常严重级别，需要上报到code中**************************
    public static void wtf(T tag, String msg) {
        log(sLogExeWTF, tag, null, msg, null);
    }

    public static void wtf(T tag, final Throwable tr, String msg) {
        log(sLogExeWTF, tag, tr, msg, null);
    }

    public static void wtf(T tag, String msg, String clsName, int lineNumber, String methodName) {
        log(sLogExeWTF, tag, null, msg, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    public static void wtf(T tag, final Throwable tr, String msg, String clsName,
                           int lineNumber, String methodName) {
        log(sLogExeWTF, tag, tr, msg, new CLoggerMethodInfo(clsName, lineNumber, methodName));
    }

    //***********************内部方法**************************
    private static void log(LogExecute logExecute, T tag, Throwable tr, String
            content, CLoggerMethodInfo info) {
        try {
            if (logExecute == null) {
                return;
            }
            if (cLoggerInstanceList == null || cLoggerInstanceList.isEmpty()) {
                return;
            }
            for (ICLogger log : cLoggerInstanceList) {
                if (log == null || !log.enable()) {
                    continue;
                }
                logExecute.execute(log, tag, tr, content, info);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public interface LogExecute {
        void execute(ICLogger log, T tag, Throwable tr, String content, CLoggerMethodInfo info);
    }

    public static void addLogImpl(ICLogger log) {
        if (log != null) {
            cLoggerInstanceList.add(log);
        }
    }

}
