package com.example;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import com.example.JNI.CanMessage;
import com.example.JNI.Canlib;

@SpringBootApplication
public class Main {
    public static void main(String[] args) {
        SpringApplication.run(Main.class, args);
        Canlib canlib = new Canlib();
        int channel = 0;
        int flag = 0x0020;

        System.out.println("Inicializando liberia");
        canlib.initialize();

        System.out.println("Abriendo canal CAN");
        int handle = canlib.openChannel(channel, flag);

        if (handle < 0) {
            System.err.println("Error al abrir canal: " + handle);
            return;
        }

        System.out.println("Seteando Bus CAN");
        int status = canlib.setBusParams(handle, 500000L, 0, 0, 0, 0, 0);
        if (status < 0) {
            System.err.println("Error al configurar el bus: " + status);
            return;
        }

        System.out.println("Activando el bus...");
        status = canlib.busOn(handle);
        if (status < 0) {
            System.err.println("Error al activar el bus: " + status);
            return;
        }

        System.out.println("Esperando mensajes...");
        while (true) {
            CanMessage msg = canlib.readWait(handle, 5000); // timeout de 5 segundos
            if (msg != null) {
                System.out.printf("Mensaje recibido: ID=%d, DLC=%d, Timestamp=%d, Data=",
                        msg.id, msg.dlc, msg.timestamp);
                for (byte b : msg.data) {
                    System.out.printf("%02X ", b);
                }
                System.out.println();
            } else {
                System.out.println("Timeout o error al recibir mensaje.");
            }
        }
    }
}

/*
 * Activar canal CAN Virtual con: $ sudo modprobe kvvirtual
 * Comprobar si se cargo: $ lsmod | grep kvvirtualcan
 * Comprobar interfaces virtuales: $ ls /dev | grep can
 * 
 * OTRA FORMA SIN DRIVER KVASER
 * Agregar interfaz virtual CAN: $ sudo ip link add dev vcan0 type vcan
 * levantar intergaz virtual CAN: $ sudo ip link set up vcan0
 * Monitoreo de interfaz CAN: $ candump vcan0
 */