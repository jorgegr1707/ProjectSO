#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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

   	pthread_join(clock_thread, NULL);

	pthread_join(job_scheduler, NULL);
		
	pthread_join(cpu_scheduler, NULL);

	scanf("%d", &flag);
	
	printf("xxxxxxxxxxxxxxxxxxxxx\n");

}


/*
		// Recibe datos
		char* buffer = malloc(10);
		int bytesRecibidos = recv(connect, buffer, 10, 0);
		printf("Recibidos: %s\n", buffer);


		// Duerme un rato
		srand(time(0));
		int r = 8 + rand() % 4;
		printf("- - - Voy a dormir: %d\n", r);
		sleep(r);
		
		// Envia datos
		char *msg = advice[rand()%5];
		send(connect, msg, strlen(msg), 0);
		msg = NULL;
		printf("- - - Le conteste a: %s\n", buffer);
		close(connect);
*/