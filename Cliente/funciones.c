// ####################################################
// De int a string 
// - value es el entero
// - result es la variable donde queda el resultado
// - base es la base a la que se va a combertir
// ####################################################
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




// ####################################################
// Crea el cliente que va a ir a consultar al servidor 
// ####################################################
int create_client(char ip[], int port, struct info_pcb temp){
  struct sockaddr_in direccionServidor;
  direccionServidor.sin_family = AF_INET;
  direccionServidor.sin_addr.s_addr = inet_addr(ip);
  direccionServidor.sin_port = htons(port);

  int cliente = socket(AF_INET, SOCK_STREAM, 0);
  if (connect(cliente, (void*)&direccionServidor, sizeof(direccionServidor)) != 0) {
    perror("No se pudo conectar con el servidor");
  }

  // envia los datos 
  char data[5];
  char dataTemp[5];
  itoa(temp.burst, data, 10);
  itoa(temp.priority, dataTemp, 10);
  strcat(data, "-");
  strcat(data, dataTemp);
  send(cliente, data, strlen(data), 0);

  // Recibe los datos
  char* buffer = malloc(10);
  int bytesRecibidos = recv(cliente, buffer, 10, 0);
  int val = atoi(buffer);
  printf("ID del proceso: %d, %d, %d\n", temp.burst, temp.priority, val);
  return val;
}


// ####################################################
// Es la accion que va a ejecutar el hilo
// - data es el struct con los datos de rafaga y prioridad
// ####################################################
void thread_action(struct info_pcb *data){
  struct info_pcb temp = {data->burst, data->priority};
  printf("Se ejecuto el hilo con B: %d y P: %d\n", temp.burst, temp.priority);
  // Accion necesaria del hilo
  // Aqui se envia via sockets...
  //for (int i = 0; i < 4; ++i){
    printf("     Estoy esperando respuesta con Burst:%d, Priority: %d\n", temp.burst, temp.priority);
    int id  = create_client("127.0.0.1", 7200, temp);
    //sleep(1);
  //}
  pthread_exit(0);
}


//####################################################
// Se encarga de concatenar un caracter a un string
// - destino es un char x[]
// - caracter es un char
//####################################################
char *concatenar(char *destino, char caracter){
  char *cad;
  int i;
  cad = realloc(destino, strlen(destino) + 2);
  for (i = 0; cad[i] != '\0'; i++);          
    cad[i++] = caracter;                     
  cad[i] = '\0';                             
    return destino;
}


//#############################################################
// Genera numeros aleatorios con un limite
//#############################################################
int getRandom(int limit){
  return 3 + rand() % (limit - 2);
}