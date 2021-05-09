package xianfei.myandroidhomework2

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper

class MyDatabaseHelper(val context: Context, name: String, version: Int) :
    SQLiteOpenHelper(context, name, null, version) {

    override fun onCreate(db: SQLiteDatabase) {
        db.execSQL("create table Staff (" +
                "id integer primary key autoincrement," +
                "name text," +
                "gender text," +
                "department text," +
                "salary integer)")
//        db.execSQL("INSERT INTO Staff VALUES (1,'Tom','male','computer',5400)")
//        db.execSQL("INSERT INTO Staff VALUES (2,'Tom','Einstein','computer',4800)")
//        db.execSQL("INSERT INTO Staff VALUES (3,'Lily','female','market',5000)")
//        db.execSQL("INSERT INTO Staff VALUES (4,'Warner','male','market',null)")
//        db.execSQL("INSERT INTO Staff VALUES (5,'Napoleon','male',null,null)")

    }

    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        db.execSQL("drop table if exists Staff")
        onCreate(db)
    }
}
