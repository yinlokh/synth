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

    void set_frequency(double frequency);

    void set_sample_rate(int32_t sampleRate);

    void set_phase(float phase);

    float generate();

private:
    Waveform waveform = SINE;
    int32_t sampleRate;
    double frequency;
    float phase = 0;
    double phase_increment = 0;
};

#endif //SYNTH_SINEOSC_H
