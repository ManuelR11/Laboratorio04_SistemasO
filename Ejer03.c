#include <stdio.h>
#include <stdbool.h>

#define NUM_RECURSOS 3
#define NUM_PROCESOS 5

// Función para comprobar si el sistema se encuentra en un estado seguro
bool estadoSeguro(int disponibles[], int asignados[][NUM_RECURSOS], int maximos[][NUM_RECURSOS], bool finalizados[]) {
    int trabajo[NUM_RECURSOS];
    bool seguro = true;
    int i, j;

    // Inicializar el vector de trabajo con los recursos disponibles
    for (i = 0; i < NUM_RECURSOS; i++) {
        trabajo[i] = disponibles[i];
    }

    // Marcar los procesos finalizados como true
    for (i = 0; i < NUM_PROCESOS; i++) {
        if (finalizados[i] == true) {
            continue;
        }

        // Verificar si los recursos necesarios para este proceso están disponibles
        bool recursosSuficientes = true;
        for (j = 0; j < NUM_RECURSOS; j++) {
            if (maximos[i][j] - asignados[i][j] > trabajo[j]) {
                recursosSuficientes = false;
                break;
            }
        }

        if (recursosSuficientes) {
            // Si hay recursos suficientes, se ejecutará este proceso
            finalizados[i] = true;
            printf("Proceso %d ejecutado.\n", i);
            for (j = 0; j < NUM_RECURSOS; j++) {
                trabajo[j] += asignados[i][j];
            }
            seguro = true;
        }
    }

    // Si todos los procesos no están finalizados, el sistema está en un estado inseguro
    for (i = 0; i < NUM_PROCESOS; i++) {
        if (finalizados[i] == false) {
            seguro = false;
            break;
        }
    }

    return seguro;
}

int main() {
    int disponibles[NUM_RECURSOS] = {10, 5, 7}; // Recursos disponibles

    // Matrices para el estado actual de asignaciones y los máximos recursos necesarios para cada proceso
    int asignados[NUM_PROCESOS][NUM_RECURSOS] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maximos[NUM_PROCESOS][NUM_RECURSOS] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    bool finalizados[NUM_PROCESOS] = {false};

    printf("Ejecución de procesos:\n");
    if (estadoSeguro(disponibles, asignados, maximos, finalizados)) {
        printf("El sistema se encuentra en un estado seguro.\n");
    } else {
        printf("El sistema se encuentra en un estado inseguro.\n");
    }

    return 0;
}
