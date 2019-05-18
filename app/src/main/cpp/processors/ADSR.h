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
    float interpolate(float a, float b, float p);

    int32_t a = 300;
    int32_t d = 50000;
    float s = 0.5f;
    int32_t r = 50000;
    int32_t sample_rate;
    int32_t frames;
    bool at_rest = true;
    bool was_note_on = false;
    float release_level = 0.f;
};


#endif //SYNTH_ADSR_H
