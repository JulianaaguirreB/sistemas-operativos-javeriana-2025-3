#############################################################################################################
#                               Pontificia Universidad Javeriana                       
# Autor: Juliana Aguirre Ballesteros                                                   
# Materia: Sistemas Operativos                                                         
# Laboratorio: OpenMP                                                                  
# Profesor: J. Corredor                                                                                                                                
# Descripcion:                                                                         
#   Este Makefile automatiza la compilacion de los programas desarrollados        
#   para los diferentes laboratorios de OpenMP. 
#	Permite compilar cada archivo individualmente y realizar la limpieza de los ejecutables generados.               
# Objetivo:                                                                            
#   - Simplificar el proceso de compilacion.                                            
#   - Facilitar la eliminacion de archivos binarios con la regla 'clean'.              
###########################################################################################################

GCC = gcc
FLAGS = -lm -fopenmp
PROGRAMAS = lab1_aguirre lab2_aguirre lab3_aguirre lab4_aguirre lab5_aguirre lab6_aguirre

# Compilacion individual de cada laboratorio
lab1_aguirre:
	$(GCC) $@.c -o $@ $(FLAGS)

lab2_aguirre:
	$(GCC) $@.c -o $@ $(FLAGS)

lab3_aguirre:
	$(GCC) $@.c -o $@ $(FLAGS)

lab4_aguirre:
	$(GCC) $@.c -o $@ $(FLAGS)

lab5_aguirre:
	$(GCC) $@.c -o $@ $(FLAGS)

lab6_aguirre:
	$(GCC) $@.c -o $@ $(FLAGS)

# Limpieza de archivos ejecutables
clean:
	rm -f $(PROGRAMAS)
