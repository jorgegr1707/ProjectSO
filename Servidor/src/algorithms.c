// ###############################################################################
// This function receives the necessaries parameters to insert in the ready queue 
// depending of the algorithm selectionated
// ###############################################################################
void insert_ready_queue(int id, int burst, int priority, int waiting_time, int turn_around_time)
{
	switch (algorithm_type)
	        {
	            case 1: //FCFS Algorithm
	                append(id, burst, priority, waiting_time, clock_cpu, turn_around_time);
	                break;
	            case 2: //SJF Algorithm
	            	insert_by_burst(id, burst, priority, waiting_time, clock_cpu, turn_around_time);
	                break;
	            case 3: //HPF Algorithm
	                insert_by_priority(id, burst, priority, waiting_time, clock_cpu, turn_around_time);
	                break;
	            case 4: //Round Robin Algorithm
	            	rr = 1; 
	            	append(id, burst, priority, waiting_time, clock_cpu, turn_around_time);
	                break;
	        }
}


// ###############################################################################
// This thread is looking for clients all the time and inserts the process in the 
// ready queue when finds one
// ###############################################################################
void * job_scheduler_action(void * args)
{
	
	int listener = begin_listener(); // Start listener

	const int PORT = 7200; // Start port
	begin_port(listener, PORT);

	if (flag)
	{
		while(1) //Wait for clients
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
			// Make the split
			splitted_buffer[0] = strtok(string,"-"); //burst
			splitted_buffer[1] = strtok(NULL,"-");	//priority
			insert_ready_queue(id, atoi(splitted_buffer[0]), atoi(splitted_buffer[1]), 0, 0);

			char message[50]; 
			strcpy(message, "Process received, with ID: ");
			char result[50];
			itoa(connect, result, 10);
			strcat(message, result);
			send(connect, message, strlen(message),0); //Send received message to client
			id++; //Increment id for the next process
		}

	}
	else
	{
		pthread_exit(0);
	}
	
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
		while (1)
		{
			if (temp != NULL)
			{
				// Set the process waiting time 
				temp->process->waiting_time = temp->process->waiting_time + (clock_cpu - temp->process->arrival_time);
				printf("Executing process: %d burst: %d has waited: %d\n", temp->process->process_id,temp->process->burst, temp->process->waiting_time);

				if(rr == 0 || (rr == 1 && temp->process->burst <= burst))
				{
					// Simulate the time in the CPU
					sleep(temp->process->burst);
					//Set the process turn around time
					temp->process->turn_around_time = temp->process->waiting_time + temp->process->burst;
					// Insert process in the finished processes queue
					append_end(temp->process->process_id, 0, temp->process->priority, temp->process->waiting_time, temp->process->turn_around_time);
					printf("Process: %d has finished.\n", temp->process->process_id);
				}
				else
				{
					// Simulate the time in the CPU 
					sleep(burst);
					//Set the process burst
					temp->process->burst = temp->process->burst - burst;
					//Set the process turn around time
					temp->process->turn_around_time = temp->process->turn_around_time + temp->process->waiting_time + burst;
					// Insert in the ready queue again
					insert_ready_queue(temp->process->process_id, temp->process->burst, temp->process->priority, temp->process->waiting_time, temp->process->turn_around_time);
				}

			}
			// Look for the next process
			temp = remove_first();
		}

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
}