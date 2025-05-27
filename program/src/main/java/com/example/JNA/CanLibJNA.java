package com.example.JNA;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

public interface CanLibJNA extends Library {

    CanLibJNA INSTANCE = Native.load("/usr/lib/libcanlib.so", CanLibJNA.class);
    Integer CAN_OPEN_ACCEPT_VIRTUAL = 0x0020;

    /* Metodos de la Libretia  */
    void canInitializeLibrary();
    
    Integer canOpenChannel(int channel, int flags);

    Integer canSetBusParams(int hnd, long freq, int tseg1, int tseg2, int sjw, int noSamp, int syncmode);

    Integer canBusOn(int hnd);

    Integer canWrite(int hnd, long id, Pointer msg, int dlc, int flag);
    
    Integer canWriteSync(int hnd, long timeout);

}
