package com.example.synth.ui;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import androidx.annotation.Nullable;

import java.util.ArrayList;
import java.util.List;

import static android.view.MotionEvent.*;

public class KeyboardView extends View {

    private static final Float WHITE_KEY_FREQUENCIES[] = {
        261.6256F, // C
        293.6648F, // D
        329.6276F, // E
        349.2282F, // F
        391.9954F, // G
        440.0000F, // A
        493.8833F  // B
    };

    private static final Float BLACK_KEY_FREQUENCIES[] = {
            277.1826F, // C#
            311.1270F, // D#
            369.9944F, // F#
            415.3047F, // G#
            466.1638F, // A#
    };

    private List<Rect> whiteKeyBounds = new ArrayList();
    private List<Rect> blackKeyBounds = new ArrayList();
    private Paint whiteKeyPaint;
    private Paint blackKeyPaint;
    private Paint hitKeyPaint;
    private Listener listener;

    private Rect pressedBounds = null;
    private boolean pressedWhiteKey = false;

    public KeyboardView(Context context) {
        super(context);

        init();
    }

    public KeyboardView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);

        init();
    }

    public KeyboardView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);

        init();
    }

    private void init() {
        whiteKeyPaint = new Paint();
        whiteKeyPaint.setColor(Color.BLACK);
        whiteKeyPaint.setStyle(Paint.Style.STROKE);
        whiteKeyPaint.setStrokeWidth(8);

        blackKeyPaint = new Paint();
        blackKeyPaint.setColor(Color.BLACK);
        blackKeyPaint.setStyle(Paint.Style.FILL_AND_STROKE);
        blackKeyPaint.setStrokeWidth(8);

        hitKeyPaint = new Paint();
        hitKeyPaint.setColor(0x99FF0000);
        hitKeyPaint.setStyle(Paint.Style.FILL_AND_STROKE);
        hitKeyPaint.setStrokeWidth(8);

        setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                pressedBounds = null;
                if (event.getAction() == ACTION_DOWN || event.getAction() == ACTION_MOVE) {
                    for (int i = 0; i < blackKeyBounds.size(); i++) {
                        if (blackKeyBounds.get(i).contains((int) event.getX(), (int) event.getY())) {
                            pressedBounds = blackKeyBounds.get(i);
                            pressedWhiteKey = false;
                            if (listener != null) {
                                listener.onKeyPressed(BLACK_KEY_FREQUENCIES[i] / 4);
                            }
                        }
                    }

                    if (pressedBounds == null) {
                        for (int i = 0; i < whiteKeyBounds.size(); i++) {
                            if (whiteKeyBounds.get(i).contains((int) event.getX(), (int) event.getY())) {
                                pressedBounds = whiteKeyBounds.get(i);
                                pressedWhiteKey = true;
                                if (listener != null) {
                                    listener.onKeyPressed(WHITE_KEY_FREQUENCIES[i] / 4);
                                }
                            }
                        }
                    }
                } else if (event.getAction() == ACTION_UP) {
                    if (listener != null) {
                        listener.onKeyReleased();
                    }
                }
                postInvalidate();
                return event.getAction() == ACTION_MOVE || event.getAction() == MotionEvent.ACTION_DOWN;
            }
        });
    }

    public void setListener(Listener listener) {
        this.listener = listener;
    }

    public void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

        updateKeyBounds();
    }

    @Override
    public void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        updateKeyBounds();
        for (Rect bounds : whiteKeyBounds) {
            canvas.drawRect(bounds, whiteKeyPaint);
        }

        if (pressedBounds != null && pressedWhiteKey) {
            canvas.drawRect(pressedBounds, hitKeyPaint);
        }

        for (Rect bounds : blackKeyBounds) {
            canvas.drawRect(bounds, blackKeyPaint);
        }

        if (pressedBounds != null && !pressedWhiteKey) {
            canvas.drawRect(pressedBounds, hitKeyPaint);
        }
    }

    private void updateKeyBounds() {
        int width = getWidth();
        int height = getHeight();
        float keyWidth = width / 7;

        whiteKeyBounds.clear();
        for (int i = 0; i < 7; i++) {
            Rect bounds = new Rect();
            bounds.left = (int) (i * keyWidth);
            bounds.top = 0;
            bounds.right = (int) ((i + 1) * keyWidth);
            bounds.bottom = height;
            whiteKeyBounds.add(bounds);
        }

        blackKeyBounds.clear();
        for (int i = 0; i < 6; i++) {
            if (i == 2) {
                continue;
            }
            Rect bounds = new Rect();
            bounds.left = (int) ((int) (i * keyWidth) + keyWidth * 3 / 4);
            bounds.top = 0;
            bounds.right = (int) ((int) ((i + 1) * keyWidth) + keyWidth / 4);
            bounds.bottom = height / 2;
            blackKeyBounds.add(bounds);
        }
    }

    public interface Listener {

        void onKeyPressed(float frequency);

        void onKeyReleased();
    }
}
