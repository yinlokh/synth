#define TWO_PI (3.14159 * 2)
#define AMPLITUDE 0.3

#include <math.h>
#include "Oscillator.h"

void Oscillator::setSampleRate(int32_t sampleRate) {
    this->sampleRate = sampleRate;
    this->phase_increment = frequency / (float) sampleRate;
}

void Oscillator::set_frequency(int32_t frequency) {
    this->frequency = frequency;
    this->phase_increment = frequency / (float) sampleRate;
}

void Oscillator::set_waveform(Waveform w) {
    waveform = w;
}

float Oscillator::generate(bool noteOn, int32_t t) {
    double amp = AMPLITUDE;
    float val = 0;

    switch(waveform) {
        case SINE:
            val = (float) (sin(phase * TWO_PI) * amp);
            break;
        case SAW:
            val = (float) amp * phase;
            break;
        case SQUARE:
            val = (float) amp * (phase > 0.5 ? -1 : 1);
            break;
        case TRIANGLE:
            val = (float) amp * (phase > 0.5 ? 1 - phase : phase * 2);
            break;
    }

    phase += phase_increment;
    phase = phase > 1 ? phase - 1 : phase;
    return val;
}