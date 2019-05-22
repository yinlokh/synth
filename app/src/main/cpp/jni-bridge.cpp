#include <jni.h>
#include <android/input.h>
#include "AudioEngine.h"

static AudioEngine *audioEngine = new AudioEngine();

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_onFilterCutoff(JNIEnv *env, jobject obj, jfloat cutoff) {
    audioEngine->setCutoff(cutoff);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_onFilterRes(JNIEnv *env, jobject obj, jfloat res) {
    audioEngine->setRes(res);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_onFilterEnvAmt(JNIEnv *env, jobject obj, jfloat val) {
    audioEngine->setFilterEnvAmt(val);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_setAttack(JNIEnv *env, jobject obj, jint id, jfloat val) {
    audioEngine->setAttack(id, val * 50000);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_setDecay(JNIEnv *env, jobject obj, jint id, jfloat val) {
    audioEngine->setDecay(id, val * 50000);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_setSustain(JNIEnv *env, jobject obj, jint id, jfloat val) {
    audioEngine->setSustain(id, val);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_setRelease(JNIEnv *env, jobject obj, jint id, jfloat val) {
    audioEngine->setRelease(id, val * 50000);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_onKeyPressed(JNIEnv *env, jobject obj, jfloat freq) {
    audioEngine->setFrequency(freq);
    audioEngine->setToneOn(true);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_onKeyReleased(JNIEnv *env, jobject obj) {
    audioEngine->setToneOn(false);
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_touchEvent(JNIEnv *env, jobject obj, jint action, jfloat x, jfloat y) {
    switch (action) {
        case AMOTION_EVENT_ACTION_DOWN :
            audioEngine->setToneOn(true);
            audioEngine->setFrequency(y/2);
            break;
        case AMOTION_EVENT_ACTION_UP :
            audioEngine->setToneOn(false);
            break;
        case AMOTION_EVENT_ACTION_MOVE :
            audioEngine->setFrequency(y/2);
            break;
        default :
            break;
    }
}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_startEngine(JNIEnv *env, jobject /* this */) {
    audioEngine->start();

}

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_stopEngine(JNIEnv *env, jobject /* this */) {
    audioEngine->stop();

}

}