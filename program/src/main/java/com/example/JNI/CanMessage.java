package com.example.JNI;

public class CanMessage {
    public long id;
    public byte[] data;
    public int dlc;
    public long timestamp;
    
    public CanMessage(long id, byte[] data, int dlc, long timestamp){
        this.id = id;
        this.data = data;
        this.dlc = dlc;
        this.timestamp = timestamp;
    }
}
