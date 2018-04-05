
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




