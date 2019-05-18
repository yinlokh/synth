#include <atomic>
#include <stdint.h>
#include "interfaces/Generator.h"
#include "oscillators/Oscillator.h"
#include "interfaces/Processor.h"
#include "processors/ADSR.h"

class Renderer {
public:
    Renderer();
    void setWaveOn(bool isWaveOn);
    void setFrequency(float frequency);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);

private:
    std::atomic<bool> isWaveOn_{false};
    int32_t counter = 0;
    Oscillator* generator[5];
    Oscillator* lfo;
    ADSR* adsr;
    ADSR* adsr2;
    int32_t osc_count = 5;
    float frequency;
};