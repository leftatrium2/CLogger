package com.ellaclub.clogger_demo;

import com.ellaclub.clogger.T;

public enum AppTest implements T {
    APP_TEST;

    @Override
    public String tag() {
        return toString();
    }
}
