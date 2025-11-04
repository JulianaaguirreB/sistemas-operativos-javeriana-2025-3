##################################################################################################################################################################
# Pontificia Universidad Javeriana
# Autor: Juliana Aguirre Ballesteros
# Materia: Sistemas Operativos
# Profesor: J.corredor
#
# Descripción:
# Este Makefile permite compilar de manera automática los distintos laboratorios de hilos.  .  
# Su uso facilita la gestión y compilación de los distintos módulos del taller.
##################################################################################################################################################################
GCC=gcc
FLAGS= -lpthread
MODULO=
RM= rm -f

PROGRAMAS=lab01_aguirre lab02_aguirre lab03_aguirre lab04_aguirre lab05_aguirre lab06_aguirre lab07_aguirre lab08_aguirre lab09_aguirre

all: $(PROGRAMAS)

lab01_aguirre: lab1_aguirre.c
	$(GCC) lab1_aguirre.c -o lab01_aguirre $(FLAGS)

lab02_aguirre: lab2_aguirre.c
	$(GCC) lab2_aguirre.c -o lab02_aguirre $(FLAGS)

lab03_aguirre: lab3_aguirre.c
	$(GCC) lab3_aguirre.c -o lab03_aguirre $(FLAGS)

lab04_aguirre: lab4_aguirre.c
	$(GCC) lab4_aguirre.c -o lab04_aguirre $(FLAGS)

lab05_aguirre: lab5_aguirre.c
	$(GCC) lab5_aguirre.c -o lab05_aguirre $(FLAGS)

lab06_aguirre: lab6_aguirre.c
	$(GCC) lab6_aguirre.c -o lab06_aguirre $(FLAGS)

lab07_aguirre: lab7_aguirre.c
	$(GCC) lab7_aguirre.c -o lab07_aguirre $(FLAGS)

lab08_aguirre: lab8_aguirre.c
	$(GCC) lab8_aguirre.c -o lab08_aguirre $(FLAGS)

lab09_aguirre: lab9_aguirre.c
	$(GCC) lab9_aguirre.c -o lab09_aguirre $(FLAGS)

clean:
	$(RM) $(PROGRAMAS)
