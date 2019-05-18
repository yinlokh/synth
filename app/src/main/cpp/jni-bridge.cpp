#include <jni.h>
#include <android/input.h>
#include "AudioEngine.h"

static AudioEngine *audioEngine = new AudioEngine();

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_synth_MainActivity_touchEvent(JNIEnv *env, jobject obj, jint action, jfloat x, jfloat y) {
    switch (action) {
        case AMOTION_EVENT_ACTION_DOWN :
            audioEngine->setToneOn(true);
            audioEngine->setFrequency(y);
            break;
        case AMOTION_EVENT_ACTION_UP :
            audioEngine->setToneOn(false);
            break;
        case AMOTION_EVENT_ACTION_MOVE :
            audioEngine->setFrequency(y);
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