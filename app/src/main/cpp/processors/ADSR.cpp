#include <math.h>
#include <android/log.h>
#include <string>
#include "ADSR.h"

float ADSR::process(bool noteOn, int32_t t, float input) {
    float level = 0.0;

    if (noteOn && !was_note_on) {
        frames = 0;
        was_note_on = true;
        at_rest = false;
    } else if (!noteOn && was_note_on) {
        frames = 0;
        was_note_on = false;
    }

    if (noteOn) {
        if (frames < a) {
            // attack
            level = interpolate(0.f, 1.f, (float) frames / (float) a);
        } else if (frames < d + a) {
            int32_t d_frames = frames - a;
            // decay
            level = interpolate(1.f, s, (float) d_frames / (float) d);
        } else {
            // sustain
            level = s;
        }
        release_level = level;
    } else if (!noteOn && !at_rest) {
        // release
        level = interpolate(fmin(s, release_level), 0.f, (float) frames / (float) r);
        at_rest = level == 0;
    }
//
//    std::string msg = "Level = " + std::to_string(level);
//    __android_log_write(ANDROID_LOG_ERROR, "Synth",  msg.data());

    frames++;
    return input * level;
}

void ADSR::set_sample_rate(int32_t sample_rate) {
    this->sample_rate = sample_rate;
}

void ADSR::set_attack(int32_t attack) {
    a = attack;
}

void ADSR::set_decay(int32_t decay) {
    d = decay;
}

void ADSR::set_sustain(float sustain) {
    s = sustain;
}

void ADSR::set_release(int32_t release) {
    r = release;
}

float ADSR::interpolate(float v1, float v2, float p) {
    return v1 + (v2 - v1) * fmin(fmax(p, 0.f), 1.f);
}