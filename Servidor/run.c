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

#include "headers/linked_list.h"
#include "src/linked_list.c"
#include "headers/process.h"

int rr;
int burst;
int algorithm_type;
int clock_cpu = 0;
int flag; //keep running or not
int id = 0;

//esto hay q acomodarlo bien xD
char * itoa (int value, char *result, int base){
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

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
// Abre el socket
// ##############################################
int open_socket(){
	int s = socket(PF_INET, SOCK_STREAM, 0);
	if(s == -1)
		printf("Error del socket\n");
	return s;
}


// ##############################################
// Conecta con el puerto
// - socket es el socket ya abierto
// - port es el puerto de escucha
// ##############################################
void bind_to_port(int socket, int port){
	struct sockaddr_in name;
	name.sin_family      = PF_INET;
	name.sin_port        = (in_port_t)htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	int reuse = 1;
	
	if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int)) == -1){
		printf("error 1\n");
	}

	int c = bind(socket, (struct sockaddr*)&name, sizeof(name));
	if (c == -1){
		printf("error 2\n");
	}
}



// ##############################################
// Se encarga de iniciar el listener
// ##############################################
int begin_listener(){
	int listener = open_socket();	
	if (listener == -1){
		printf("No se pudo iniciar el listener listener\n");
		return 0;
	}
	return listener;
}


// ##############################################
// Se encarga de iniciar el puesto de acceso 
// - listener es el istener ya abierto
// - PORT es el puesto al que se va a comunicar
// ############################################## 
void begin_port(int listener, int PORT){
	bind_to_port(listener, PORT);
	if (listen (listener, 10) == -1){
		printf("No es posible escuchar en este puerto\n");
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

	// Espera por clientes. Cuando encuentra uno, lo mte a la cola
	printf(" - - - Enlazado al puerto\n");
	while(1)
	{
		// Crea la estructura del cliente que se va a recibir
		struct sockaddr_storage client;
		unsigned int address_size = sizeof(client);
		printf("\n - - - Esperando al cliente\n");

		// Verifica si algun cliente necesita el servicio
		int connect = accept(listener, (struct sockaddr*)&client, &address_size);
		printf("- - - Atendiendo al cliente\n");
		
//.....................................................................................
//.....................................................................................
		// AQUI TOMA LA connect Y LO DEBE COLOCAR EN LA COLA
		// ASI Recibe datos
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
		send(connect, message, strlen(message),0);
		id++;


		printf("Recibidos: %s\n", buffer);
//.....................................................................................
//.....................................................................................
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
				printf("%d\n", clock_cpu);
				printf("%d\n", temp->process->arrival_time);

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
			sleep(1);
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