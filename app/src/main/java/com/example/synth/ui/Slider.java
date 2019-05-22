package com.example.synth.ui;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import androidx.annotation.Nullable;
import com.example.synth.util.Validation;

public class Slider extends ControlView {

    private float level;
    private Paint paintBorder;
    private Paint paintFill;

    public Slider(Context context) {
        super(context);
        init();
    }

    public Slider(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public Slider(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init() {
        paintBorder = new Paint();
        paintBorder.setColor(Color.RED);
        paintBorder.setStrokeWidth(8);
        paintBorder.setStyle(Paint.Style.STROKE);

        paintFill = new Paint();
        paintFill.setColor(Color.RED);
        paintFill.setStrokeWidth(8);
        paintFill.setStyle(Paint.Style.FILL);

        setOnTouchListener(
                new OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        if (event.getAction() == MotionEvent.ACTION_DOWN
                            || event.getAction() == MotionEvent.ACTION_MOVE) {
                            level = Validation.clamp(
                                    event.getX() / Math.max(1, v.getWidth()),
                                            0.f,
                                            1.f);
                            setLevel(level);
                            postInvalidate();
                            return true;
                        }
                        return false;
                    }
                }
        );
    }

    @Override
    public void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        canvas.drawRect(0, 0, canvas.getWidth(), canvas.getHeight(), paintBorder);
        canvas.drawRect(0, 0, canvas.getWidth() * level, canvas.getHeight(), paintFill);
    }
}
