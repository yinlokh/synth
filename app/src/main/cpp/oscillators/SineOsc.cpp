#define TWO_PI (3.14159 * 2)
#define AMPLITUDE 0.3
#define FREQUENCY 440.0

#include <math.h>
#include "SineOsc.h"

 SineOsc::SineOsc(){

}

SineOsc::~SineOsc() {

}

void SineOsc::setSampleRate(int32_t sampleRate) {
    this->sampleRate = sampleRate;
}

float SineOsc::generate(bool noteOn, int32_t t) {
    releaseTime = !noteOn && releaseTime == 0 ? t : releaseTime;
    double increment = (TWO_PI * FREQUENCY) / (double) sampleRate;
    double amp = AMPLITUDE * (noteOn ? 1 : fmax(0, (1000 - (t - releaseTime)) / 1000));
    float val = (float) (sin(increment * t) * amp);
    return val;
}