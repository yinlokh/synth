//
// Generator interface, outputs frames.
//
#include <stdint.h>

#ifndef generator_h
#define generator_h

class Generator {
public:
    virtual void set_sample_rate(int32_t sampleRate) = 0;
    virtual float generate() = 0;
};

#endif