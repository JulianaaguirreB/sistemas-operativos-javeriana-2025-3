#***********************************************************************************************
#                              Pontificia Universidad Javeriana
# Autores: Juliana Aguirre Ballesteros, Juan Carlos Santamaría Orjuela
# Profesor: J. Corredor
# Materia: Sistemas Operativos
# Tema: Taller de Evaluación de Rendimiento
# Archivo: lanzador.pl
# OBJETIVOS:
# - Ejecutar automáticamente todos los programas con distintos tamaños y hilos.
# - Repetir cada combinación varias veces para tener tiempos más confiables.
# - Guardar los tiempos en archivos .dat dentro de results/ para análisis en Excel/LibreOffice.
# - Mostrar en consola el avance y un resumen final.
# - Dejar todo listo para calcular speedup y eficiencia en el informe.
#***********************************************************************************************

use strict;
use warnings;

# CONFIGURACIÓN DE PARÁMETROS

# Obtener directorio actual
my $Path = `pwd`;
chomp($Path);

# CONFIGURACIÓN PRINCIPAL - MODIFICA ESTOS VALORES

# my $Nombre_Ejecutable = "bin/mmClasicaFork";   # 

# Ejecutables a evaluar 
my @Ejecutables = (
    "bin/mmClasicaSerie",
    "bin/mmClasicaFork",
    "bin/mmClasicaPosix",
    "bin/mmClasicaOpenMP",
    "bin/mmFilasOpenMP"
);

# Tamaños de matriz a probar (ajusta si quieres)
my @Size_Matriz = (100, 500, 1000);

# Número de hilos a probar (ajusta según cores)
my @Num_Hilos = (1, 2, 4);

# Número de repeticiones por configuración
my $Repeticiones = 30;

# Directorio para guardar resultados
my $Results_Dir = "results";

# VALIDACIÓN Y PREPARACIÓN

# Verificar que existen TODOS los ejecutables
for my $EXE (@Ejecutables) {
    unless (-x "$Path/$EXE") {
        die "\n ERROR: No se encuentra el ejecutable: $EXE\n" .
            "   Ejecuta 'make all' primero para compilar los programas.\n\n";
    }
}

# Crear directorio de resultados si no existe
unless (-d $Results_Dir) {
    mkdir($Results_Dir) or die "No se pudo crear directorio $Results_Dir: $!\n";
    print "✓ Directorio $Results_Dir creado\n";
}

# INFORMACIÓN DEL EXPERIMENTO

print "\n";
print "="x80 . "\n";
print " TALLER DE EVALUACIÓN DE RENDIMIENTO\n";
print " Script de Automatización de Experimentos\n";
print "="x80 . "\n\n";

print "CONFIGURACIÓN:\n";
print "-" x 80 . "\n";
print sprintf("  Programas:     %s\n", join(", ", @Ejecutables));
print sprintf("  Tamaños:       %s\n", join(", ", @Size_Matriz));
print sprintf("  Hilos:         %s\n", join(", ", @Num_Hilos));
print sprintf("  Repeticiones:  %d por configuración\n", $Repeticiones);
print sprintf("  Salida:        %s/\n", $Results_Dir);

# Calcular total de ejecuciones 
my $total_experimentos = scalar(@Size_Matriz) * scalar(@Num_Hilos) * $Repeticiones * scalar(@Ejecutables);
print sprintf("  Total ejecuciones: %d\n", $total_experimentos);
print "-" x 80 . "\n\n";

# Advertencia si hay muchos experimentos
if ($total_experimentos > 500) {
    print "  ADVERTENCIA: Este experimento tiene $total_experimentos ejecuciones.\n";
    print "   Esto puede tomar bastante tiempo.\n\n";
    print "¿Continuar? (s/n): ";
    my $respuesta = <STDIN>;
    chomp($respuesta);
    unless ($respuesta =~ /^[sS]/) {
        print "Experimento cancelado.\n";
        exit(0);
    }
}

# EJECUCIÓN DE EXPERIMENTOS

print "INICIANDO EXPERIMENTOS...\n";
print "="x80 . "\n\n";

my $contador_total = 0;
my $tiempo_inicio = time();

# recorrer cada ejecutable, manteniendo tu misma estructura 
foreach my $Nombre_Ejecutable (@Ejecutables) {

    print "\n========================================\n";
    print   " PROGRAMA: $Nombre_Ejecutable\n";
    print   "========================================\n";

    # Bucle principal: iterar sobre tamaños de matriz
    foreach my $size (@Size_Matriz) {
        print "\n┌" . "─"x78 . "┐\n";
        print sprintf("│ TAMAÑO DE MATRIZ: %d x %d%-52s│\n", $size, $size, "");
        print "└" . "─"x78 . "┘\n\n";

        # Bucle secundario: iterar sobre número de hilos
        foreach my $hilo (@Num_Hilos) {

            # Construir nombre del archivo de salida (basename del ejecutable)
            (my $base = $Nombre_Ejecutable) =~ s!.*/!!;   # mmClasicaFork, etc.
            my $file = "$Path/$Results_Dir/${base}-${size}-Hilos-${hilo}.dat";

            # Abrir archivo para escribir
            open(my $fh, '>', $file) or die "No se pudo crear $file: $!\n";

            # Encabezado del archivo
            print $fh "# Resultados de rendimiento\n";
            print $fh "# Programa: $Nombre_Ejecutable\n";
            print $fh "# Tamaño matriz: $size x $size\n";
            print $fh "# Número de hilos: $hilo\n";
            print $fh "# Repeticiones: $Repeticiones\n";
            print $fh "# Tiempo en microsegundos\n";
            print $fh "#\n";
            print $fh "# Iteracion\tTiempo(us)\n";

            # Información en consola
            print sprintf("  Hilos: %-2d │ ", $hilo);

            # Ejecutar repeticiones
            for (my $i = 1; $i <= $Repeticiones; $i++) {
                $contador_total++;

                # Construir comando
                my $comando = "$Path/$Nombre_Ejecutable $size $hilo";

                # Ejecutar y capturar salida
                my $output = `$comando 2>&1`;
                chomp($output);

                # Extraer tiempo (última línea de números, mismo estilo)
                my $tiempo = "";
                if ($output =~ /(\d+)\s*$/) {
                    $tiempo = $1;
                }

                # Guardar en archivo
                if ($tiempo ne "") {
                    print $fh "$i\t$tiempo\n";
                } else {
                    print $fh "$i\tERROR\n";
                    warn "  Advertencia: No se pudo extraer tiempo en iteración $i\n";
                }

                # Mostrar progreso
                if ($i % 5 == 0 || $i == $Repeticiones) {
                    print sprintf("█");
                }

                # Flush del buffer para ver progreso en tiempo real
                $| = 1;
            }

            # Cerrar archivo
            close($fh);

            # Calcular progreso global (cuenta todos los ejecutables)
            my $progreso = ($contador_total / $total_experimentos) * 100;
            print sprintf(" │ %d/%d (%.1f%%)\n",
                         $contador_total, $total_experimentos, $progreso);
        }
    }
} #  fin foreach $Nombre_Ejecutable

# RESUMEN FINAL

my $tiempo_fin = time();
my $duracion = $tiempo_fin - $tiempo_inicio;
my $minutos = int($duracion / 60);
my $segundos = $duracion % 60;

print "\n";
print "="x80 . "\n";
print " EXPERIMENTOS COMPLETADOS\n";
print "="x80 . "\n";
print sprintf("✓ Ejecuciones realizadas: %d\n", $contador_total);
print sprintf("✓ Tiempo total: %d minutos, %d segundos\n", $minutos, $segundos);
print sprintf("✓ Archivos generados: %d\n",
             scalar(@Size_Matriz) * scalar(@Num_Hilos) * scalar(@Ejecutables));
print sprintf("✓ Ubicación: %s/\n", $Results_Dir);
print "\n";

# INSTRUCCIONES POST-EXPERIMENTO

print "PRÓXIMOS PASOS:\n";
print "-" x 80 . "\n";
print "1. Revisar archivos .dat en el directorio '$Results_Dir/'\n";
print "2. Importar datos a hoja de cálculo (Excel, LibreOffice, etc.)\n";
print "3. Calcular estadísticas:\n";
print "   - Promedio (media)\n";
print "   - Desviación estándar\n";
print "   - Mínimo y máximo\n";
print "4. Calcular métricas de rendimiento:\n";
print "   - Speedup = Tiempo(1 hilo) / Tiempo(N hilos)\n";
print "   - Eficiencia = Speedup / N hilos\n";
print "5. Generar gráficas comparativas\n";
print "6. Analizar resultados para el informe\n";
print "-" x 80 . "\n\n";

print "SUGERENCIAS DE ANÁLISIS:\n";
print "-" x 80 . "\n";
print "• Gráfica 1: Tiempo vs Número de hilos (por cada tamaño)\n";
print "• Gráfica 2: Speedup vs Número de hilos\n";
print "• Gráfica 3: Eficiencia vs Número de hilos\n";
print "• Gráfica 4: Comparación entre diferentes tamaños\n";
print "-" x 80 . "\n\n";

# Ejemplo de comando para ver resultados
my $primer_archivo = `ls $Results_Dir/*.dat 2>/dev/null | head -1`;
chomp($primer_archivo);
if ($primer_archivo) {
    print "EJEMPLO - Ver primer archivo:\n";
    print "  cat $primer_archivo\n\n";
}

print "="x80 . "\n\n";

exit(0);
