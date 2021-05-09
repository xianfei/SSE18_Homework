package xianfei.myandroidhomework2

import android.content.Context
import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // 使用SharedPreferences保存用户的自定义字体颜色
        val prefs = getSharedPreferences("data", Context.MODE_PRIVATE)
        textView.setTextColor(Color.parseColor(prefs.getString("text_color","#000000")))
        editText.setText(prefs.getString("text_color","#000000"))

        // 设置颜色
        button.setOnClickListener {
            textView.setTextColor(Color.parseColor(editText.text.toString()))
            val editor = prefs.edit()
            editor.putString("text_color",editText.text.toString())
            editor.apply()
        }


        val dbHelper = MyDatabaseHelper(this, "test.db", 1)
        val db = dbHelper.writableDatabase
        val cursor = db.query("Staff", null, null, null, null, null, null)
        if (cursor.moveToFirst()) {
            do {
                // 遍历Cursor对象，取出数据并打印
                val id = cursor.getInt(cursor.getColumnIndex("id"))
                val name = cursor.getString(cursor.getColumnIndex("name"))
                val gender = cursor.getString(cursor.getColumnIndex("gender"))
                val department = cursor.getString(cursor.getColumnIndex("department"))
                val salary = cursor.getInt(cursor.getColumnIndex("salary"))
                textView.text = textView.text.toString() + "\n $id \t| $name \t| $gender \t| $department \t| $salary";
            } while (cursor.moveToNext())
        }
        cursor.close()

        refresh.setOnClickListener{
            textView.text = "id \t| name \t| gender \t| department \t| salary"
            val cursor = db.query("Staff", null, null, null, null, null, null)
            if (cursor.moveToFirst()) {
                do {
                    // 遍历Cursor对象，取出数据并打印
                    val id = cursor.getInt(cursor.getColumnIndex("id"))
                    val name = cursor.getString(cursor.getColumnIndex("name"))
                    val gender = cursor.getString(cursor.getColumnIndex("gender"))
                    val department = cursor.getString(cursor.getColumnIndex("department"))
                    val salary = cursor.getInt(cursor.getColumnIndex("salary"))
                    textView.text = textView.text.toString() + "\n $id \t| $name \t| $gender \t| $department \t| $salary";
                } while (cursor.moveToNext())
            }
            cursor.close()
        }
    }
}
