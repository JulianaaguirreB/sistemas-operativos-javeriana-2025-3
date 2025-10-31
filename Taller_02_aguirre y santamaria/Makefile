#####################################################################################################
# Universidad: Pontificia Universidad Javeriana
# Materia: Sistemas Operativos – 2025-30
# Profesor: J. Corredor
# Autores: Juliana Aguirre Ballesteros - Juan Carlos Santamaría Orjuela
# Nombre archivo: Makefile
#
# Objetivos:
#   - Automatizar el proceso de compilación, ejecución y limpieza del proyecto.
#   - Evitar compilaciones manuales usando comandos de GCC por separado.
#   - Organizar las dependencias entre archivos fuente, objetos y ejecutable final.
#####################################################################################################

CC = gcc

#Comando para eliminar archivos 
RM = rm -f

# Nombre del ejecutable final 
PROGRAMAS = taller_procesos

#Archivos fuente del proyecto
SRC = \
        main.c \
        Implementacion/lectura.c \
        Implementacion/suma.c

OBJ = $(SRC:.c=.o)

#Regla principal: compila todo el proyecto 
all: $(PROGRAMAS)

#  Enlaza los objetos para generar el ejecutable 
taller_procesos: $(OBJ)
	$(CC) $(OBJ) -o $@

# Interfacez indica la carpeta donde están los archivos .h 
%.o: %.c
	$(CC) -IInterfacez -c $< -o $@

#   Ejecuta el binario con dos archivos de entrada ejemplo y sus tamaños N1 y N2.
run: $(PROGRAMAS)
	./taller_procesos 5 datos/archivo00.txt 4 datos/archivo01.txt

#   Elimina los ejecutables y archivos objeto generados durante la compilación.
clean:
	$(RM) $(PROGRAMAS) $(OBJ)
