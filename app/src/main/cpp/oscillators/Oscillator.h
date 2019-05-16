#include <stdint.h>
#include "../interfaces/Generator.h"
#ifndef SYNTH_SINEOSC_H
#define SYNTH_SINEOSC_H

enum Waveform {
    SINE,
    TRIANGLE,
    SQUARE,
    SAW
};

class Oscillator : public Generator {
public:

    void set_waveform(Waveform w);

    void set_frequency(int32_t frequency);

    void setSampleRate(int32_t sampleRate);

    float generate(bool noteOn, int32_t t);

private:
    Waveform waveform = SINE;
    int32_t sampleRate;
    int32_t frequency;
    float phase = 0;
    double phase_increment = 0;
};

#endif //SYNTH_SINEOSC_H
