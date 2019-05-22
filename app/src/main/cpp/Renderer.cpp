#define FREQUENCY 300
#define AMPLITUDE 0.3

#include "Renderer.h"
#include "oscillators/Oscillator.h"
#include "processors/ADSR.h"
#include <math.h>

Renderer::Renderer() {
    for (int i = 0; i < osc_count; i++) {
        generator[i] = new Oscillator();
        generator[i]->set_waveform(SAW);
        generator[i]->set_frequency(FREQUENCY  + FREQUENCY / 24 * i);
        generator[i]->set_phase(0.9 * i);
    }

    lfo = new Oscillator();
    lfo->set_frequency(2);
    lfo->set_waveform(SINE);

    filter = new Filter();
    filter->set_cutoff(0.5);
    filter->set_res(0.3);

    for (int i = 0; i < 2; i++) {
        adsr[i] = new ADSR();
        adsr[i]->set_attack(10);
        adsr[i]->set_decay(12000);
        adsr[i]->set_sustain(1);
        adsr[i]->set_release(12000);
    }
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

void Renderer::setCutoff(float cutoff) {
    this->cutoff = cutoff;
}

void Renderer::setFilterEnvAmt(float val) {
    this->filter_env_amt = val;
}

void Renderer::setRes(float res) {
    this->res = res;
}

void Renderer::setAttack(int32_t i, float val) {
    this->adsr[i]->set_attack(val);
}

void Renderer::setDecay(int32_t i, float val) {
    this->adsr[i]->set_decay(val);
}

void Renderer::setSustain(int32_t i, float val) {
    this->adsr[i]->set_sustain(val);
}

void Renderer::setRelease(int32_t i, float val) {
    this->adsr[i]->set_release(val);
}

void Renderer::render(float *audioData, int32_t numFrames) {
    for (int i = 0; i < numFrames; i++) {
        bool note_on = isWaveOn_.load();
        float osc_output = 0;
        float freq_mod = 0;

        for (int j = 0; j < osc_count; j++) {
            generator[j]->set_frequency(frequency + freq_mod + frequency / 60 * j);
            osc_output += 1.0 / osc_count * generator[j]->generate();
        }

        osc_output *= AMPLITUDE;

        float adsr2_output = adsr[1]->process(note_on, counter, 1.f);
        this->filter->set_cutoff(fmin(fmax(cutoff + filter_env_amt * adsr2_output, 0.f), 1.f));
        this->filter->set_res(res);

        float filter_output = filter->process(note_on, counter, osc_output);
        audioData[i] = adsr[0]->process(note_on, counter, filter_output);
        counter++;
    }
}