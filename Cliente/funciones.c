// ##############################################
// Pasa de entero a char[]
// - ins value    : Es el valor a convertir
// - char *result : El char donde va a quedar el resultado
// - int base     : Es la base de Conversión, normalmente es 10
// ##############################################
char * itoa (int value, char *result, int base)
{
    if (base < 2 || base > 36) 
    { 
      *result = '\0'; 
      return result; 
    }

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
// - char ip[]            : Direccion IP del servidor 
// - int port             : Puerto de lectura
// - struct info_pcb temp : Estructura de envio de datos
// ####################################################
int create_client(char ip[], int port, struct info_pcb temp)
{
  struct sockaddr_in serverDirection;
  serverDirection.sin_family      = AF_INET;
  serverDirection.sin_addr.s_addr = inet_addr(ip);
  serverDirection.sin_port        = htons(port);

  int client = socket(AF_INET, SOCK_STREAM, 0);
  if (connect(client, (void*)&serverDirection, sizeof(serverDirection)) != 0) {
    perror("No se pudo conectar con el servidor");
  }

  // Envia los datos de la forma --> Burst-Priority
  char data[5];
  char dataTemp[5];
  itoa(temp.burst, data, 10);
  itoa(temp.priority, dataTemp, 10);
  strcat(data, "-");
  strcat(data, dataTemp);
  send(client, data, strlen(data), 0);

  // Recibe los datos
  char* buffer = malloc(50);
  int bytesRecibidos = recv(client, buffer, 50, 0);
  int val = atoi(buffer);
  printf("- - - - Proceso recibidocon el ID:  %s\n", buffer);
  return val;
}


// ####################################################
// Es la accion que va a ejecutar el hilo
// - struct info_pcb *data: Estructura de envio de datos
// ####################################################
void thread_action(struct info_pcb *data)
{
  struct info_pcb temp = {data->burst, data->priority};
  
  printf("\n\n###################################################\n");
  printf("## Se ejecuto el hilo con Burst: %d y Prioridad: %d \n", temp.burst, temp.priority);
  printf("###################################################\n");
  int id  = create_client("127.0.0.1", 7200, temp);
  pthread_exit(0);
}


//####################################################
// Se encarga de concatenar un caracter a un string
// - destino es un char x[]
// - caracter es un char
//####################################################
char *concatenar(char *destino, char caracter)
{
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
int getRandom(int limit)
{
  return 3 + rand() % (limit - 2);
}


//#############################################################
// Verifica si los valores de burst son correctos y si es posible usarlos
// - int minBurst : Minimo aceptado > 0
// - int maxBurst : Maximo aceptado
// Retorna 1 si los valores son aceptados
// Retorna 0 si los valores no son aceptados
//############################################################# 
int validar_bursts_entrada(int minBurst, int maxBurst)
{
  if ((minBurst >= maxBurst) || (minBurst < 0) || (maxBurst < 0))
  {
    return 0;
  }
  return 1;
}


//#############################################################
// Verifica si los valores de tiempo son correctos y si es posible usarlos
// - int minTime : Minimo aceptado
// - int maxTime : Maximo aceptado
// Retorna 1 si los valores son aceptados
// Retorna 0 si los valores no son aceptados
//#############################################################
int validar_tiempos_entrada(int minTime, int maxTime)
{
  if ((minTime >= maxTime) || (minTime <= 0) || (maxTime <= 0))
  {
    return 0;
  }
  return 1;
}