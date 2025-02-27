package com.ellaclub.clogger.utils;

import com.ellaclub.clogger.T;

public enum CLoggerSDKT implements T {
    CODE;

    @Override
    public String tag() {
        return toString();
    }
}
