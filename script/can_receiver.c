#include <stdio.h>
#include <stdlib.h>
#include <canlib.h>

#define CHANNEL 0  // Usamos kvvirtualcan1

int main() {
    canHandle handle;
    canStatus status;
    long id;
    unsigned char msg[8];
    unsigned int dlc;
    unsigned int flag;
    unsigned long timestamp;

    canInitializeLibrary();

    handle = canOpenChannel(CHANNEL, canOPEN_ACCEPT_VIRTUAL);
    if (handle < 0) {
        printf("Error al abrir canal: %d\n", handle);
        return 1;
    }

    canSetBusParams(handle, BAUD_500K, 0, 0, 0, 0, 0);
    canBusOn(handle);

    printf("Esperando mensajes...\n");
    while (1) {
        status = canReadWait(handle, &id, msg, &dlc, &flag, &timestamp, 5000);
        if (status == canOK) {
            printf("Mensaje recibido: ID=%ld, Data=", id);
            for (int i = 0; i < dlc; i++) {
                printf("%02X ", msg[i]);
            }
            printf("\n");
        } else {
            printf("Error o timeout al recibir.\n");
        }
    }

    canBusOff(handle);
    canClose(handle);
    return 0;
}

// gcc can_transmitter.c -o can_transmitter -lcanlib