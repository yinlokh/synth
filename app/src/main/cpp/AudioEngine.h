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

private:
    Renderer oscillator_;
    AAudioStream *stream_;
};
#endif //PART1_AUDIOENGINE_H