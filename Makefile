# Definir el compilador y las banderas de compilación

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm  # Banderas para depuración, desactivar advertencias y habilitar hilos

# Archivos fuente y cabeceras

SRCS = main.c modulo.c  # Archivos fuente que se compilarán
HEADERS = modulo.h      # Archivos de cabecera necesarios

# Regla predeterminada: compilar el ejecutable principal

all: main

# Regla para compilar el ejecutable principal
# Compila los archivos fuente y los enlaza para generar el archivo ejecutable "main"

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

# Regla para compilar un ejecutable de depuración
# Compila los archivos con optimización desactivada (-O0) para facilitar la depuración

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

# Regla para limpiar los archivos generados
# Elimina los archivos ejecutables "main" y "main-debug"

clean:
	rm -f main main-debug

