package com.example.synth.util;

public class Validation {

    private Validation() { }

    public static float clamp(float input, float min, float max) {
        return input > min ? (input < max ? input : max) :min;
    }
}
