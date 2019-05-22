package com.example.synth.panels;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.LinearLayout;
import androidx.annotation.Nullable;
import com.example.synth.R;
import com.example.synth.ui.ControlListener;
import com.example.synth.ui.Knob;

public class FilterControls extends LinearLayout {

    private FilterListener listener;

    public FilterControls(Context context) {
        super(context);
    }

    public FilterControls(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public FilterControls(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @Override
    public void onFinishInflate() {
        super.onFinishInflate();
        Knob cutoff = findViewById(R.id.cutoff);
        cutoff.setListener(new ControlListener() {
            @Override
            public void onValueChanged(float value) {
                if (listener != null) {
                    listener.onCutoffChange(value);
                }
            }
        });

        Knob res = findViewById(R.id.res);
        res.setListener(new ControlListener() {
            @Override
            public void onValueChanged(float value) {
                if (listener != null) {
                    listener.onResChange(value);
                }
            }
        });

        Knob envAmt = findViewById(R.id.env_amt);
        envAmt.setListener(new ControlListener() {
            @Override
            public void onValueChanged(float value) {
                if (listener != null) {
                    listener.onEnvAmtChange(value);
                }
            }
        });
    }

    public void setListener(FilterListener listener) {
        this.listener = listener;
    }

    public interface FilterListener {

        void onCutoffChange(float cutoff);

        void onResChange(float res);

        void onEnvAmtChange(float val);
    }
}
