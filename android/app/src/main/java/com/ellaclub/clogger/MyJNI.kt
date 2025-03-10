package com.ellaclub.clogger

class MyJNI {
    companion object{
        init {
            System.loadLibrary("app")
        }

        @JvmStatic
        external fun testPrint()
    }
}