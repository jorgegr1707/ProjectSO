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

void * job_scheduler_action(void * args)
{
	srand(time(0));
	int burst; 
	int priority;
	for (int i = 0; i < 5; i++)
	{
		burst = (rand() % 6) + 1;
		priority = (rand() % 10) + 1;
		switch (algorithm_type)
        {
            case 1:
                append(i, burst, priority);
                break;
            case 2:
            	insert_by_burst(i, burst, priority);
                break;
            case 3:
                insert_by_priority(i, burst, priority);
                break;
            case 4:
            	rr = 1;
            	append(i, burst, priority);
                break;

        }
	}
	pthread_exit(0);
}

void * cpu_scheduler_action(void * args)
{
	struct dnode *temp;
	temp = remove_first();
	
	while (temp != NULL)
	{
		printf("Ejecutando hilo: %d con burst: %d\n", temp->process->process_id,temp->process->burst);

		if(rr == 0 || (rr == 1 && temp->process->burst <= burst))
		{
			sleep(temp->process->burst);
			temp->process->burst = 0;
			printf("El proceso: %d ha terminado su ejecucion\n", temp->process->process_id);
		}
		else
		{
			sleep(burst);
			temp->process->burst = temp->process->burst - burst;
			append(temp->process->process_id, temp->process->burst, temp->process->priority);
		}
		temp = remove_first();
	}
	pthread_exit(0);
}



int main()
{
    
            	
    printf("\n\nWelcome to the server, please select one option");
    printf("\n1. FCFS Algorithm \n2. SJF Algorithm\n3. HPF Algorithm\n4. RR Algorithm\n0. Exit\n");
    printf("\nEnter Choice 0-4? : ");
    scanf("%d", &algorithm_type);

    printf("\nBurst: ");
    scanf("%d", &burst);

    pthread_t job_scheduler;
	pthread_create(&job_scheduler, NULL, (void*)job_scheduler_action, NULL);
	pthread_join(job_scheduler, NULL);

	pthread_t cpu_scheduler;
	pthread_create(&cpu_scheduler, NULL, (void*)cpu_scheduler_action, NULL);
	pthread_join(cpu_scheduler, NULL);
	
        
}





