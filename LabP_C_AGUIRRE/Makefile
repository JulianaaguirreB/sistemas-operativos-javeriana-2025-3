###################################################################################
# Autor: Juliana Aguirre Ballesteros
# Archivo: Makefile
# Materia: Sistemas Operativos
# Tema: Implementación de Productor–Consumidor con Pipes Nombrados (FIFO)
#
# Descripción:
# -Este archivo automatiza el proceso de compilación y limpieza
# de los programas cliente y servidor que implementan comunicación
# entre procesos mediante un FIFO.
#
# -Permite compilar ambos programas de forma independiente
# o ejecutar una limpieza general del proyecto eliminando
# los ejecutables generados.
###################################################################################

GCC = gcc

# Opciones adicionales para el compilador 
FLAGS =
MODULO =
# Lista de ejecutables que generará el proyecto
PROGRAMAS = cliente servidor

# Regla para compilar el  cliente
cliente:
	$(GCC) $(FLAGS) $@.c -o $@

# Regla para compilar el  servidor
servidor:
	$(GCC) $(FLAGS) $@.c -o $@
# Elimina los ejecutables generados durante la compilación
clear:
	$(RM) $(PROGRAMAS)
