#define FREQUENCY 80
#define AMPLITUDE 0.3

#include "Renderer.h"
#include "oscillators/Oscillator.h"
#include "processors/ADSR.h"
#include <math.h>

Renderer::Renderer() {
    for (int i = 0; i < osc_count; i++) {
        generator[i] = new Oscillator();
        generator[i]->set_waveform(SQUARE);
        generator[i]->set_frequency(FREQUENCY  + 2 * i);
        generator[i]->set_phase(0.9 * i);
    }

    lfo = new Oscillator();
    lfo->set_frequency(0.05);
    lfo->set_waveform(SINE);
    adsr = new ADSR();
    adsr->set_attack(300);
    adsr->set_decay(12000);
    adsr->set_sustain(1.0);
    adsr->set_release(12000);

    adsr2 = new ADSR();
    adsr2->set_attack(300);
    adsr2->set_decay(5000);
    adsr2->set_sustain(0);
    adsr2->set_release(12000);
}

void Renderer::setSampleRate(int32_t sampleRate) {
    for (int i = 0; i < osc_count; i++) {
        generator[i]->set_sample_rate(sampleRate);
    }
    lfo->set_sample_rate(sampleRate);
}

void Renderer::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Renderer::setFrequency(float frequency) {
    this->frequency = frequency;
}

void Renderer::render(float *audioData, int32_t numFrames) {
    for (int i = 0; i < numFrames; i++) {
        bool note_on = isWaveOn_.load();
        float osc_output = 0;
        float freq_mod = 0;

        for (int j = 0; j < osc_count; j++) {
            generator[j]->set_frequency(frequency + freq_mod + 1 * j);
            osc_output += 1.0 / osc_count * generator[j]->generate();
        }

        osc_output *= AMPLITUDE;
        audioData[i] = adsr->process(note_on, counter, osc_output);
        counter++;
    }
}