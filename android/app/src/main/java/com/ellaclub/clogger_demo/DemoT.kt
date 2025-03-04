package com.ellaclub.clogger_demo

import com.ellaclub.clogger.T

enum class DemoT : T {
    DemoT;

    override fun tag(): String {
        return toString()
    }
}