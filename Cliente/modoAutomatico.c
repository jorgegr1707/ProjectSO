int randon_range(int n1, int n2)
{
	int min = n1;
	int valorRandom = rand() % (n2 - n1);
	return min + valorRandom;
}

// ###########################################
// Ejecuta el modo automatico
// - int minBurst : Rango minimo aceptado del burst 
// - int maxBurst : Rango maximo aceptado del burst
// - int minTime  : Rango minimo aceptado del tiempo 
// - int maxTime  : Rango maximo aceptado del tiempo 
// ###########################################
int modo_automatico(int minBurst, int maxBurst, int minTime, int maxTime)
{
	// Todos los hilos se guardan aqui
	int thread_index = 0;
  	pthread_t threads[1000];
  	srand(time(0));

  	int burst, priority, tasa_creacion;
  	int minPriority = 1;
  	int maxPriority = 10;

  	while(1)
  	{
  		// Produce los valores aleatorios
  		burst         = randon_range(minBurst, maxBurst);
  		priority      = randon_range(minPriority,  maxPriority);
  		tasa_creacion = randon_range(minTime,  maxTime);

  		// Dispara el hilo
  		struct info_pcb new_info_pcb = { burst, priority };
      	pthread_create(&threads[thread_index], NULL, (void*)thread_action, (void*)&new_info_pcb);
      	thread_index++;
      	
  		// Duerme un tiempo aleatorio en el rango dado
  		sleep(tasa_creacion);
  	}

  	// Espera que todos los hilos terminen
	for (int i = 0; i < thread_index; i++){
		pthread_join(threads[i], NULL);
	}
	return 0;
}