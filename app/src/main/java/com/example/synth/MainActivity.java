package com.example.synth;

import android.os.Bundle;
import android.view.MotionEvent;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private native void touchEvent(int action, float x, float y);

    private native void startEngine();

    private native void stopEngine();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        startEngine();
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        touchEvent(event.getAction(), event.getX(), event.getY());
        return super.onTouchEvent(event);
    }

    @Override
    public void onDestroy() {
        stopEngine();
        super.onDestroy();
    }
}
