#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "estructuras.c"
#include "funciones.c"
#include "modoManual.c"
#include "modoAutomatico.c"


int main(int argc, char *argv[]) {

  // Verifica el minimo de datos
  if (argc < 4)
  {
    printf("Faltan datos \n");
    return 0;
  }

  
  int minBurst = atoi(argv[1]);
  int maxBurst = atoi(argv[2]);
  
  // Verifica los valores de burst aceptados
  if (validar_bursts_entrada(minBurst, maxBurst) == 0)
  {
    printf("Los valores maximos y minimos no pueden ser aceptados\n");
    return 0;
  }
  
  // Modo manual 
  if (argc == 4)
  {
    printf("\n#################################\n");
    printf("### Ejecutando en modo manual ###\n");
    printf("#################################\n\n");
    FILE *data_output_file = fopen (argv[3], "r");
    if (data_output_file == NULL)
    {
      printf("El archivo no existe o no se puede abrir\n");
      return 0;
    }
    // Ejecuta el modo manual
    modo_manual(minBurst, maxBurst, data_output_file);
    return 0;
  }

  // Modo automatico
  if (argc == 5)
  {
    printf("\n#####################################\n");
    printf("### Ejecutando en modo automatico ###\n");
    printf("#####################################\n\n");
    int minTime = atoi(argv[3]);
    int maxTime = atoi(argv[4]);
    if (validar_tiempos_entrada(minTime, maxTime) == 0)
    {
      printf("Los valores maximos y minimos de tiempo no pueden ser aceptados\n");
    }
    modo_automatico(minBurst, maxBurst, minTime, maxTime);
    return 0;
  }

  // Si faltan o sobran datos
  printf("Datos erroneos\n");
  return 0;
  
}