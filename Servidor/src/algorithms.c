
void insert_ready_queue(int id, int burst, int priority, int waiting_time, int turn_around_time)
{
	switch (algorithm_type)
	        {
	            case 1:
	                append(id, burst, priority, waiting_time, clock_cpu, turn_around_time);
	                break;
	            case 2:
	            	insert_by_burst(id, burst, priority, waiting_time, clock_cpu, turn_around_time);
	                break;
	            case 3:
	                insert_by_priority(id, burst, priority, waiting_time, clock_cpu, turn_around_time);
	                break;
	            case 4:
	            	rr = 1;
	            	append(id, burst, priority, waiting_time, clock_cpu, turn_around_time);
	                break;
	        }

}

// ##############################################
// Se encarga de estar constantemente buscando clientes.
// cuando encuentra uno, lo envia a la cola ## falta implementarlo
// ##############################################
void * job_scheduler_action(void * args)
{
	// Inicia el listener
	int listener = begin_listener();

	// Inicia el puerto
	const int PORT = 7200;
	begin_port(listener, PORT);

	// Espera por clientes. Cuando encuentra uno, lo ingresa a la cola
	while(1)
	{
		// Crea la estructura del cliente que se va a recibir
		struct sockaddr_storage client;
		unsigned int address_size = sizeof(client);

		// Verifica si algun cliente necesita el servicio
		int connect = accept(listener, (struct sockaddr*)&client, &address_size);
		
		//recibe los datos del cliente
		char* buffer = malloc(10);
		recv(connect, buffer, 10, 0);
		
		char string[10];
		strcpy(string, buffer);
		char *splitted_buffer[10];
		//this makes the split
		splitted_buffer[0] = strtok(string,"-"); //burst
		splitted_buffer[1] = strtok(NULL,"-");	//priority
		insert_ready_queue(id, atoi(splitted_buffer[0]), atoi(splitted_buffer[1]), 0, 0);

		char message[50]; 
		strcpy(message, "Proceso recibido, con ID: ");
		char result[50];
		itoa(connect, result, 10);
		strcat(message, result);
		send(connect, message, strlen(message),0); //contesta al cliente
		id++;
	}
	pthread_exit(0);
}

void * cpu_scheduler_action(void * args)
{
	struct dnode *temp;
	temp = remove_first();

	if(flag)
	{
		while (1)
		{
			if (temp != NULL)
			{
				
				temp->process->waiting_time = temp->process->waiting_time + (clock_cpu - temp->process->arrival_time);
				printf("Tiempo de llegada: %d\n", temp->process->arrival_time);
				printf("Timer: %d\n", clock_cpu);
				printf("Ejecutando hilo: %d con burst: %d ha esperado: %d\n", temp->process->process_id,temp->process->burst, temp->process->waiting_time);

				if(rr == 0 || (rr == 1 && temp->process->burst <= burst))
				{
					sleep(temp->process->burst);
					temp->process->turn_around_time = temp->process->waiting_time + temp->process->burst;
					append_end(temp->process->process_id, 0, temp->process->priority, temp->process->waiting_time, temp->process->turn_around_time);
					printf("El proceso: %d ha terminado su ejecucion\n", temp->process->process_id);
				}
				else
				{
					sleep(burst);
					temp->process->burst = temp->process->burst - burst;
					temp->process->turn_around_time = temp->process->turn_around_time + temp->process->waiting_time + burst;
					insert_ready_queue(temp->process->process_id, temp->process->burst, temp->process->priority, temp->process->waiting_time, temp->process->turn_around_time);
				}

			}
			
			temp = remove_first();
		}

	}
	else
	{
		pthread_exit(0);

	}
	
}

void * clock_action(void * args)
{
	while(flag)
	{
		clock_cpu++;
		sleep(1);
	}
}