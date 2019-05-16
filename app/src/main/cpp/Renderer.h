#include <atomic>
#include <stdint.h>
#include "interfaces/Generator.h"
#include "oscillators/Oscillator.h"
#include "interfaces/Processor.h"

class Renderer {
public:
    Renderer();
    void setWaveOn(bool isWaveOn);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);

private:
    std::atomic<bool> isWaveOn_{false};
    int32_t counter = 0;
    Oscillator* generator[10];
    Processor* adsr;
};