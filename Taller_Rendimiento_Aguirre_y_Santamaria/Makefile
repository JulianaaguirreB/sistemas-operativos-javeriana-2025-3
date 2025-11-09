#==============================================================================
# PONTIFICIA UNIVERSIDAD JAVERIANA 
# Materia: Sistemas Operativos
# Profesor: J. Corredor
#Tema: Taller de Evaluación de Rendimiento
#Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
#* Programa: Makefile del Taller de Evaluación de Rendimiento
#------------------------------------------------------------------------------
# OBJETIVOS:
# 1) Compilar TODAS las variantes del proyecto de multiplicación de matrices:
#    - mmClasicaSerie    
#    - mmClasicaOpenMP   
#    - mmFilasOpenMP      
#    - mmClasicaPosix     
#    - mmClasicaFork      
#
# 2) Centralizar opciones de compilación:
#    - Flags comunes de optimización y warnings.
#    - Soporte específico para OpenMP  y Pthreads .
#    - Inclusión de headers desde include/ y utilidades.
#
# 3) Gestionar artefactos de construcción:
#    - Colocar ejecutables en bin/.
#    - Crear directorios necesarios (bin/, results/, scripts/) antes de compilar.
#
# 4) Facilitar validación y medición rápida:
#    - make test       -> prueba rápida con tamaños pequeños.
#    - make verify     -> verificación de correctitud (matriz pequeña).
#    - make benchmark  -> mini benchmark comparativo variando hilos.
#
# 5) Mantener limpieza y empaque:
#    - make clean / clean-results / distclean -> limpieza selectiva o completa.
#    - make prepare-submission               -> empaquetar para entrega.
#==============================================================================

# CONFIGURACIÓN DEL COMPILADOR


CC = gcc
CFLAGS = -Wall -Wextra -O3 -march=native
CFLAGS_OPENMP = $(CFLAGS) -fopenmp
CFLAGS_POSIX = $(CFLAGS) -pthread
LDFLAGS = -lm
LDFLAGS_POSIX = -lm -lpthread

# DIRECTORIOS

SRC_DIR = src
BIN_DIR = bin
INC_DIR = include
RES_DIR = results
SCRIPT_DIR = scripts

# Incluir headers
INCLUDES  = -I$(INC_DIR)

# Biblioteca (funciones comunes + interfaz)
UTILS_SRC = src/mmOpenMP.c
# Header correspondiente: include/mmOpenMP.h

# ARCHIVOS FUENTE

# OpenMP Clásico
SRC_OPENMP = mmClasicaOpenMP.c
TARGET_OPENMP = $(BIN_DIR)/mmClasicaOpenMP

# OpenMP con Transpuesta
SRC_FILAS = mmFilasOpenMP.c
TARGET_FILAS = $(BIN_DIR)/mmFilasOpenMP

# Pthreads
SRC_POSIX = mmClasicaPosix.c
TARGET_POSIX = $(BIN_DIR)/mmClasicaPosix

# Fork
SRC_FORK = mmClasicaFork.c
TARGET_FORK = $(BIN_DIR)/mmClasicaFork

# Secuencial (línea base)
SRC_SERIE   = mmClasicaSerie.c
TARGET_SERIE = $(BIN_DIR)/mmClasicaSerie


# Todos los ejecutables
TARGETS = $(TARGET_OPENMP) $(TARGET_FILAS) $(TARGET_POSIX) $(TARGET_FORK) $(TARGET_SERIE)


# REGLAS PRINCIPALES

.PHONY: all openmp posix fork clean test help dirs info

# Compilar todo
all: dirs $(TARGETS)
	@echo ""
	@echo "================================================"
	@echo " ✓ COMPILACIÓN COMPLETADA"
	@echo "================================================"
	@echo "Ejecutables en directorio: $(BIN_DIR)/"
	@echo ""
	@ls -lh $(BIN_DIR)/
	@echo ""

# Crear directorios necesarios
dirs:
	@mkdir -p $(BIN_DIR) $(RES_DIR) $(SCRIPT_DIR)

# Compilar solo versiones OpenMP
openmp: dirs $(TARGET_OPENMP) $(TARGET_FILAS)
	@echo "✓ Versiones OpenMP compiladas"

# Compilar solo versión Pthreads
posix: dirs $(TARGET_POSIX)
	@echo "✓ Versión Pthreads compilada"

# Compilar solo versión Fork
fork: dirs $(TARGET_FORK)
	@echo "✓ Versión Fork compilada"


# REGLAS DE COMPILACIÓN INDIVIDUALES

# OpenMP Clásico
$(TARGET_OPENMP): $(SRC_DIR)/$(SRC_OPENMP) $(UTILS_SRC)
	@echo "Compilando mmClasicaOpenMP..."
	@$(CC) $(CFLAGS_OPENMP) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ mmClasicaOpenMP listo"

# OpenMP con Transpuesta
$(TARGET_FILAS): $(SRC_DIR)/$(SRC_FILAS) $(UTILS_SRC)
	@echo "Compilando mmFilasOpenMP..."
	@$(CC) $(CFLAGS_OPENMP) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ mmFilasOpenMP listo"

# Pthreads
$(TARGET_POSIX): $(SRC_DIR)/$(SRC_POSIX) $(UTILS_SRC)
	@echo "Compilando mmClasicaPosix..."
	@$(CC) $(CFLAGS_POSIX) $(INCLUDES) -o $@ $^ $(LDFLAGS_POSIX)
	@echo "✓ mmClasicaPosix listo"

# Fork
$(TARGET_FORK): $(SRC_DIR)/$(SRC_FORK) $(UTILS_SRC)
	@echo "Compilando mmClasicaFork..."
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ mmClasicaFork listo"

# Secuencial (línea base)
$(TARGET_SERIE): $(SRC_DIR)/$(SRC_SERIE) $(UTILS_SRC)
	@echo "Compilando mmClasicaSerie..."
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ mmClasicaSerie listo"

# REGLAS DE PRUEBA

# Prueba rápida de todos los programas
test: all
	@echo ""
	@echo "================================================"
	@echo " PRUEBAS RÁPIDAS (Matriz 4x4, 2 hilos)"
	@echo "================================================"
	@echo ""
	@echo "--- mmClasicaOpenMP ---"
	@$(TARGET_OPENMP) 4 2
	@echo ""
	@echo "--- mmFilasOpenMP ---"
	@$(TARGET_FILAS) 4 2
	@echo ""
	@echo "--- mmClasicaPosix ---"
	@$(TARGET_POSIX) 4 2
	@echo ""
	@echo "--- mmClasicaFork ---"
	@$(TARGET_FORK) 4 2
	@echo ""
	@echo "--- mmClasicaSerie ---"
	@$(TARGET_SERIE) 4 1
	@echo ""
	@echo "✓ Todas las pruebas completadas"
	@echo ""


# Prueba de verificación (matrices pequeñas)
verify: all
	@echo ""
	@echo "================================================"
	@echo " VERIFICACIÓN DE CORRECTITUD"
	@echo "================================================"
	@echo "Ejecutando con matriz 3x3 para ver resultados..."
	@echo ""
	@$(TARGET_OPENMP) 3 1

# Benchmark rápido
benchmark: all
	@echo ""
	@echo "================================================"
	@echo " BENCHMARK COMPARATIVO"
	@echo "================================================"
	@echo ""
	@echo "Matriz 1000x1000, variando hilos..."
	@echo ""
	@for hilos in 1 2 4 8; do \
		echo "=== $$hilos hilo(s) ==="; \
		echo -n "OpenMP:   "; \
		$(TARGET_OPENMP) 1000 $$hilos; \
		echo -n "Posix:    "; \
		$(TARGET_POSIX) 1000 $$hilos; \
		echo ""; \
	done

# REGLAS DE LIMPIEZA

# Limpieza completa
clean:
	@echo "Limpiando archivos compilados..."
	@rm -rf $(BIN_DIR)
	@rm -f $(SRC_DIR)/*.o
	@rm -f *~ $(SRC_DIR)/*~ $(INC_DIR)/*~
	@echo "✓ Limpieza completada"

# Limpiar solo resultados
clean-results:
	@echo "Limpiando resultados..."
	@rm -f $(RES_DIR)/*.dat $(RES_DIR)/*.csv $(RES_DIR)/*.txt
	@echo "✓ Resultados eliminados"

# Limpieza profunda
distclean: clean clean-results
	@rm -rf $(RES_DIR) $(BIN_DIR)
	@echo "✓ Limpieza profunda completada"

# INFORMACIÓN Y AYUDA

# Información del sistema
info:
	@echo ""
	@echo "================================================"
	@echo " INFORMACIÓN DEL SISTEMA"
	@echo "================================================"
	@echo ""
	@echo "Sistema Operativo:"
	@uname -a
	@echo ""
	@echo "Distribución:"
	@cat /etc/os-release | grep PRETTY_NAME
	@echo ""
	@echo "Compilador:"
	@$(CC) --version | head -1
	@echo ""
	@echo "CPU:"
	@lscpu | grep "Model name"
	@echo ""
	@echo "Núcleos físicos:"
	@lscpu | grep "^CPU(s):" | head -1
	@echo ""
	@echo "Núcleos lógicos:"
	@lscpu | grep "Thread(s) per core"
	@echo ""
	@echo "Memoria RAM:"
	@free -h | grep "Mem:"
	@echo ""
	@echo "Soporte OpenMP:"
	@echo | $(CC) -fopenmp -dM -E - 2>/dev/null | grep _OPENMP || echo "No disponible"
	@echo ""

# Ayuda
help:
	@echo ""
	@echo "================================================"
	@echo " MAKEFILE - TALLER DE EVALUACIÓN DE RENDIMIENTO"
	@echo "================================================"
	@echo ""
	@echo "COMPILACIÓN:"
	@echo "  make all          Compila todos los programas"
	@echo "  make openmp       Compila solo versiones OpenMP"
	@echo "  make posix        Compila solo versión Pthreads"
	@echo "  make fork         Compila solo versión Fork"
	@echo ""
	@echo "PRUEBAS:"
	@echo "  make test         Prueba rápida de todos los programas"
	@echo "  make verify       Verifica correctitud con matriz pequeña"
	@echo "  make benchmark    Benchmark comparativo rápido"
	@echo ""
	@echo "LIMPIEZA:"
	@echo "  make clean        Elimina archivos compilados"
	@echo "  make clean-results Elimina solo archivos de resultados"
	@echo "  make distclean    Limpieza completa"
	@echo ""
	@echo "INFORMACIÓN:"
	@echo "  make info         Muestra información del sistema"
	@echo "  make help         Muestra esta ayuda"
	@echo ""
	@echo "PROGRAMAS COMPILADOS:"
	@echo "  mmClasicaOpenMP   Multiplicación con OpenMP (clásico)"
	@echo "  mmFilasOpenMP     OpenMP con matriz transpuesta"
	@echo "  mmClasicaPosix    Multiplicación con Pthreads"
	@echo "  mmClasicaFork     Multiplicación con Fork"
	@echo ""
	@echo "USO DE LOS PROGRAMAS:"
	@echo "  ./bin/mmClasicaOpenMP <tamaño> <hilos>"
	@echo ""
	@echo "EJEMPLO:"
	@echo "  ./bin/mmClasicaOpenMP 1000 4"
	@echo "  Multiplica matrices 1000x1000 con 4 hilos"
	@echo ""
	@echo "PARA EXPERIMENTOS AUTOMATIZADOS:"
	@echo "  1. Edita scripts/lanzador.pl"
	@echo "  2. Ejecuta: perl scripts/lanzador.pl"
	@echo "  3. Analiza resultados en results/"
	@echo ""

# Mostrar variables del Makefile
show-vars:
	@echo "CC = $(CC)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "CFLAGS_OPENMP = $(CFLAGS_OPENMP)"
	@echo "CFLAGS_POSIX = $(CFLAGS_POSIX)"
	@echo "BIN_DIR = $(BIN_DIR)"
	@echo "TARGETS = $(TARGETS)"

# REGLAS PARA EVALUACIÓN 

# Preparar archivos para entregar
prepare-submission: all
	@echo "Preparando archivos para entrega..."
	@mkdir -p entrega/src entrega/scripts entrega/results
	@cp $(SRC_DIR)/*.c entrega/src/
	@cp $(INC_DIR)/*.h entrega/src/ 2>/dev/null || true
	@cp Makefile entrega/
	@cp $(SCRIPT_DIR)/*.pl entrega/scripts/ 2>/dev/null || true
	@echo "Documentación del proyecto" > entrega/README.txt
	@echo "Compilar con: make all" >> entrega/README.txt
	@echo "Ejecutar pruebas: make test" >> entrega/README.txt
	@cd entrega && zip -r ../proyecto_taller.zip *
	@echo "✓ Archivo proyecto_taller.zip creado"

