/********************************************************************************************
                         Pontificia Universidad Javeriana
Autores: Juliana Aguirre Ballesteros 
         Juan Carlos Santamaria Orjuela
Materia: sistemas operativos
Profesor: j. corredor
Taller 03 Posix Semáforos

Descripcion:
Este programa implementa el proceso productor del problema clásico 
productor–consumidor usando semáforos POSIX con nombre y memoria compartida.
El productor es el encargado de crear o abrir los semáforos y la memoria 
compartida, preparar el búfer circular desde cero y comenzar a colocar valores 
en él. Cada dato producido se guarda en una posición del búfer y se avanza 
de forma circular para mantener un flujo continuo.

El semáforo "vacio" indica cuántos espacios libres quedan en el búfer, y el 
semáforo "lleno" indica cuántas posiciones ya tienen datos. El productor espera 
si no quedan espacios vacíos, y avanza solo cuando el consumidor libera espacio. 
También inicializa la estructura compartida para que ambos procesos tengan un 
estado consistente desde el inicio.

Objetivos:
- crear e inicializar semáforos POSIX con nombre para coordinar procesos.
- crear e inicializar memoria compartida donde se guardan los datos del búfer.
- producir valores de manera ordenada y almacenarlos en un búfer circular.
- garantizar que el acceso al búfer esté sincronizado mediante semáforos.
- liberar recursos del sistema como semáforos y memoria compartida.
********************************************************************************************/

#include "shared.h"

int main() {
    // abre o crea los semáforos con valores iniciales para vacíos y llenos
    sem_t *vacio = sem_open(SEM_VACIO, O_CREAT, 0644, BUFFER);
    sem_t *lleno = sem_open(SEM_LLENO, O_CREAT, 0644, 0);
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");                // muestra error si el semáforo falla
        exit(EXIT_FAILURE);                // termina porque no hay sincronización válida
    }

    // crea o abre el área de memoria compartida que contendrá el búfer circular
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0644);
    if (shm_fd < 0) {
        perror("shm_open");                // muestra error si no se pudo abrir/crear la shm
        exit(EXIT_FAILURE);                // termina porque no hay espacio de memoria
    }

    // ajusta el tamaño del área compartida para que tenga espacio para la estructura
    if (ftruncate(shm_fd, sizeof(compartir_datos)) < 0) {
        perror("ftruncate");               // muestra error si no se pudo asignar el tamaño
        exit(EXIT_FAILURE);
    }

    // mapea la memoria compartida en el espacio del proceso para leer y escribir
    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos),
                                      PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (compartir == MAP_FAILED) {
        perror("mmap");                    // muestra error si no se pudo mapear
        exit(EXIT_FAILURE);
    }

    // inicializa la estructura del búfer circular y deja todo listo
    compartir->entrada = 0;                // posición donde se insertará el próximo dato
    compartir->salida  = 0;                // posición donde el consumidor leerá datos
    memset(compartir->bus, 0, sizeof(compartir->bus));  // limpia el contenido del búfer

    // ciclo que produce 10 elementos y los coloca en el búfer compartido
    for (int i = 1; i <= 10; i++) {
        sem_wait(vacio);                   // espera a que exista un espacio vacío
        compartir->bus[compartir->entrada] = i; // coloca el dato en la posición 'entrada'
        printf("Productor: Produce %d\n", i);    // muestra cuál dato se produjo
        compartir->entrada = (compartir->entrada + 1) % BUFFER; // avanza en forma circular
        sem_post(lleno);                   // indica que ahora hay un elemento lleno disponible
        sleep(1);                          // pequeña pausa para observar el flujo
    }

    // libera el mapeo de memoria y cierra la shm
    munmap(compartir, sizeof(compartir_datos));  // desmapea la memoria compartida
    close(shm_fd);                                // cierra el descriptor de la shm

    // cierra los semáforos en este proceso
    sem_close(vacio);                 // cierra el semáforo de espacios vacíos
    sem_close(lleno);                 // cierra el semáforo de espacios llenos

    // elimina del sistema el semáforo y la memoria compartida que controla el productor
    sem_unlink(SEM_VACIO);            // elimina el semáforo 'vacio'
    shm_unlink(SHM_NAME);             // elimina el objeto de memoria compartida

    return 0;                          // fin correcto del proceso productor
}
