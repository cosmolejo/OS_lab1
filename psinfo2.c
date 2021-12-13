#include <unistd.h>
#include <stdio.h>
#include <string.h> //Se incluye para poder usar la función strtok. By C

int main(int argc, char* argv[])
{
    if (argc<2)
        return perror("Falta un argumento"), 1;

    char statFileName[128];             /* /proc/PIC/status - I think 512 bytes is far enough */
   
    sprintf(statFileName, "/proc/%s/status", argv[1]);
    /* Podíamos comprobar que argv[1] es numérico y que es de poco
       tamaño, pero para el ejemplo nos vale. */

    // Demás que habrá que hacer esas comprobaciones después. By C
    FILE *fd = fopen(statFileName, "r"); 
    // fd es el puntero que contiene la dirección al archivo "status" del proceso que se desea analizar, llamada al sistema para "abrir"
    // el archivo, se pasa el argumento "r" ya que vamos a usar este archivo únicamente en modo de lectura (read).

    //char *value, line[512], temp[512]; // Vbles de prueba, aún no se llega a un resultado satisfactorio :c. By C
    //int i = 0; // Contador i para el while que probé que no funcionó. By C
    if (fd == NULL)
        return perror("No puedo encontrar el proceso especificado"),1;
    // Se declaran  las 8 vbles que necesitamos imprimir para la práctica
    char
      name[32],
      state[80];

    unsigned long long
      vmSize,
      vmData,
      vmStk,
      vmExe;

    unsigned long
      v_ctx_swt,
      nv_ctx_swt;

    // Intenté cosas con "strtok()" pero esta destruye los strings, aparentemente es de un sólo uso
    // Probé con "strtok_r()" y tampoco tuve buenos resultados
    // La función "strcpy()" String Copy se usa para copiar el contenido de un string 
    // La función "fgets()" supuestamente se usa para examinar y obtener strings de un archivo
    // Estaba probando la función "fscanf()" que se usa también para extraer información de un archivo
    // pero no me funcionó, sin embargo creo que es la función que se debe usar entonces pa que le
    // cacharreen pls y miren si pueden lograr algo.
    // Ciclo que finalmente no funcionó :c. By C (Aquí ya me rendí) 
    /*
    while (fgets(line, sizeof(line), fd)){
        //strcpy(temp, line);
        if(i == 0){
            strcpy(value, strtok(line, ":  "));
            strcpy(name, strtok(NULL, "\n")+1);
        }
        
        if(i == 2){
            strcpy(value, strtok(line, ":  "));
            strcpy(state, strtok(NULL, "\n")+1);
        }
        i++;
        value = NULL;
    }*/

    // Se supone que en esta parte del código es donde se desarrolla la lógica para acceder al archivo "status"
    // de cada proceso, se extraen los valores y posteriormente se imprimen como se indica en la guía. Osea que de la
    // línea 40 a la linea 70 hay que borrar toda esta mondá y desarollar un algoritmo que sí sirva xd.

    // NOTA: Yo consideré que esos tipos de variable eran los indicados para la información que queremos cargar ahí, pero
    // no los pude probar entonces no sé si sean los ideales. Tengo mis dudas con los valores de memoria que son una
    // cantidad en KB
   
    fclose(fd); // Se cierra el archivo status que se estaba leyendo

    printf("Nombre del proceso: %s\n", name); // Finalmente se imprime la información extraída del archivo
}


/*
Nota: Para compilar el archivo y generar el ejecutable hay que escribir en la terminal (EN LINUX):
        
        gcc -o psinfo psinfo2.c

    Donde "psinfo" será el nombre del archivo ejecutable (asi tal cuál, sin ninguna extensión) y "psinfo2.c" es este archivo 
    que contiene el código fuente del programa

      Para ejecutar el archivo ejecutable generado, escribimos en la terminal (sobre el mismo directorio donde se encuentran los archivos):

        ./psinfo [PID]

    Donde [PID] será el PID del proceso que se desee examinar

    Para saber el PID de un proceso ejecutamos en la terminal:

        ps aux | grep [nombre_aplicación]

    Usaremos la función grep a través de un pipeline para filtrar los procesos y obtener la salida que nos interesa filtrando por el
    nombre del programa/aplicación que deseemos
*/