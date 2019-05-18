#define TWO_PI (3.14159 * 2)

#include <math.h>
#include "Oscillator.h"

void Oscillator::set_sample_rate(int32_t sampleRate) {
    this->sampleRate = sampleRate;
    this->phase_increment = frequency / (float) sampleRate;
}

void Oscillator::set_frequency(double frequency) {
    this->frequency = frequency;
    this->phase_increment = frequency / (float) sampleRate;
}

void Oscillator::set_waveform(Waveform w) {
    waveform = w;
}

void Oscillator::set_phase(float phase) {
    this->phase = phase;
}

float Oscillator::generate() {
    float val = 0;

    phase = phase > 1 ? phase - 1 : phase;

    switch(waveform) {
        case SINE:
            val = (float) (sin(phase * TWO_PI));
            break;
        case SAW:
            val = phase * 2 - 1;
            break;
        case SQUARE:
            val = (float) (phase > 0.5 ? 1 : -1);
            break;
        case TRIANGLE:
            val = (float) 1 - abs(phase - 0.5f) * 2;
            break;
    }

    phase += phase_increment;
    return val;
}