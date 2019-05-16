#define FREQUENCY 250.0

#include "Renderer.h"
#include "oscillators/Oscillator.h"
#include "processors/ADSR.h"
#include <math.h>

Renderer::Renderer() {
    for (int i = 0; i < 10; i++) {
        generator[i] = new Oscillator();
        generator[i]->set_waveform(SAW);
        generator[i]->set_frequency(FREQUENCY  + 1.5 * i);
    }
    adsr = new ADSR();
}

void Renderer::setSampleRate(int32_t sampleRate) {
    for (int i = 0; i < 10; i++) {
        generator[i]->setSampleRate(sampleRate);
    }
}

void Renderer::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Renderer::render(float *audioData, int32_t numFrames) {
    for (int i = 0; i < numFrames; i++) {
        bool note_on = isWaveOn_.load();
        float val = 0;
        for (int j = 0; j < 10; j++) {
            val += 0.1 * generator[j]->generate(note_on, counter);
        }
        audioData[i] = adsr->process(note_on, counter, val);
        counter++;
    }
}