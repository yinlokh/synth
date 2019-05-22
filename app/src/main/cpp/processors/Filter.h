//
// Created by ericho921 on 5/17/19.
//

#ifndef SYNTH_FILTER_H
#define SYNTH_FILTER_H


#include <math.h>
#include "../interfaces/Processor.h"

class Filter : public Processor {
public:
    enum Mode {
        LOW_PASS,
        HIGH_PASS,
        BAND_PASS
    };
    void set_sample_rate(int32_t sampleRate);
    float process(bool noteOn, int32_t t, float input);
    void set_cutoff(float cutoff) {this->cutoff = cutoff; calculate_feedback_amt();}
    void set_res(float res) {this->res = res; calculate_feedback_amt();}
private:
    inline void calculate_feedback_amt() { feedback_amt = res + res / (1.0f - fmax(0.f , fmin(0.9999999999999f, cutoff))); }

    float cutoff;
    float res = 0.00000;
    Mode mode = LOW_PASS;
    float feedback_amt;
    float buf0;
    float buf1;
    float buf2;
    float buf3;
    float buf4;
    float buf5;
};


#endif //SYNTH_FILTER_H
