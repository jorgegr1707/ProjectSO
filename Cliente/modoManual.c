// ###########################################
// Ejecuta el modo manual
// - int minBurst : Rango minimo aceptado del burst 
// - int maxBurst : Rango maximo aceptado del burst
// - FILE *data_output_file : Es el archivo 
//   donde se encuentran los datos
// ###########################################
int modo_manual(int minBurst, int maxBurst, FILE *data_output_file){
  // Todos los hilos se guardan aqui
  int thread_index = 0;
  pthread_t threads[1000];
  srand(time(0));
  
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

    // Enteros del burst y la prioridad
    int burst_final    = atoi(burst);
    int priority_final = atoi(priority);

    // Si el dato no viene en el documento
    if (priority_final == 0)
    {
      priority_final = 5;
    }

    // Se envian los datos correctos
    if( strcmp(burst, "")         && 
        (burst_final <= maxBurst) && 
        (burst_final >= minBurst) &&
        (priority_final > 0)      && 
        (priority_final < 10)
      )
    {
      struct info_pcb new_info_pcb = { burst_final, priority_final };
      pthread_create(&threads[thread_index], NULL, (void*)thread_action, (void*)&new_info_pcb);
      thread_index++;
      sleep(getRandom(8));
    }
  }

  // Espera que todos los hilos terminen
  for (int i = 0; i < thread_index; i++){
    pthread_join(threads[i], NULL);
  }
}
