#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <time.h>

#include "src/sockets.c"
#include "src/linked_list.c"
#include "headers/variables.h"
#include "src/algorithms.c"


int main()
{	
    printf("\n\n");
    printf("#########################################################\n");
    printf("###  Welcome to the server, please select one option  ###\n");
    printf("#########################################################\n");
    printf("  1. FCFS Algorithm\n");
    printf("  2. SJF Algorithm\n");
    printf("  3. HPF Algorithm\n");
    printf("  4. RR Algorithm\n");
    printf("  0. Exit\n");
    printf("#########################################################\n");
    printf("Enter Choice 0-4? : ");
    scanf("%d", &algorithm_type);
    printf("#########################################################\n");

    if (algorithm_type == 4)
    {
    	printf("\nQuantum: ");
    	scanf("%d", &burst);
    }
    printf("\n#########################################################\n");
    printf("Instructions:\n");
    printf("- Press 1 to display the process queue\n");
    printf("- Press 2 for finishing the server and display the tables\n");
    printf("#########################################################\n");

    printf("\n#################################\n");
    printf("- - - The server is running - - -\n");
    printf("#################################\n\n");
    sem_init(&semaphore_thread, 0, 1);  //Semaphore Initialized 
    
    flag = 1;
    
    pthread_t clock_thread, job_scheduler, cpu_scheduler, terminalIn_thread;
    
    pthread_create(&terminalIn_thread, NULL, (void*)terminalIn_thread_action, NULL); //Thread waiting for a terminal entry
	pthread_create(&clock_thread, NULL, (void*)clock_action, NULL);
	pthread_create(&job_scheduler, NULL, (void*)job_scheduler_action, NULL);
	pthread_create(&cpu_scheduler, NULL, (void*)cpu_scheduler_action, NULL);
    
    pthread_join(terminalIn_thread, NULL);
   	pthread_join(clock_thread, NULL);
	pthread_join(job_scheduler, NULL);
	pthread_join(cpu_scheduler, NULL);

    sem_destroy(&semaphore_thread);     //Semaphore destroyed

    printf("\n-------------------------> SERVER FINALIZED <-----------------------------\n");

}
