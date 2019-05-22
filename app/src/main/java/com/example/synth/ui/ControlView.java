package com.example.synth.ui;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import androidx.annotation.Nullable;

public abstract class ControlView extends View {

    private ControlListener listener;

    public ControlView(Context context) {
        super(context);
    }

    public ControlView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public ControlView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public void setListener(ControlListener listener) {
        this.listener = listener;
    }

    protected void setLevel(float level) {
        if (listener != null) {
            listener.onValueChanged(level);
        }
    }
}
