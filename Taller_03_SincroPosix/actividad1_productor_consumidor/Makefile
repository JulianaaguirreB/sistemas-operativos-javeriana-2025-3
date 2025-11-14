#####################################################################3#############################
#                         Pontificia Universidad Javeriana
#Autores: Juliana Aguirre Ballesteros 
#         Juan Carlos Santamaria Orjuela
#Materia: sistemas operativos
#Profesor: j. corredor
#Taller 03 Posix Semáforos – Makefile Actividad 1
#
#Descripción:
#Este Makefile compila los dos programas de la Actividad 1: el productor y el consumidor.
#Ambos dependen de memoria compartida y semáforos POSIX, y usan el archivo shared.h que
#está en la carpeta "include". 
#
#Objetivos:
#- compilar producer.c y consumer.c de manera automática.
#- organizar los ejecutables dentro de la carpeta bin/.
#- permitir ejecutar fácilmente el productor y el consumidor con el comando make run.
###################################################################################################

GCC   = gcc
FLAGS = -O2 -Wall -Wextra -D_POSIX_C_SOURCE=200809L -pthread

SRC = src
INC = include
BIN = bin

# ejecutables finales que se generarán
PROGRAMAS = $(BIN)/producer $(BIN)/consumer

# compilar todo y crear carpetas necesarias
all: dirs $(PROGRAMAS)

# crea la carpeta bin si no existe
dirs:
	mkdir -p $(BIN)

# compila el productor incluyendo las cabeceras de include
$(BIN)/producer:
	$(GCC) $(SRC)/producer.c -I$(INC) -o $@ $(FLAGS)

# compila el consumidor de la misma forma
$(BIN)/consumer:
	$(GCC) $(SRC)/consumer.c -I$(INC) -o $@ $(FLAGS)

# muestra cómo ejecutar el flujo productor consumidor desde dos terminales
run:
	@echo "1) Terminal A: ./bin/consumer"
	@echo "2) Terminal B: ./bin/producer"


clean:
	$(RM) $(PROGRAMAS)
