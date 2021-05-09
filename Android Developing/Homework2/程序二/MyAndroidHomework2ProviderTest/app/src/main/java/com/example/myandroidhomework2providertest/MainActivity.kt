package com.example.myandroidhomework2providertest

import android.content.DialogInterface
import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import androidx.appcompat.app.AlertDialog
import androidx.core.content.contentValuesOf
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    var ids = ArrayList<String?>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        addData.setOnClickListener {
            // 添加数据
            val uri = Uri.parse("content://xianfei.myandroidhomework2.provider/staff")
            val values = arrayOf(
                contentValuesOf(
                    "name" to "Tom",
                    "gender" to "male",
                    "department" to "computer",
                    "salary" to 5400
                ),contentValuesOf(
                    "name" to "Einstein",
                    "gender" to "male",
                    "department" to "computer",
                    "salary" to 4800
                ),contentValuesOf(
                    "name" to "Lily",
                    "gender" to "female",
                    "department" to "market",
                    "salary" to 5000
                ),contentValuesOf(
                    "name" to "Warner",
                    "gender" to "male",
                    "department" to "market"
                ),contentValuesOf(
                    "name" to "Napoleon",
                    "gender" to "male"
                )
            )
            values.forEach {
                val newUri = contentResolver.insert(uri, it)
                ids.add(newUri?.pathSegments?.get(1))
            }

        }

        queryData.setOnClickListener {
            // 查询数据
            textView.text = "id \t| name \t| gender \t| department \t| salary"
            val uri = Uri.parse("content://xianfei.myandroidhomework2.provider/staff")
            contentResolver.query(uri, null, null, null, null)?.apply {
                while (moveToNext()) {
                    val id = getInt(getColumnIndex("id"))
                    val name = getString(getColumnIndex("name"))
                    val gender = getString(getColumnIndex("gender"))
                    val department = getString(getColumnIndex("department"))
                    val salary = getInt(getColumnIndex("salary"))
                    textView.text =
                        textView.text.toString() + "\n $id \t| $name \t| $gender \t| $department \t| $salary";
                }
                close()
            }
        }

        updateData.setOnClickListener {
            // 更新数据
            ids.forEach {
                it?.let {
                    val uri = Uri.parse("content://xianfei.myandroidhomework2.provider/staff/$it")
//                val values = contentValuesOf("name" to "Tom",
//                "gender" to "male", "department" to "computer", "salary" to 1500)
                    val values = contentValuesOf("salary" to -100)
                    contentResolver.update(uri, values, null, null)
                }
            }

        }

        deleteData.setOnClickListener {
            // 删除数据
            ids.forEach {
                it?.let {
                    val uri = Uri.parse("content://xianfei.myandroidhomework2.provider/staff/$it")
                    contentResolver.delete(uri, null, null)
                }
            }
        }

        val intent = Intent(this, MyService::class.java)
        startService(intent) // 启动Service



    }


}
