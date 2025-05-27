package com.example.JNI;

public class Canlib {

    static {
        System.load("/home/benja/Escritorio/test/metech/program/jni/libcanlib_jni.so");
    }

    public native void initialize();
    public native int openChannel(int channel, int flags);
    public native int setBusParams(int hnd, long freq, int tseg1, int tseg2, int sjw, int noSamp, int syncmode);
    public native int busOn(int handle);
    public native CanMessage readWait(int handle, int timeOutMs);
    public native int bussOff(int handle);
    public native int close(int handle);    
}


/*
 * javac -d . src/main/java/com/adaq/can/Canlib.java --> Compila el canlib.java a bytecode .class (ejecutable en JVM)
 * javac -h jni src/main/java/com/adaq/can/Canlib.java
 */