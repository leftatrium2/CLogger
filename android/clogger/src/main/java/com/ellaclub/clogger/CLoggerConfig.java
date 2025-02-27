package com.ellaclub.clogger;

import java.io.File;

public class CLoggerConfig {
    private boolean saveToDisk;
    private File saveToDiskLog;
    private boolean logan;
    private File loganCache;
    private File loganDir;
    private int loganMaxFile;
    private int loganMaxDay;
    private boolean loganUseFakeTime;
    private boolean loganIsDebug;
    private boolean printable;
    private boolean ismethodinfo;

    private CLoggerConfig(Builder builder) {
        this.saveToDisk = builder.saveToDisk;
        this.logan = builder.logan;
        this.printable = builder.printable;
        this.saveToDiskLog = builder.saveToDiskLog;
        this.loganCache = builder.loganCache;
        this.loganDir = builder.loganDir;
        this.loganMaxFile = builder.loganMaxFile;
        this.loganMaxDay = builder.loganMaxDay;
        this.loganIsDebug = builder.loganIsDebug;
        this.ismethodinfo = builder.ismethodinfo;
        this.loganUseFakeTime = builder.loganUseFakeTime;
    }

    public static Builder builder() {
        return new Builder();
    }

    public boolean loganUseFakeTime() {
        return this.loganUseFakeTime;
    }

    public boolean isSaveToDisk() {
        return saveToDisk;
    }

    public boolean isLogan() {
        return logan;
    }

    public boolean isPrintable() {
        return printable;
    }

    public File getSaveToDiskLog() {
        return saveToDiskLog;
    }

    public File getLoganCache() {
        return loganCache;
    }

    public File getLoganDir() {
        return loganDir;
    }

    public int getLoganMaxFile() {
        return loganMaxFile;
    }

    public int getLoganMaxDay() {
        return loganMaxDay;
    }

    public boolean getLoganIsDebug() {
        return loganIsDebug;
    }

    public boolean ismethodinfo() {
        return ismethodinfo;
    }

    public static class Builder {
        //在debug以及测试环境中，存到外存，默认不存
        private boolean saveToDisk = false;
        //存到logan中，默认不存
        private boolean logan = false;
        //直接控制台输出 -- 默认开启
        private boolean printable = true;
        private File saveToDiskLog = null;
        private File loganCache = null;
        private File loganDir = null;
        private int loganMaxFile = 10 * 1024 * 1024; //默认10M
        private int loganMaxDay = 10;//默认保存10天
        private boolean loganIsDebug = false; //默认关闭debug
        private boolean ismethodinfo = false; //默认关闭method
        private boolean loganUseFakeTime = false; //默认关闭faketime

        public Builder loganUseFakeTime(boolean loganUseFakeTime) {
            this.loganUseFakeTime = loganUseFakeTime;
            return this;
        }

        public Builder saveToDisk(boolean saveToDisk) {
            this.saveToDisk = saveToDisk;
            return this;
        }

        public Builder logan(boolean logan) {
            this.logan = logan;
            return this;
        }

        public Builder printable(boolean printable) {
            this.printable = printable;
            return this;
        }

        public Builder saveToDiskLogPath(File saveToDiskLogPath) {
            this.saveToDiskLog = saveToDiskLogPath;
            return this;
        }

        public Builder loganCachePath(File loganCachePath) {
            this.loganCache = loganCachePath;
            return this;
        }

        public Builder loganDirPath(File loganDirPath) {
            this.loganDir = loganDirPath;
            return this;
        }

        public Builder loganMaxFile(int loganMaxFile) {
            this.loganMaxFile = loganMaxFile;
            return this;
        }

        public Builder loganMaxDay(int loganMaxDay) {
            this.loganMaxDay = loganMaxDay;
            return this;
        }

        public Builder loganIsDebug(boolean loganIsDebug) {
            this.loganIsDebug = loganIsDebug;
            return this;
        }

        public Builder ismethodinfo(boolean ismethodinfo) {
            this.ismethodinfo = ismethodinfo;
            return this;
        }


        public CLoggerConfig build() {
            return new CLoggerConfig(this);
        }
    }
}
