#include <stdio.h>
#include <stdlib.h>
#include <canlib.h>
#include <unistd.h>  // Para sleep()

#define CHANNEL 0  // Usamos kvvirtualcan0
#define ID 100     // Identificador CAN arbitrario

int main() {
    canHandle handle;
    canStatus status;
    unsigned char msg[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    canInitializeLibrary();

    handle = canOpenChannel(CHANNEL, canOPEN_ACCEPT_VIRTUAL);
    if (handle < 0) {
        printf("Error al abrir canal: %d\n", handle);
        return 1;
    }

    canSetBusParams(handle, BAUD_500K, 0, 0, 0, 0, 0);
    canBusOn(handle);

    status = canWrite(handle, ID, msg, 8, 0);
    if (status != canOK) {
        printf("Error al enviar mensaje: %d\n", status);
    } else {
        printf("Mensaje enviado.\n");
    }

    canBusOff(handle);
    canClose(handle);
    return 0;
}
