#ifndef PART1_AUDIOENGINE_H
#define PART1_AUDIOENGINE_H

#include <aaudio/AAudio.h>
#include "Renderer.h"

class AudioEngine {
public:
    bool start();
    void stop();
    void restart();
    void setToneOn(bool isToneOn);
    void setFrequency(float frequency);
    void setCutoff(float cutoff);
    void setFilterEnvAmt(float val);
    void setRes(float res);
    void setAttack(int32_t i, float val);
    void setDecay(int32_t i, float val);
    void setSustain(int32_t i, float val);
    void setRelease(int32_t i, float val);

private:
    Renderer renderer;
    AAudioStream *stream_;
};
#endif //PART1_AUDIOENGINE_H