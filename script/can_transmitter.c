#include <stdio.h>
#include <stdlib.h>
#include <canlib.h>
#include <string.h>

//#define CHANNEL 0  // Usamos kvvirtualcan0
//#define ID 100     // Identificador CAN arbitrario

int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("Uso: %s <CHANNEL> <ID> <MESSAGE_HEX>\n", argv[0]);
        printf("Ejemplo: %s 0 200 0x1122334455667788\n", argv[0]);
        return 1;
    }

    int CHANNEL = atoi(argv[1]);
    int ID = (int)strtol(argv[2], NULL, 0);
    unsigned long long fullMsg = strtoull(argv[3], NULL, 0);

    unsigned char msg[8];
    for (int i = 0; i < 8; ++i) {
        msg[7 - i] = (fullMsg >> (i * 8)) & 0xFF;
    }

    canHandle handle;
    canStatus status;
    canInitializeLibrary();

    handle = canOpenChannel(CHANNEL, canOPEN_ACCEPT_VIRTUAL);
    if (handle < 0) {
        printf("Error al abrir canal: %d\n", handle);
        return 1;
    }

    canSetBusParams(handle, BAUD_500K, 0, 0, 0, 0, 0);
    canBusOn(handle);

    status = canWrite(handle, ID, msg, 8, canMSG_EXT);
    if (status != canOK) {
        printf("Error al enviar mensaje: %d\n", status);
    } else {
        printf("Mensaje enviado.\n");
    }

    canBusOff(handle);
    canClose(handle);
    return 0;
}

// gcc can_transmitter.c -o can_transmitter -lcanlib
// 0xEE11223344556D76 9C27DC29FFFFF323
/* 0x185F1F2E 0x010AFF3C7E001020*/
// 0X185F00FE
// 0x1860FEFE 0x010AFF3C7E001020
// 0xCF 00 40 FE 0xFFFF7E0000FFFFFF
// 0x0CF00400 0xFFFF7E0000FFFFFF
