package com.ellaclub.clogger_demo

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.ellaclub.clogger.CLogger
import com.ellaclub.clogger.MyJNI
import com.ellaclub.clogger.utils.CLoggerJNIHelper
import com.ellaclub.clogger.utils.LogType
import java.util.concurrent.Executors

class MainActivity : AppCompatActivity() {
    private var isEnablePrintable: Boolean = false
    private var isEnableSavefile: Boolean = false
    private var isenableLogan: Boolean = false
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main_activity)
        findViewById<Button>(R.id.btn1).setOnClickListener {
            CLogger.d(DemoT.DemoT, "打印日志1")
            CLogger.d(DemoT.DemoT, Exception("Test Exception!"), "打印日志2")
            CLogger.v(DemoT.DemoT, "打印verbose日志3")
            CLogger.i(DemoT.DemoT, "打印info日志4")
            CLogger.w(DemoT.DemoT, "打印warning日志5")
            CLogger.e(DemoT.DemoT, "打印error日志6")
            CLogger.wtf(DemoT.DemoT, "打印wtf日志7")
        }
        findViewById<Button>(R.id.btn2).setOnClickListener {
            for (i in 0..199) {
                CLogger.d(DemoT.DemoT, "打印日志8，index：$i")
            }
        }
        findViewById<Button>(R.id.btn3).setOnClickListener {


            // verbose
            CLoggerJNIHelper.loganLogV_S(
                LogType.APACHE, DemoT.DemoT.toString(), "打印日志，verbose，apache", null
            )
            CLoggerJNIHelper.loganLogV_S(
                LogType.BIZ_SIMA, DemoT.DemoT.toString(), "打印日志，verbose，sima", null
            )
            CLoggerJNIHelper.loganLogV_S(
                LogType.APM, DemoT.DemoT.toString(), "打印日志，verbose，apm", null
            )
            CLoggerJNIHelper.loganLogV_S(
                LogType.LIFECYCLE, DemoT.DemoT.toString(), "打印日志，verbose，lifecycle", null
            )
            CLoggerJNIHelper.loganLogV_S(
                LogType.DEBUG, DemoT.DemoT.toString(), "打印日志，verbose，debug", null
            )
            CLoggerJNIHelper.loganLogV_S(
                LogType.API, DemoT.DemoT.toString(), "打印日志，verbose，api", null
            )

            // debug
            CLoggerJNIHelper.loganLogD_S(
                LogType.APACHE, DemoT.DemoT.toString(), "打印日志，debug，apache", null
            )
            CLoggerJNIHelper.loganLogD_S(
                LogType.BIZ_SIMA, DemoT.DemoT.toString(), "打印日志，debug，sima", null
            )
            CLoggerJNIHelper.loganLogD_S(
                LogType.APM, DemoT.DemoT.toString(), "打印日志，debug，apm", null
            )
            CLoggerJNIHelper.loganLogD_S(
                LogType.LIFECYCLE, DemoT.DemoT.toString(), "打印日志，debug，lifecycle", null
            )
            CLoggerJNIHelper.loganLogD_S(
                LogType.DEBUG, DemoT.DemoT.toString(), "打印日志，debug，debug", null
            )
            CLoggerJNIHelper.loganLogD_S(
                LogType.API, DemoT.DemoT.toString(), "打印日志，debug，api", null
            )

            // info
            CLoggerJNIHelper.loganLogI_S(
                LogType.APACHE, DemoT.DemoT.toString(), "打印日志，info，apache", null
            )
            CLoggerJNIHelper.loganLogI_S(
                LogType.BIZ_SIMA, DemoT.DemoT.toString(), "打印日志，info，sima", null
            )
            CLoggerJNIHelper.loganLogI_S(
                LogType.APM, DemoT.DemoT.toString(), "打印日志，info，apm", null
            )
            CLoggerJNIHelper.loganLogI_S(
                LogType.LIFECYCLE, DemoT.DemoT.toString(), "打印日志，info，lifecycle", null
            )
            CLoggerJNIHelper.loganLogI_S(
                LogType.DEBUG, DemoT.DemoT.toString(), "打印日志，info，debug", null
            )
            CLoggerJNIHelper.loganLogI_S(
                LogType.API, DemoT.DemoT.toString(), "打印日志，info，api", null
            )

            // warning
            CLoggerJNIHelper.loganLogW_S(
                LogType.APACHE, DemoT.DemoT.toString(), "打印日志，warning，apache", null
            )
            CLoggerJNIHelper.loganLogW_S(
                LogType.BIZ_SIMA, DemoT.DemoT.toString(), "打印日志，warning，sima", null
            )
            CLoggerJNIHelper.loganLogW_S(
                LogType.APM, DemoT.DemoT.toString(), "打印日志，warning，apm", null
            )
            CLoggerJNIHelper.loganLogW_S(
                LogType.LIFECYCLE, DemoT.DemoT.toString(), "打印日志，warning，lifecycle", null
            )
            CLoggerJNIHelper.loganLogW_S(
                LogType.DEBUG, DemoT.DemoT.toString(), "打印日志，warning，debug", null
            )
            CLoggerJNIHelper.loganLogW_S(
                LogType.API, DemoT.DemoT.toString(), "打印日志，warning，api", null
            )

            // error
            CLoggerJNIHelper.loganLogE_S(
                LogType.APACHE, DemoT.DemoT.toString(), "打印日志，error，apache", null
            )
            CLoggerJNIHelper.loganLogE_S(
                LogType.BIZ_SIMA, DemoT.DemoT.toString(), "打印日志，error，sima", null
            )
            CLoggerJNIHelper.loganLogE_S(
                LogType.APM, DemoT.DemoT.toString(), "打印日志，error，apm", null
            )
            CLoggerJNIHelper.loganLogE_S(
                LogType.LIFECYCLE, DemoT.DemoT.toString(), "打印日志，error，lifecycle", null
            )
            CLoggerJNIHelper.loganLogE_S(
                LogType.DEBUG, DemoT.DemoT.toString(), "打印日志，error，debug", null
            )
            CLoggerJNIHelper.loganLogE_S(
                LogType.API, DemoT.DemoT.toString(), "打印日志，error，api", null
            )
        }
        findViewById<Button>(R.id.btn4).setOnClickListener {
            for (i in 0..499999) {
                val step = i
                val executorService = Executors.newFixedThreadPool(10);
                executorService.submit(Runnable {
                    CLogger.d(
                        DemoT.DemoT,
                        "打印日志9，thread_id: [" + Thread.currentThread().id + "]，index：" + step
                    )
                })
            }
        }
        findViewById<Button>(R.id.btn_enable_printable).setOnClickListener {
            val btn = it as Button
            isEnablePrintable = !isEnablePrintable
            if (isEnablePrintable) {
                btn.text = "关闭Printable日志"
            } else {
                btn.text = "开启Printable日志"
            }
            CLogger.setPrintable(isEnablePrintable)
        }
        findViewById<Button>(R.id.btn_enable_savefile).setOnClickListener {
            val btn = it as Button
            isEnableSavefile = !isEnableSavefile
            if (isEnableSavefile) {
                btn.text = "关闭Savefile日志"
            } else {
                btn.text = "开启Savefile日志"
            }
            CLogger.setSaveToDisk(isEnableSavefile)
        }
        findViewById<Button>(R.id.btn_enable_logan).setOnClickListener {
            val btn = it as Button
            isenableLogan = !isenableLogan
            if (isenableLogan) {
                btn.text = "关闭Logan日志"
            } else {
                btn.text = "开启Logan日志"
            }
            CLogger.setLogan(isenableLogan)
        }
        findViewById<Button>(R.id.btn_native_log).setOnClickListener {
            MyJNI.testPrint()
        }
    }

    override fun onDestroy() {
        CLogger.destroy()
        super.onDestroy()
    }
}