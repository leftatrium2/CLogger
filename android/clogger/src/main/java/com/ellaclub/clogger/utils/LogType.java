package com.ellaclub.clogger.utils;


import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

import androidx.annotation.StringDef;

@StringDef({
        LogType.APACHE,
        LogType.BIZ_SIMA,
        LogType.APM,
        LogType.LIFECYCLE,
        LogType.DEBUG,
        LogType.API,
})
@Retention(RetentionPolicy.SOURCE)
public @interface LogType {
    String APACHE = "APACHE";
    String BIZ_SIMA = "BIZ_SIMA";
    String APM = "APM";
    String LIFECYCLE = "LIFECYCLE";
    String DEBUG = "DEBUG";
    String API = "API";
}
