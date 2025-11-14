/********************************************************************************************
                         Pontificia Universidad Javeriana
Autores: Juliana Aguirre Ballesteros 
 Juan Carlos Santamaria Orjuela
Materia: sistemas operativos
Profesor: j. corredor
Taller 03 Posix Semáforos
Descripcion: este programa implementa el proceso consumidor del problema
productor–consumidor usando memoria compartida y semáforos POSIX.
El consumidor se conecta a un búfer circular que otro proceso ya creó y llena,
toma los valores que haya disponibles y los muestra por pantalla respetando la
sincronización. se usa un semáforo para contar los espacios llenos y otro para
contar los espacios vacíos, evitando que el consumidor lea cuando el búfer está
vacío y manteniendo el orden de salida.
Objetivos:
- practicar el uso básico de semáforos POSIX con nombre para sincronizar procesos.
- leer datos de una zona de memoria compartida de forma segura.
- entender el flujo clásico productor–consumidor con un búfer circular sencillo.
- cerrar y liberar correctamente los recursos usados por el proceso consumidor.
***************************************************************************************/

#include "shared.h"

int main() {
    // abre los semáforos existentes usando sus nombres (no los crea, solo los usa)
    sem_t *vacio = sem_open(SEM_VACIO, 0);
    sem_t *lleno = sem_open(SEM_LLENO, 0);
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");       // muestra un mensaje si hubo error al abrir los semáforos
        exit(EXIT_FAILURE);       // termina el programa porque no hay sincronización válida
    }

    // abre el objeto de memoria compartida donde está el búfer circular
    int fd_compartido = shm_open(SHM_NAME, O_RDWR, 0644);
    if (fd_compartido < 0) {
        perror("shm_open");       // muestra un mensaje si hubo error al abrir la shm
        exit(EXIT_FAILURE);       // termina el programa porque no puede acceder al búfer
    }

    // mapea la memoria compartida en el espacio de direcciones del proceso
    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos),
                                      PROT_READ | PROT_WRITE, MAP_SHARED, fd_compartido, 0);
    if (compartir == MAP_FAILED) {
        perror("mmap");           // muestra un mensaje si hubo error al mapear la memoria
        exit(EXIT_FAILURE);       // termina el programa porque no puede usar la estructura
    }

    // recorre un ciclo donde consume 10 elementos del búfer compartido
    for (int i = 1; i <= 10; i++) {
        sem_wait(lleno);                         // espera a que haya al menos un elemento lleno
        int item = compartir->bus[compartir->salida];   // toma el elemento en la posición de salida
        printf("Consumidor: Consume %d\n", item);       // muestra el valor consumido en la consola
        compartir->salida = (compartir->salida + 1) % BUFFER; // avanza la posición de salida en forma circular
        sem_post(vacio);                         // informa que ahora hay un espacio vacío disponible
        sleep(2);                                // pausa para ver mejor el consumo paso a paso
    }

    // libera el mapeo de memoria y cierra el descriptor del área compartida
    munmap(compartir, sizeof(compartir_datos));  // deja de usar la región de memoria compartida
    close(fd_compartido);                        // cierra el archivo de memoria compartida

    // cierra los semáforos en este proceso
    sem_close(lleno);                            // cierra el semáforo que cuenta espacios llenos
    sem_close(vacio);                            // cierra el semáforo que cuenta espacios vacíos

    // aquí se eliminan del sistema el semáforo /lleno y la memoria compartida
    // esto borra los objetos globales para que no queden recursos colgados
    sem_unlink(SEM_LLENO);
    shm_unlink(SHM_NAME);

    return 0;                                    // fin correcto del proceso consumidor
}
