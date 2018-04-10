// ###############################################################################
// This function receives the necessaries parameters to insert in the ready queue 
// depending of the algorithm selectionated
// Parameters: Process Id, Process Burst, Process Priority, Process waiting time,
//			   Process turn around time, Process Original Burst, Process Original
//			   time around time
// These parameters are the PCB information
// ###############################################################################
void insert_ready_queue(int id, int burst, int priority, int waiting_time, int turn_around_time, int burst_original, int arrival_time_original)
{
	if(arrival_time_original == -1)
	{
		arrival_time_original = clock_cpu;
	}

	switch (algorithm_type)
	        {
	            case 1: //FCFS Algorithm
	                append(id, burst, priority, waiting_time, clock_cpu, turn_around_time, burst_original, arrival_time_original);
	                break;
	            case 2: //SJF Algorithm
	            	insert_by_burst(id, burst, priority, waiting_time, clock_cpu, turn_around_time, burst_original, arrival_time_original);
	                break;
	            case 3: //HPF Algorithm
	                insert_by_priority(id, burst, priority, waiting_time, clock_cpu, turn_around_time, burst_original, arrival_time_original);
	                break;
	            case 4: //Round Robin Algorithm
	            	rr = 1; 
	            	append(id, burst, priority, waiting_time, clock_cpu, turn_around_time, burst_original, arrival_time_original);
	                break;
	        }
}


// ###############################################################################
// This thread is looking for clients all the time and inserts the process in the 
// ready queue when finds one
// ###############################################################################
void * job_scheduler_action(void * args)
{
	int listener   = begin_listener(); // Start listener
	const int PORT = 7200;             // Start port
	begin_port(listener, PORT);
	
	while(flag) //Wait for clients
	{
		// Create the struct of the client
		struct sockaddr_storage client;
		unsigned int address_size = sizeof(client);

		// Verify if there is a client
		int connect = accept(listener, (struct sockaddr*)&client, &address_size);
		
		// Receive data from the cliente in buffer, it's a string "burst-priority"
		char* buffer = malloc(10);
		recv(connect, buffer, 10, 0);
		
		// This section makes the split, converts string to int and inserts data in the ready queuee
		char string[10];
		strcpy(string, buffer);
		char *splitted_buffer[10];
		splitted_buffer[0] = strtok(string,"-"); //burst
		splitted_buffer[1] = strtok(NULL,"-");	//priority
		insert_ready_queue(connect, atoi(splitted_buffer[0]), atoi(splitted_buffer[1]), 0, 0, atoi(splitted_buffer[0]), -1);

		// Send data
		char result[6];
		itoa(connect, result, 10);
		send(connect, result, strlen(result), 0); 
	}
	pthread_exit(0);	
}


// ###############################################################################
// This thread executes the processes of the ready queue
// ###############################################################################
void * cpu_scheduler_action(void * args)
{
	struct dnode *temp;
	temp = remove_first();

	if(flag)
	{
		while (flag)
		{
			if (temp != NULL)
			{
				// Set the process waiting time 
				temp->process->waiting_time = temp->process->waiting_time + (clock_cpu - temp->process->arrival_time);
				printf("- - - Executing process: %d, burst: %d, has waited: %d\n", temp->process->process_id,temp->process->burst, temp->process->waiting_time);

				if(rr == 0 || (rr == 1 && temp->process->burst <= burst))
				{
					// Simulate the time in the CPU
					sleep(temp->process->burst);
					//Update the cpu working time counting
					cpu_working_time += temp->process->burst;
					//Set the process turn around time
					temp->process->turn_around_time = temp->process->waiting_time + temp->process->burst;
					// Insert process in the finished processes queue
					append_end(temp->process->process_id, 0, temp->process->priority, temp->process->waiting_time, temp->process->turn_around_time, 
						temp->process->arrival_time, temp->process->burst_original, temp->process->arrival_time_original);
					
					printf("- - - Process: %d has finished.\n", temp->process->process_id);
				}
				else
				{
					// Simulate the time in the CPU 
					sleep(burst);
					//Update the cpu working time counting
					cpu_working_time += burst;
					//Set the process burst
					temp->process->burst = temp->process->burst - burst;
					//Set the process turn around time
					temp->process->turn_around_time = temp->process->turn_around_time + temp->process->waiting_time + burst;
					// Insert in the ready queue again
					insert_ready_queue(temp->process->process_id, temp->process->burst, temp->process->priority, temp->process->waiting_time, 
						temp->process->turn_around_time, temp->process->burst_original, temp->process->arrival_time_original);
				}

			}
			// Look for the next process
			temp = remove_first();

		}
		pthread_exit(0);

	}
	else
	{
		pthread_exit(0);

	}	
}


// ###############################################################################
// This thread simulates the CPU clock
// ###############################################################################
void * clock_action(void * args)
{
	while(flag)
	{
		clock_cpu++; //This variable keeps the actual time
		sleep(1);
	}
	pthread_exit(0);
}


// ###############################################################################
// This thread keeps waiting for a user entry 
// ###############################################################################
void * terminalIn_thread_action(void * args)
{
	
	while(1){
		
		scanf("%d", &terminal_entry);
		
		//Queue is displayed
		if(terminal_entry == 1)				
		{
			sem_wait(&semaphore_thread);

			printf("---- Queue ----\n");
			display();

			sem_post(&semaphore_thread);
			terminal_entry = 0;
			
		} 
		//All the threads are finished and also the server
		else if(terminal_entry == 2)		
		{

			flag = 0;

			printf("Finalizing processes\n\n");

			sem_wait(&semaphore_thread);

			final_display();

			sem_post(&semaphore_thread);
			pthread_exit(0);

		}
		else 
		{

			terminal_entry = 0;
		}

	}
}