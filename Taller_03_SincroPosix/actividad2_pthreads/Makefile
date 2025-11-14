###################################################################################################
#                         Pontificia Universidad Javeriana
#Autores: Juliana Aguirre Ballesteros 
#         Juan Carlos Santamaria Orjuela
#Materia: sistemas operativos
#Profesor: j. corredor
#Taller 03 Posix Semáforos – Makefile Actividad 2
#
#Descripción:
#Este Makefile compila los programas de la Actividad 2, donde se trabaja con 
#hilos POSIX, mutex y variables de condición. Se generan dos ejecutables:
#uno para el ejemplo productor–spooler y otro para procesar datos con
#varios hilos. 
#
#Objetivos:
#- compilar automáticamente posixSincro.c y concurrenciaPosix.c.
#- organizar los ejecutables dentro de la carpeta bin.
#- facilitar la ejecución de pruebas con los comandos make run y make run-max.
###################################################################################################

GCC   = gcc
FLAGS = -O2 -Wall -Wextra -D_POSIX_C_SOURCE=200809L -pthread

SRC = src
INC = include
BIN = bin
DATA = data

# ejecutables que se generarán
PROGRAMAS = $(BIN)/posixSincro $(BIN)/concurrenciaPosix

#compilar todo y crear carpetas si faltan
all: dirs $(PROGRAMAS)

# crea la carpeta bin si no existe
dirs:
	mkdir -p $(BIN)

# compila el programa principal de sincronización con hilos
$(BIN)/posixSincro:
	$(GCC) $(SRC)/posixSincro.c -I$(INC) -o $@ $(FLAGS)

# compila el programa de procesamiento de datos con hilos
$(BIN)/concurrenciaPosix: $(SRC)/concurrenciaPosix.c
	$(GCC) $(SRC)/concurrenciaPosix.c -I$(INC) -o $@ $(FLAGS)

# ejecuta la versión productor spooler
run:
	./bin/posixSincro

# ejecuta la versión paralela que procesa el archivo de datos
run-max:
	./bin/concurrenciaPosix ./data/datos.txt 1000 4 || true

# elimina los ejecutables generados
clean:
	$(RM) $(PROGRAMAS)