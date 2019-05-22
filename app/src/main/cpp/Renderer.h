#include <atomic>
#include <stdint.h>
#include "interfaces/Generator.h"
#include "oscillators/Oscillator.h"
#include "interfaces/Processor.h"
#include "processors/ADSR.h"
#include "processors/Filter.h"

class Renderer {
public:
    Renderer();
    void setWaveOn(bool isWaveOn);
    void setFrequency(float frequency);
    void setCutoff(float cutoff);
    void setFilterEnvAmt(float val);
    void setRes(float res);
    void setAttack(int32_t i, float val);
    void setDecay(int32_t i, float val);
    void setSustain(int32_t i, float val);
    void setRelease(int32_t i, float val);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);

private:
    std::atomic<bool> isWaveOn_{false};
    int32_t counter = 0;
    Oscillator* generator[1];
    ADSR* adsr[2];
    Oscillator* lfo;
    Filter* filter;
    int32_t osc_count = 1;
    float frequency = 300;
    float cutoff;
    float res;
    float filter_env_amt;
};