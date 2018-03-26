#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "estructuras.c"
#include "funciones.c"

int main(int argc, char *argv[]) {
  // Todos los hilos se guardan aqui
  int thread_index = 0;
  pthread_t threads[1000];
  srand(time(0));
  
  // Archivo de datos 
  FILE *data_output_file = fopen (argv[1], "r");        
  
  // Intenta leer el archivo
  if (data_output_file == NULL){
    printf("El archivo %s no existe o no se puede abrir\n", argv[1]);
    return 0;
  }
  
  // Procesa el archivo          
  char line[10];
  while (feof(data_output_file) == 0){
    fgets(line, 10, data_output_file);
    char *burst    = malloc(3);
    char *priority = malloc(3);
    int i = 0, flag = 0;
    while(line[i] != '\0'){
      char val = line[i];
      if (val == '\n')
        break;
      if (val == ' ')
        flag = 1;
      else{
        if(flag == 0)
          concatenar(burst, val);
        if(flag == 1)
          concatenar(priority, val);
      }
      i++;
    }

    // Solo envia los datos correctos
    if(strcmp(burst, "")){
      printf("\n\n%d : %d\n", atoi(burst), atoi(priority));

      // Crea el hilo y lo pone a correr
      struct info_pcb new_info_pcb = {atoi(burst), atoi(priority)};
      pthread_create(&threads[thread_index], NULL, (void*)thread_action, (void*)&new_info_pcb);
      
      thread_index++;
      sleep(getRandom(8));
    }
  }

  // Espera que todos los hilos terminen
  for (int i = 0; i < thread_index; i++){
    pthread_join(threads[i], NULL);
  }

  printf("termine\n");
  return 0;
}