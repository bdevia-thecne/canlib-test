package com.example.JNA;

import com.sun.jna.Memory;
import com.sun.jna.Pointer;

public class CanService {
    
    private CanLibJNA canlib;
    private Integer handle;

    public CanService(Integer channel, Integer flag){
        try{
            canlib = CanLibJNA.INSTANCE;
            canlib.canInitializeLibrary();
            System.out.println("CanLibJNA instance " + canlib);

            openChannel(channel, flag);
            setBusParams();
            busOn();   
        } 
        catch(Exception e){
            System.err.println("Error al inicializar CANlib: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private void openChannel(Integer channel, Integer flag ){
        handle = canlib.canOpenChannel(channel, flag);
        if(handle < 0){
            System.err.println("Error al abrir el canal CAN: " + handle);
            return;
        } 
        System.out.println("Canal CAN abierto con handle: " + handle);
    }

    private void setBusParams(){
        Integer status = canlib.canSetBusParams(handle, 500000, 0, 0, 0, 0, 0);
        if(status < 0){
            System.out.println("Error al configurar los parámetros del bus CAN: " + status);
            return;
        }
        System.out.println("Parámetros del bus CAN configurados correctamente.");
    }

    private void busOn(){
        Integer status = canlib.canBusOn(handle);
        if(status < 0){
            System.out.println("Error al encender el bus CAN: " + status);
            return;
        } 
        System.out.println("Bus CAN encendido correctamente");
    }

    public void sendCanMessage(long id, byte[] message, int flag){
        Pointer msgPointer = new Memory(message.length);
        msgPointer.write(0, message, 0, message.length);

        System.out.println("Enviando mensaje CAN...");
        int status = canlib.canWrite(handle, id, msgPointer, message.length, flag);
        checkStatus("canWrite", status);

        status = canlib.canWriteSync(handle, 500);
        checkStatus("canWriteSync", status);

        System.out.println("Mensaje CAN enviado correctamente.");
    }

    private void checkStatus(String methodName, int status) {
        if (status != 0) {
            throw new RuntimeException(methodName + " falló con código de error: " + status);
        }
    }

}
