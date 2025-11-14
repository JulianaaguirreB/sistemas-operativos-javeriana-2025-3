###################################################################################################
#                         Pontificia Universidad Javeriana
#Autores: Juliana Aguirre Ballesteros 
#         Juan Carlos Santamaria Orjuela
#Materia: Sistemas Operativos
#Profesor: j. corredor
#Taller 03 – Posix Semáforos y Pthreads
#Fichero: Makefile Macro 
#
#Descripción:
#Este Makefile general se encarga de coordinar la compilación de todo el taller.
#No compila archivos directamente; en su lugar, llama a los Makefiles internos 
#de cada actividad:
#
#   - actividad1_productor_consumidor  
#   - actividad2_pthreads              
#
#La idea es mantener organizado el proyecto y permitir compilar, ejecutar y 
#limpiar fácilmente cada actividad desde la raíz del taller.
#
#Objetivos:
#- centralizar la compilación del taller usando un punto de entrada único.
#- delegar en los Makefiles internos sin duplicar reglas o rutas.
###################################################################################################


GCC   = gcc
FLAGS = -O2 -Wall -Wextra

# Directorios
A1_DIR     = actividad1_productor_consumidor
A2_DIR     = actividad2_pthreads

# Regla principal: compilar todas las actividades
all: actividad1 actividad2

# Compilar Actividad 1
actividad1:
	$(MAKE) -C $(A1_DIR) all GCC="$(GCC)" FLAGS="$(FLAGS)"

# Compilar Actividad 2
actividad2:
	$(MAKE) -C $(A2_DIR) all GCC="$(GCC)" FLAGS="$(FLAGS)"

# Atajos de ejecución
run-a1:
	$(MAKE) -C $(A1_DIR) run

run-a2:
	$(MAKE) -C $(A2_DIR) run

# Limpieza de subproyectos
clean:
	$(MAKE) -C $(A1_DIR) clean || true
	$(MAKE) -C $(A2_DIR) clean || true

# Limpieza global adicional
distclean: clean
	@echo "Nada más que limpiar en la raíz."

# Guía rápida de uso
help:
	@echo "Objetivos disponibles:"
	@echo "  make all         -> Compila Actividad 1 y Actividad 2"
	@echo "  make actividad1  -> Solo compila Actividad 1"
	@echo "  make actividad2  -> Solo compila Actividad 2"
	@echo "  make run-a1      -> Instrucciones para ejecutar A1"
	@echo "  make run-a2      -> Ejecuta binario de A2"
	@echo "  make clean       -> Limpia subproyectos"
	@echo "  make distclean   -> Limpieza total"