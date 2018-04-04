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
#include <unistd.h>

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
void look_clients(){	
	// Inicia el listener
	int listener = begin_listener();

	// Inicia el puerto
	const int PORT = 7200;
	begin_port(listener, PORT);

	// Espera por clientes. Cuando encuentra uno, lo mte a la cola
	printf(" - - - Enlazado al puerto\n");
	while(1){
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
		printf("Recibidos: %s\n", buffer);
//.....................................................................................
//.....................................................................................
	}
	pthread_exit(0);
}


int main(){	
	// Inicia el hilo que esta en constante busqueda de clientes
	pthread_t look_for_clients;
	pthread_create(&look_for_clients, NULL, (void*)look_clients, NULL);

	// Ejecuta el algoritmo seleccionado
	while(1){
		printf("Ejecutando el algoritmo\n");
		sleep(1);

	}
	pthread_join(look_for_clients, NULL);
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