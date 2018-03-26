#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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


int main(){
	// Datos inutiles para respuesta
	char * advice[] = {"4444", "1111", "3333", "2222", "888"};

	// variables de sistema
	const int PORT = 7200;

	// Inicia el listener
	int listener = open_socket();	
	if (listener == -1){
		printf("Error en listener\n");
		return 0;
	}

	// Inicia el puerto 
	bind_to_port(listener, PORT);
	if (listen (listener, 10) == -1){
		printf("no es posible escuchar\n");
		return 0;
	}

	// Inicia el servidor
	printf(" - - - Enlazado al puerto\n");
	while(1){
		struct sockaddr_storage client;
		unsigned int addres_size = sizeof(client);
		printf(" - - - Esperando al cliente...\n\n");

		// Verifica la conexion
		int connect = accept(listener, (struct sockaddr*)&client, &addres_size);
		if (connect == -1){
			printf("@ - - No se pudo conectar\n");
		}
		printf(" - - - Atendiendo al cliente\n");
		
		// Recibe datos
		char* buffer = malloc(10);
		int bytesRecibidos = recv(connect, buffer, 10, 0);
		printf("Recibidos: %s\n", buffer);

		// Envia datos
		sleep(1);
		char *msg = advice[rand()%5];
		send(connect, msg, strlen(msg), 0);
		msg = NULL;
		close(connect);
	}
}