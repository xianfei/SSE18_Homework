package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 显示信息
        findViewById(R.id.button2).setOnClickListener((e) -> {
            String str = ((EditText) findViewById(R.id.editTextTextPersonName)).getText().toString() + "今年"
                    + ((EditText) findViewById(R.id.editTextTextPersonName4)).getText().toString() + "岁了，身高是"
                    + ((EditText) findViewById(R.id.editTextTextPersonName3)).getText().toString() + "米。";
            ((TextView) findViewById(R.id.textView4)).setText(str);
        });

        // 删除信息
        findViewById(R.id.button3).setOnClickListener((e) -> {
            ((EditText) findViewById(R.id.editTextTextPersonName)).setText("");
            ((EditText) findViewById(R.id.editTextTextPersonName4)).setText("");
            ((EditText) findViewById(R.id.editTextTextPersonName3)).setText("");
            ((TextView) findViewById(R.id.textView4)).setText("");
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Toast.makeText(getApplicationContext(), "你点击了" + item.getTitle() + "菜单项", Toast.LENGTH_SHORT).show();
        return false;
    }
}