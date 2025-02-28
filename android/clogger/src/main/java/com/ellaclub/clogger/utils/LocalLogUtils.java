package com.ellaclub.clogger.utils;

import android.content.Context;
import android.os.Environment;
import android.util.Log;

import com.ellaclub.clogger.CLogger;

import java.io.File;

public class LocalLogUtils {

    public static final String LOG_SEGMENT_DEFAULT = "__d__";
    private static File saveFileDirectory = null;
    private static File loganDirectory = null;

    public static File getSaveFileLogDirectory(Context context) {
        if (null == saveFileDirectory) {
            synchronized (CLogger.class) {
                if (null == saveFileDirectory) {
                    try {
                        if (Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState())) {
                            if (context != null) {
                                // TODO: 2018/7/17 这个需要合并到FileUtil中，做统一目录处理，也存在比如SD卡禁用后无法存储等问题
                                saveFileDirectory = context.getExternalFilesDir(".log");
                                Log.d(LOG_SEGMENT_DEFAULT, "sLogDirectory:" + saveFileDirectory);
                            }
                        } else {
                            Log.e(LOG_SEGMENT_DEFAULT, "sdcard not mounted");
                        }
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }

                }
            }
        }
        return saveFileDirectory;
    }

    public static File getLoganDirectory(Context context) {
        if (null == loganDirectory) {
            synchronized (CLogger.class) {
                if (null == loganDirectory) {
                    try {
                        if (Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState())) {
                            if (context != null) {
                                // TODO: 2018/7/17 这个需要合并到FileUtil中，做统一目录处理，也存在比如SD卡禁用后无法存储等问题
                                loganDirectory = context.getExternalFilesDir("clogger");
                                Log.d(LOG_SEGMENT_DEFAULT, "sLoganDirectory:" + loganDirectory);
                            }
                        } else {
                            Log.e(LOG_SEGMENT_DEFAULT, "sdcard not mounted");
                        }
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }

                }
            }
        }
        return loganDirectory;
    }
}
