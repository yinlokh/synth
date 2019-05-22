package com.example.synth.ui;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import androidx.annotation.Nullable;
import com.example.synth.util.Validation;

import static android.view.KeyEvent.ACTION_DOWN;
import static android.view.MotionEvent.ACTION_MOVE;
import static com.example.synth.util.Validation.clamp;

public class Knob extends ControlView {

    private float level;
    private Paint valueFill;
    private Paint trackFill;
    private float lastX;

    public Knob(Context context) {
        super(context);
        init();
    }

    public Knob(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public Knob(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init() {
        valueFill = new Paint();
        valueFill.setColor(Color.RED);
        valueFill.setStrokeWidth(10);
        valueFill.setStyle(Paint.Style.STROKE);

        trackFill = new Paint();
        trackFill.setColor(Color.LTGRAY);
        trackFill.setStrokeWidth(10);
        trackFill.setStyle(Paint.Style.STROKE);

        setOnTouchListener(
                new OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        switch(event.getAction()) {
                            case ACTION_DOWN:
                                lastX = event.getX();
                                return true;
                            case ACTION_MOVE:
                                level = clamp(level + (event.getX() - lastX) / 100, 0, 1);
                                setLevel(level);
                                lastX = event.getX();
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

        int width = getWidth();
        int height = getHeight();
        int diameter = width > height ? height : width;
        int radius = diameter / 2 - 10;
        RectF rectF = new RectF();
        rectF.left = width / 2 - radius;
        rectF.top = height / 2 - radius;
        rectF.right = width / 2 + radius;
        rectF.bottom = height / 2 + radius;
        canvas.drawArc(rectF, 90+15, 330, false, trackFill);
        canvas.drawArc(rectF, 90+15, level * 330, false, valueFill);
    }
}
