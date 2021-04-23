package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class DisplayMessageActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_message);

        // Get the Intent that started this activity and extract the string
        Intent intent = getIntent();
        String message = intent.getStringExtra("xianfei.myhomework1.showinfo");

        // Capture the layout's TextView and set the string as its text
        TextView textView = findViewById(R.id.textView6);
        textView.setText(message);

        // 销毁
        findViewById(R.id.button).setOnClickListener(e->{
            finish();
        });
    }
}