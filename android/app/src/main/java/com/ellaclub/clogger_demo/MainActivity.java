package com.ellaclub.clogger_demo;

import android.app.Activity;
import android.os.Bundle;
import android.os.Looper;
import android.view.View;
import android.widget.Button;

import com.ellaclub.clogger.MyJNI;
import com.ellaclub.clogger.CLogger;
import com.ellaclub.clogger.utils.LogType;
import com.ellaclub.clogger.utils.CLoggerJNIHelper;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends Activity implements View.OnClickListener {
    private Button mBtn1;
    private Button mBtn2;
    private Button mBtn3;
    private Button mBtn4;
    private Button mBtnEnablePrintable;
    private Button mBtnEnableSavefile;
    private Button mBtnEnableLogan;
    private Button mBtnNativeLog;

    private ExecutorService mExecutorService;

    private boolean isEnablePrintable = true;
    private boolean isEnableSavefile = true;
    private boolean isenableLogan = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);
        CLogger.d(AppTest.APP_TEST, "test");
        mBtn1 = (Button) findViewById(R.id.btn1);
        mBtn1.setOnClickListener(this);
        mBtn2 = (Button) findViewById(R.id.btn2);
        mBtn2.setOnClickListener(this);
        mBtn3 = (Button) findViewById(R.id.btn3);
        mBtn3.setOnClickListener(this);
        mBtn4 = (Button) findViewById(R.id.btn4);
        mBtn4.setOnClickListener(this);
        mBtnEnablePrintable = (Button) findViewById(R.id.btn_enable_printable);
        mBtnEnablePrintable.setOnClickListener(this);
        mBtnEnableSavefile = (Button) findViewById(R.id.btn_enable_savefile);
        mBtnEnableSavefile.setOnClickListener(this);
        mBtnEnableLogan = (Button) findViewById(R.id.btn_enable_logan);
        mBtnEnableLogan.setOnClickListener(this);
        mBtnNativeLog = (Button) findViewById(R.id.btn_native_log);
        mBtnNativeLog.setOnClickListener(this);
        Thread.currentThread().getId();
        Looper.getMainLooper().getThread().getId();

        mExecutorService = Executors.newFixedThreadPool(10);
    }

    @Override
    protected void onDestroy() {
        CLogger.destroy();
        super.onDestroy();
    }

    @Override
    public void onClick(View v) {
        if (v == mBtn1) {
            CLogger.d(AppTest.APP_TEST, "打印日志1");
            CLogger.d(AppTest.APP_TEST, new Exception("Test Exception!"), "打印日志2");
            CLogger.v(AppTest.APP_TEST, "打印verbose日志3");
            CLogger.i(AppTest.APP_TEST, "打印info日志4");
            CLogger.w(AppTest.APP_TEST, "打印warning日志5");
            CLogger.e(AppTest.APP_TEST, "打印error日志6");
            CLogger.wtf(AppTest.APP_TEST, "打印wtf日志7");
        } else if (v == mBtn2) {
            for (int i = 0; i < 200; i++) {
                CLogger.d(AppTest.APP_TEST, "打印日志8，index：" + i);
            }
        } else if (v == mBtn4) {
            for (int i = 0; i < 500000; i++) {
                final int step = i;
                mExecutorService.submit(new Runnable() {
                    @Override
                    public void run() {
                        CLogger.d(AppTest.APP_TEST, "打印日志9，thread_id: [" + Thread.currentThread().getId() + "]，index：" + step);
                    }
                });
            }
        } else if (v == mBtn3) {
            // verbose
            CLoggerJNIHelper.loganLogV_S(LogType.APACHE, AppTest.APP_TEST.toString(), "打印日志，verbose，apache", null);
            CLoggerJNIHelper.loganLogV_S(LogType.BIZ_SIMA, AppTest.APP_TEST.toString(), "打印日志，verbose，sima", null);
            CLoggerJNIHelper.loganLogV_S(LogType.APM, AppTest.APP_TEST.toString(), "打印日志，verbose，apm", null);
            CLoggerJNIHelper.loganLogV_S(LogType.LIFECYCLE, AppTest.APP_TEST.toString(), "打印日志，verbose，lifecycle", null);
            CLoggerJNIHelper.loganLogV_S(LogType.DEBUG, AppTest.APP_TEST.toString(), "打印日志，verbose，debug", null);
            CLoggerJNIHelper.loganLogV_S(LogType.API, AppTest.APP_TEST.toString(), "打印日志，verbose，api", null);
            // debug
            CLoggerJNIHelper.loganLogD_S(LogType.APACHE, AppTest.APP_TEST.toString(), "打印日志，debug，apache", null);
            CLoggerJNIHelper.loganLogD_S(LogType.BIZ_SIMA, AppTest.APP_TEST.toString(), "打印日志，debug，sima", null);
            CLoggerJNIHelper.loganLogD_S(LogType.APM, AppTest.APP_TEST.toString(), "打印日志，debug，apm", null);
            CLoggerJNIHelper.loganLogD_S(LogType.LIFECYCLE, AppTest.APP_TEST.toString(), "打印日志，debug，lifecycle", null);
            CLoggerJNIHelper.loganLogD_S(LogType.DEBUG, AppTest.APP_TEST.toString(), "打印日志，debug，debug", null);
            CLoggerJNIHelper.loganLogD_S(LogType.API, AppTest.APP_TEST.toString(), "打印日志，debug，api", null);
            // info
            CLoggerJNIHelper.loganLogI_S(LogType.APACHE, AppTest.APP_TEST.toString(), "打印日志，info，apache", null);
            CLoggerJNIHelper.loganLogI_S(LogType.BIZ_SIMA, AppTest.APP_TEST.toString(), "打印日志，info，sima", null);
            CLoggerJNIHelper.loganLogI_S(LogType.APM, AppTest.APP_TEST.toString(), "打印日志，info，apm", null);
            CLoggerJNIHelper.loganLogI_S(LogType.LIFECYCLE, AppTest.APP_TEST.toString(), "打印日志，info，lifecycle", null);
            CLoggerJNIHelper.loganLogI_S(LogType.DEBUG, AppTest.APP_TEST.toString(), "打印日志，info，debug", null);
            CLoggerJNIHelper.loganLogI_S(LogType.API, AppTest.APP_TEST.toString(), "打印日志，info，api", null);
            // warning
            CLoggerJNIHelper.loganLogW_S(LogType.APACHE, AppTest.APP_TEST.toString(), "打印日志，warning，apache", null);
            CLoggerJNIHelper.loganLogW_S(LogType.BIZ_SIMA, AppTest.APP_TEST.toString(), "打印日志，warning，sima", null);
            CLoggerJNIHelper.loganLogW_S(LogType.APM, AppTest.APP_TEST.toString(), "打印日志，warning，apm", null);
            CLoggerJNIHelper.loganLogW_S(LogType.LIFECYCLE, AppTest.APP_TEST.toString(), "打印日志，warning，lifecycle", null);
            CLoggerJNIHelper.loganLogW_S(LogType.DEBUG, AppTest.APP_TEST.toString(), "打印日志，warning，debug", null);
            CLoggerJNIHelper.loganLogW_S(LogType.API, AppTest.APP_TEST.toString(), "打印日志，warning，api", null);
            // error
            CLoggerJNIHelper.loganLogE_S(LogType.APACHE, AppTest.APP_TEST.toString(), "打印日志，error，apache", null);
            CLoggerJNIHelper.loganLogE_S(LogType.BIZ_SIMA, AppTest.APP_TEST.toString(), "打印日志，error，sima", null);
            CLoggerJNIHelper.loganLogE_S(LogType.APM, AppTest.APP_TEST.toString(), "打印日志，error，apm", null);
            CLoggerJNIHelper.loganLogE_S(LogType.LIFECYCLE, AppTest.APP_TEST.toString(), "打印日志，error，lifecycle", null);
            CLoggerJNIHelper.loganLogE_S(LogType.DEBUG, AppTest.APP_TEST.toString(), "打印日志，error，debug", null);
            CLoggerJNIHelper.loganLogE_S(LogType.API, AppTest.APP_TEST.toString(), "打印日志，error，api", null);
        } else if (v == mBtnEnablePrintable) {
            isEnablePrintable = !isEnablePrintable;
            if (isEnablePrintable) {
                mBtnEnablePrintable.setText("关闭Printable日志");
            } else {
                mBtnEnablePrintable.setText("开启Printable日志");
            }
            CLogger.setPrintable(isEnablePrintable);
        } else if (v == mBtnEnableSavefile) {
            isEnableSavefile = !isEnableSavefile;
            if (isEnableSavefile) {
                mBtnEnableSavefile.setText("关闭Savefile日志");
            } else {
                mBtnEnableSavefile.setText("开启Savefile日志");
            }
            CLogger.setSaveToDisk(isEnableSavefile);
        } else if (v == mBtnEnableLogan) {
            isenableLogan = !isenableLogan;
            if (isenableLogan) {
                mBtnEnableLogan.setText("关闭Logan日志");
            } else {
                mBtnEnableLogan.setText("开启Logan日志");
            }
            CLogger.setLogan(isenableLogan);
        } else if (v == mBtnNativeLog) {
            MyJNI.testPrint();
        }
    }
}