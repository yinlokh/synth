#ifndef SYNTH_ADSR_H
#define SYNTH_ADSR_H

#include <stdint.h>
#include "../interfaces/Processor.h"

class ADSR : public Processor {
public:

    float process(bool noteOn, int32_t t, float input);

    void set_sample_rate(int32_t sample_rate);

    void set_attack(int32_t attack);

    void set_decay(int32_t decay);

    void set_sustain(float sustain);

    void set_release(int32_t release);

private:
    int32_t a = 10000;
    int32_t d = 10000;
    float s = 0.5;
    int32_t r = 10000;
    int32_t sample_rate;
    int32_t frames;
    int32_t release_frames;
    bool at_rest = true;
};


#endif //SYNTH_ADSR_H
