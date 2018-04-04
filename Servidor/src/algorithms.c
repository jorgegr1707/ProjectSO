#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "../headers/linked_list.h"
#include "linked_list.c"
#include "../headers/process.h"

int rr;
int burst;
int algorithm_type;
int clock_cpu = 0;
int flag; //keep running or not

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

void * job_scheduler_action(void * args)
{
	srand(time(0));
	int burst; 
	int priority;
	if(flag)
	{
		for (int i = 0; i < 5; i++)
		{
			burst = (rand() % 6) + 1;
			priority = (rand() % 10) + 1;
			insert_ready_queue(i, burst, priority, 0, 0);
		}
	
	}
	else
	{
		pthread_exit(0);
	}
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



int main()
{
    
            	
    printf("\n\nWelcome to the server, please select one option");
    printf("\n1. FCFS Algorithm \n2. SJF Algorithm\n3. HPF Algorithm\n4. RR Algorithm\n0. Exit\n");
    printf("\nEnter Choice 0-4? : ");
    scanf("%d", &algorithm_type);

    printf("\nBurst: ");
    scanf("%d", &burst);

    flag = 1;
    
    pthread_t clock_thread, job_scheduler, cpu_scheduler;
	pthread_create(&clock_thread, NULL, (void*)clock_action, NULL);
	pthread_create(&job_scheduler, NULL, (void*)job_scheduler_action, NULL);
	pthread_create(&cpu_scheduler, NULL, (void*)cpu_scheduler_action, NULL);

    while(1)
    {
    	
		pthread_join(clock_thread, NULL);

		pthread_join(job_scheduler, NULL);
		
		pthread_join(cpu_scheduler, NULL);
	}
    
	
        
}





