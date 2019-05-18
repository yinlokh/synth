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

private:
    Renderer renderer;
    AAudioStream *stream_;
};
#endif //PART1_AUDIOENGINE_H