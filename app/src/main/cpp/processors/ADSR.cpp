#include <math.h>
#include "ADSR.h"

float ADSR::process(bool noteOn, int32_t t, float input) {
    float level = 0.0;

    frames = at_rest ? 0 : frames;

    if (!noteOn && !at_rest) {
        level = s * fmax(0.0f, (r - release_frames) / (float) r);
        at_rest = level == 0;
    } else if (noteOn) {
        at_rest = false;
        release_frames = 0;
        if (frames < a) {
            level = 1.0f * frames / a;
        } else if (frames - a < d) {
            level = (1.0f - s) + s * fmax(0.0f, (d - frames + a) / (float) d);
        } else {
            level = s;
        }
    }

    frames++;
    release_frames++;
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