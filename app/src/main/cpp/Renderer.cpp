#include "Renderer.h"
#include "oscillators/SineOsc.h"
#include <math.h>

Renderer::Renderer() {
    generator = new SineOsc();
}

void Renderer::setSampleRate(int32_t sampleRate) {
    generator->setSampleRate(sampleRate);
}

void Renderer::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Renderer::render(float *audioData, int32_t numFrames) {
    for (int i = 0; i < numFrames; i++) {
        audioData[i] = generator->generate(isWaveOn_.load(), counter);
        counter++;
    }
}