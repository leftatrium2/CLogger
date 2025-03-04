package com.ellaclub.clogger_demo

import android.app.Application
import com.ellaclub.clogger.CLogger
import com.ellaclub.clogger.CLoggerConfig

class MyApplication : Application() {
    override fun onCreate() {
        super.onCreate()
        val builder = CLoggerConfig.builder()
            .printable(true)
            .logan(true)
            .saveToDisk(true)
            .ismethodinfo(true)
            .loganUseFakeTime(true)
            .loganIsDebug(true)
            .build()
        CLogger.init(this, builder)
    }
}