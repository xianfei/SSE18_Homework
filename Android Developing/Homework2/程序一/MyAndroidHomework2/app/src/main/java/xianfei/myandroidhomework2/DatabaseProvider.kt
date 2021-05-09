package xianfei.myandroidhomework2

import android.content.ContentProvider
import android.content.ContentValues
import android.database.Cursor
import android.net.Uri
import android.content.UriMatcher
import android.os.CancellationSignal
import android.database.sqlite.SQLiteDatabase

class DatabaseProvider : ContentProvider() {

    private val staffDir = 0
    private val staffItem = 1
    private val authority = "xianfei.myandroidhomework2.provider"
    private var dbHelper: MyDatabaseHelper? = null

    private val uriMatcher by lazy {
        val matcher = UriMatcher(UriMatcher.NO_MATCH)
        matcher.addURI(authority, "staff", staffDir)
        matcher.addURI(authority, "staff/#", staffItem)
        matcher
    }

    override fun onCreate() = context?.let {
        dbHelper = MyDatabaseHelper(it, "test.db", 1)
        true
    } ?: false

    override fun query(
        uri: Uri,
        projection: Array<String>?,
        selection: String?,
        selectionArgs: Array<String>?,
        sortOrder: String?
    ) = dbHelper?.let {
        // 查询数据
        val db = it.readableDatabase
        val cursor = when (uriMatcher.match(uri)) {
            staffDir -> db.query("Staff", projection, selection, selectionArgs, null, null, sortOrder)
            staffItem -> {
                val staffId = uri.pathSegments[1]
                db.query("Staff", projection, "id = ?", arrayOf(staffId), null, null, sortOrder)
            }
            else -> null
        }
        cursor
    }

    override fun insert(uri: Uri, values: ContentValues?) = dbHelper?.let {
        // 添加数据
        val db = it.writableDatabase
        val uriReturn = when (uriMatcher.match(uri)) {
            staffDir, staffItem -> {
                val newStaffId = db.insert("Staff", null, values)
                Uri.parse("content://$authority/staff/$newStaffId")
            }
            else -> null
        }
        uriReturn
    }

    override fun update(uri: Uri, values: ContentValues?, selection: String?, selectionArgs: Array<String>?) =
        dbHelper?.let {
            // 更新数据
            val db = it.writableDatabase
            val updatedRows = when (uriMatcher.match(uri)) {
                staffDir -> db.update("Staff", values, selection, selectionArgs)
                staffItem -> {
                    val staffId = uri.pathSegments[1]
                    db.update("Staff", values, "id = ?", arrayOf(staffId))
                }
                else -> 0
            }
            updatedRows
        } ?: 0

    override fun delete(uri: Uri, selection: String?, selectionArgs: Array<String>?) = dbHelper?.let {
        // 删除数据
        val db = it.writableDatabase
        val deletedRows = when (uriMatcher.match(uri)) {
            staffDir -> db.delete("Staff", selection, selectionArgs)
            staffItem -> {
                val staffId = uri.pathSegments[1]
                db.delete("Staff", "id = ?", arrayOf(staffId))
            }
            else -> 0
        }
        deletedRows
    } ?: 0

    override fun getType(uri: Uri) = when (uriMatcher.match(uri)) {
        staffDir -> "vnd.android.cursor.dir/vnd.xianfei.myandroidhomework2.provider.staff"
        staffItem -> "vnd.android.cursor.item/vnd.xianfei.myandroidhomework2.provider.staff"
        else -> null
    }
}
