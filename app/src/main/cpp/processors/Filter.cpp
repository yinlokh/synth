//
// Created by ericho921 on 5/17/19.
//

#include "Filter.h"

void Filter::set_sample_rate(int32_t sampleRate) {

}

float Filter::process(bool noteOn, int32_t t, float input) {
    buf0 += cutoff * (input - buf0 + feedback_amt * (buf0- buf1));
    buf1 += cutoff * (buf0 - buf1);
    buf2 += cutoff * (buf1 - buf2);
    buf3 += cutoff * (buf2 - buf3);
    buf4 += cutoff * (buf3 - buf4);
    buf5 += cutoff * (buf4 - buf5);
    switch (mode) {
        case LOW_PASS:
            return buf5;
        case HIGH_PASS:
            return input - buf5;
        case BAND_PASS:
            return buf0 - buf5;
    }
}