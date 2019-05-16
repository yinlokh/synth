#include <stdint.h>
#ifndef SYNTH_PROCESSOR_H
#define SYNTH_PROCESSOR_H

class Processor {
public:
    virtual void set_sample_rate(int32_t sampleRate) = 0;
    virtual float process(bool noteOn, int32_t t, float input) = 0;
};


#endif //SYNTH_PROCESSOR_H
