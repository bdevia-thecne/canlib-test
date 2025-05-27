#include <jni.h>
#include "com_example_JNI_Canlib.h"
#include <canlib.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_example_JNI_Canlib_initialize(JNIEnv *env, jobject obj){
    return canInitializeLibrary();
}

JNIEXPORT jint JNICALL Java_com_example_JNI_Canlib_openChannel(JNIEnv *env, jobject obj, jint channel, jint flags){
    return canOpenChannel(channel, flags);
}

JNIEXPORT jint JNICALL Java_com_example_JNI_Canlib_setBusParams(JNIEnv *env, jobject obj, jint hnd, jlong freq, jint tseg1, jint tseg2, jint sjw, jint noSamp, jint syncmode){
    return canSetBusParams(hnd, freq, tseg1, tseg2, sjw, noSamp, syncmode);
}

JNIEXPORT jint JNICALL Java_com_example_JNI_Canlib_busOn(JNIEnv *env, jobject obj, jint hnd){
    return canBusOn(hnd);
}

JNIEXPORT jobject JNICALL Java_com_example_JNI_Canlib_readWait(JNIEnv *env, jobject obj, jint hnd, jint timeOutMs){
    long id;
    unsigned char msg[8];
    unsigned int dlc;
    unsigned int flag;
    unsigned long timestamp;
    
    canStatus status = canReadWait(hnd, &id, msg, &dlc, &flag, &timestamp, timeOutMs);
    if(status != canOK){
        return NULL; // TODO: Lanzar excepcion
    }
    // Creamos array Java
    jbyteArray dataArray = (*env)->NewByteArray(env, dlc);
    (*env)->SetByteArrayRegion(env, dataArray, 0, dlc, (jbyte *)msg);

    // Creamos objeto CanMessage
    jclass cls = (*env)->FindClass(env, "com/example/JNI/CanMessage");
    jmethodID constructor = (*env)->GetMethodID(env, cls, "<init>", "(J[BIJ)V");
    return (*env)->NewObject(env, cls, constructor, (jlong)id, dataArray, (jint)dlc, (jlong)timestamp);
}

JNIEXPORT jint JNICALL Java_com_example_JNI_Canlib_bussOff(JNIEnv *env, jobject obj, jint hnd){
    return canBusOff(hnd);
}

JNIEXPORT jint JNICALL Java_com_example_JNI_Canlib_close(JNIEnv *env, jobject obj, jint hnd){
    return canClose(hnd);
}


/* 
gcc -fPIC \
    -I${JAVA_HOME}/include \
    -I${JAVA_HOME}/include/linux \
    -shared -o libcanlib_jni.so \
    jni/CanlibJNI.c -lcanlib
*/