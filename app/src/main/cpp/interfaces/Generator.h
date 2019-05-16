//
// Generator interface, outputs frames.
//
#include <stdint.h>

#ifndef generator_h
#define generator_h

class Generator {
public:
    virtual void setSampleRate(int32_t sampleRate) = 0;
    virtual float generate(bool noteOn, int32_t t) = 0;
};

#endif