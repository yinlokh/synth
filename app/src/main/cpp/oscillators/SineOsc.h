#include <stdint.h>
#include "../interfaces/Generator.h"
#ifndef SYNTH_SINEOSC_H
#define SYNTH_SINEOSC_H

class SineOsc : public Generator {
public:

    SineOsc();

    ~SineOsc();

    void setSampleRate(int32_t sampleRate);

    float generate(bool noteOn, int32_t t);

private:
    int32_t sampleRate;
    int32_t releaseTime = 0;
};

#endif //SYNTH_SINEOSC_H
