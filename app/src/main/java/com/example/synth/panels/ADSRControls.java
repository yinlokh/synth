package com.example.synth.panels;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.LinearLayout;
import androidx.annotation.Nullable;
import com.example.synth.R;
import com.example.synth.ui.ControlListener;
import com.example.synth.ui.Knob;

public class ADSRControls extends LinearLayout {

    private ADSRListener listener;

    public ADSRControls(Context context) {
        super(context);
    }

    public ADSRControls(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public ADSRControls(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }
    @Override
    public void onFinishInflate() {
        super.onFinishInflate();
        Knob cutoff = findViewById(R.id.attack);
        cutoff.setListener(new ControlListener() {
            @Override
            public void onValueChanged(float value) {
                if (listener != null) {
                    listener.onAttackChange(value);
                }
            }
        });

        Knob decay = findViewById(R.id.decay);
        decay.setListener(new ControlListener() {
            @Override
            public void onValueChanged(float value) {
                if (listener != null) {
                    listener.onDecayChange(value);
                }
            }
        });

        Knob sustain = findViewById(R.id.sustain);
        sustain.setListener(new ControlListener() {
            @Override
            public void onValueChanged(float value) {
                if (listener != null) {
                    listener.onSustainChange(value);
                }
            }
        });

        Knob release = findViewById(R.id.release);
        release.setListener(new ControlListener() {
            @Override
            public void onValueChanged(float value) {
                if (listener != null) {
                    listener.onReleaseChange(value);
                }
            }
        });
    }

    public void setListener(ADSRListener listener) {
        this.listener = listener;
    }

    public interface ADSRListener {

        void onAttackChange(float attack);

        void onDecayChange(float decay);

        void onSustainChange(float sustain);

        void onReleaseChange(float release);
    }
}
