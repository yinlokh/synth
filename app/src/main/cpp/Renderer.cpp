#include "Renderer.h"
#include "oscillators/SineOsc.h"
#include "processors/ADSR.h"
#include <math.h>

Renderer::Renderer() {
    generator = new SineOsc();
    adsr = new ADSR();
}

void Renderer::setSampleRate(int32_t sampleRate) {
    generator->setSampleRate(sampleRate);
}

void Renderer::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Renderer::render(float *audioData, int32_t numFrames) {
    for (int i = 0; i < numFrames; i++) {
        bool note_on = isWaveOn_.load();
        audioData[i] = adsr->process(note_on, counter, generator->generate(note_on, counter));
        counter++;
    }
}