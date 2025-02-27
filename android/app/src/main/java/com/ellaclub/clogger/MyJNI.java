package com.ellaclub.clogger;

public class MyJNI {
    static {
        System.loadLibrary("app");
    }

    public static native void testPrint();
}
