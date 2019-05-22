package com.example.synth;

import android.os.Bundle;
import android.view.MotionEvent;
import androidx.appcompat.app.AppCompatActivity;
import com.example.synth.panels.ADSRControls;
import com.example.synth.panels.FilterControls;
import com.example.synth.ui.KeyboardView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private native void onFilterCutoff(float cutoff);

    private native void onFilterRes(float res);

    private native void onFilterEnvAmt(float val);

    private native void onKeyPressed(float freq);

    private native void onKeyReleased();

    private native void setAttack(int id, float val);

    private native void setDecay(int id, float val);

    private native void setSustain(int id, float val);

    private native void setRelease(int id, float val);

    private native void touchEvent(int action, float x, float y);

    private native void startEngine();

    private native void stopEngine();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        KeyboardView keyboard = findViewById(R.id.keyboard);
        keyboard.setListener(new KeyboardView.Listener() {
            @Override
            public void onKeyPressed(float frequency) {
                MainActivity.this.onKeyPressed(frequency);
            }

            @Override
            public void onKeyReleased() {
                MainActivity.this.onKeyReleased();
            }
        });

        FilterControls filterControls = findViewById(R.id.filter);
        filterControls.setListener(new FilterControls.FilterListener() {
            @Override
            public void onCutoffChange(float cutoff) {
                onFilterCutoff(cutoff);
            }

            @Override
            public void onResChange(float res) {
                onFilterRes(res);
            }

            @Override
            public void onEnvAmtChange(float val) {
                onFilterEnvAmt(val);
            }
        });

        ADSRControls adsrControls = findViewById(R.id.adsr1);
        adsrControls.setListener(new ADSRControls.ADSRListener() {
            @Override
            public void onAttackChange(float attack) {
                setAttack(0, attack);
            }

            @Override
            public void onDecayChange(float decay) {
                setDecay(0, decay);
            }

            @Override
            public void onSustainChange(float sustain) {
                setSustain(0, sustain);
            }

            @Override
            public void onReleaseChange(float release) {
                setRelease(0, release);
            }
        });

        ADSRControls adsr2Controls = findViewById(R.id.adsr2);
        adsr2Controls.setListener(new ADSRControls.ADSRListener() {
            @Override
            public void onAttackChange(float attack) {
                setAttack(1, attack);
            }

            @Override
            public void onDecayChange(float decay) {
                setDecay(1, decay);
            }

            @Override
            public void onSustainChange(float sustain) {
                setSustain(1, sustain);
            }

            @Override
            public void onReleaseChange(float release) {
                setRelease(1, release);
            }
        });

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
