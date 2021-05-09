package com.example.myandroidhomework2providertest

import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.app.Service
import android.content.Context
import android.content.Intent
import android.graphics.BitmapFactory
import android.net.Uri
import android.os.Binder
import android.os.Build
import android.os.IBinder
import android.util.Log
import androidx.core.app.NotificationCompat
import androidx.core.content.contentValuesOf
import java.io.BufferedWriter
import java.io.IOException
import java.io.OutputStreamWriter
import java.text.SimpleDateFormat
import java.util.*
import kotlin.concurrent.thread


class MyService : Service() {
    override fun onBind(intent: Intent?): IBinder? {
//        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
        return Binder()
    }
    override fun onCreate() {
        super.onCreate()
        val manager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val channel = NotificationChannel("my_service", "running", NotificationManager.IMPORTANCE_DEFAULT)
            manager.createNotificationChannel(channel)
        }
        val intent = Intent(this, MainActivity::class.java)
        val pi = PendingIntent.getActivity(this, 0, intent, 0)
        val notification = NotificationCompat.Builder(this, "my_service")
            .setContentTitle("服务正在运行")
            .setContentText("检查薪水是否为负的")
            .setSmallIcon(R.drawable.ic_android_black_24dp)
            .setLargeIcon(BitmapFactory.decodeResource(resources, R.drawable.ic_android_black_24dp))
            .setContentIntent(pi)
            .build()
        startForeground(1, notification)
    }

    override fun onStartCommand(intent: Intent, flags: Int, startId: Int): Int {
        thread {
            while (true){
                val uri = Uri.parse("content://xianfei.myandroidhomework2.provider/staff")
                var mylog:String = ""
                contentResolver.query(uri, null, null, null, null)?.apply {
                    while (moveToNext()) {
                        val id = getInt(getColumnIndex("id"))
                        val salary = getInt(getColumnIndex("salary"))
                        val name = getString(getColumnIndex("name"))
                        if (salary < 0){
                            mylog += "id:$id(name:$name) salary is $salary. changed to zero.\n"
                            val newuri = Uri.parse("content://xianfei.myandroidhomework2.provider/staff/$id")
                            val values = contentValuesOf("salary" to 0)
                            contentResolver.update(newuri, values, null, null)
                        }
                    }
                    if(!mylog.equals("")){
                        try {
                            val output = openFileOutput("check.log", Context.MODE_PRIVATE)
                            val writer = BufferedWriter(OutputStreamWriter(output))
                            writer.use {
                                val simpleDateFormat = SimpleDateFormat("yyyy年MM月dd日 HH:mm:ss")
                                val date = Date(System.currentTimeMillis())
                                it.write(simpleDateFormat.format(date))
                                it.write(":\n")
                                it.write(mylog)
                                it.write("\n\n")
                            }
                        } catch (e: IOException) {
                            e.printStackTrace()
                        }
                    }
                    close()
                }
                Thread.sleep(5000)
                Log.d("MyService","I am running!")
            }
        }
//        Log.d("MyService", "onStartCommand executed")
        return super.onStartCommand(intent, flags, startId)
    }

    override fun onDestroy() {
        super.onDestroy()
//        Log.d("MyService", "onDestroy executed")
    }


}