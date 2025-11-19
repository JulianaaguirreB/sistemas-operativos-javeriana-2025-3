Proyecto: Simulacion de un Sistema de Reservas
=============================================

Autores:
- Juliana Aguirre Ballesteros
- Juan Carlos Santamaria Orjuela
- Juan David Daza

Materia:
- Sistemas Operativos 2025-30

Profesor:
-J.corredor

Descripcion general
-------------------
Este proyecto simula un sistema de reservas para el parque Berlin.

Hay un proceso servidor y varios procesos agente.

- El servidor controla el aforo del parque por horas.
- Los agentes leen archivos CSV con reservas de familias y las envian al servidor.
- El servidor decide si la reserva se acepta, se reprograma o se niega.
- Un reloj de simulacion avanza la hora y actualiza la agenda del parque.
- Al final del dia se imprime un reporte con estadisticas.

Estructura de carpetas
----------------------
- bin/       : ejecutables (servidor y agente)
- build/     : archivos objeto .o
- src/       : codigo fuente .c
- include/   : archivos de cabecera .h
- data/      : archivos CSV de ejemplo (agenteA.csv, agenteB.csv)
- Makefile   : reglas de compilacion

Requisitos
----------
- Sistema operativo Linux
- Compilador gcc
- Herramienta make

Comandos de compilacion
-----------------------
Compilar todo el proyecto:

    make

o tambien:

    make all

Limpiar ejecutables y archivos .o:

    make clean

Como ejecutar el servidor
-------------------------
Ejemplo basico desde la carpeta raiz del proyecto:

    ./bin/servidor -i 7 -f 19 -s 1 -t 10 -p /tmp/pipe_reservas

Significado de los parametros:
- -i 7   : hora inicial de la simulacion (7)
- -f 19  : hora final de la simulacion (19)
- -s 1   : segundos reales por cada hora simulada (1 segundo = 1 hora)
- -t 10  : aforo maximo del parque (10 personas por hora)
- -p ... : ruta del pipe FIFO por donde los agentes envian mensajes

Como ejecutar los agentes
-------------------------
Ejemplo de un agente A:

    ./bin/agente -s agenteA -a data/agenteA.csv -p /tmp/pipe_reservas

Ejemplo de un agente B (en otra terminal):

    ./bin/agente -s agenteB -a data/agenteB.csv -p /tmp/pipe_reservas

Significado de los parametros:
- -s agenteA  : nombre logico del agente
- -a ...      : ruta al archivo CSV con reservas
- -p ...      : ruta del pipe FIFO del servidor (igual a la usada en el servidor)

Flujo basico
------------
1. Se compila el proyecto con `make`.
2. Se inicia el servidor con los parametros deseados.
3. Se inician uno o varios agentes apuntando al mismo pipe del servidor.
4. Cada agente lee su CSV, envia reservas y muestra las respuestas.
5. Al llegar la hora final, el servidor imprime el reporte del dia y envia FIN DEL DIA.
6. Los agentes reciben FIN DEL DIA, borran su pipe de respuesta y terminan.

Notas finales
-------------
- Los archivos CSV de ejemplo se encuentran en la carpeta data/.
- Si se cambia la ruta del pipe del servidor (-p), se debe usar la misma en todos los agentes.
- Si hay problemas de compilacion o de ejecucion, usar `make clean` y luego `make` de nuevo.
