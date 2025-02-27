package com.ellaclub.clogger_demo;

import android.app.Application;

import com.ellaclub.clogger.CLogger;
import com.ellaclub.clogger.CLoggerConfig;

public class MyApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        CLoggerConfig.Builder builder = new CLoggerConfig.Builder();
        builder.logan(true);
        builder.printable(true);
        builder.saveToDisk(true);
        builder.ismethodinfo(true);
        builder.loganUseFakeTime(true);
        builder.loganIsDebug(true);
        CLogger.init(this, builder.build());
    }
}
