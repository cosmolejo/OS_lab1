#include <unistd.h>
#include <stdio.h>
#include <string.h> //Se incluye para poder usar la función strtok. By C

int main(int argc, char *argv[])
{
    if (argc < 2)
        return perror("Falta un argumento"), 1;

    char statFileName[128]; /* /proc/PIC/status - I think 512 bytes is far enough */

    sprintf(statFileName, "/proc/%s/status", argv[1]);
    /* Podíamos comprobar que argv[1] es numérico y que es de poco
       tamaño, pero para el ejemplo nos vale. */

    // Demás que habrá que hacer esas comprobaciones después. By C
    FILE *fd = fopen(statFileName, "r");
    // fd es el puntero que contiene la dirección al archivo "status" del proceso que se desea analizar, llamada al sistema para "abrir"
    // el archivo, se pasa el argumento "r" ya que vamos a usar este archivo únicamente en modo de lectura (read).

    char
        *value,
        *aux,
         name[32],
        state[80],
        line[512],
        temp[512],
        vmSize[512],
        vmData[512],
        vmStk[512],
        vmExe[512],
        v_ctx_swt[512],
        nv_ctx_swt[512]; // Vbles de prueba, aún no se llega a un resultado satisfactorio :c. By C

    int i = 0; // Contador i para el while que probé que no funcionó. By C
    if (fd == NULL)
        return perror("No puedo encontrar el proceso especificado"), 1;


    while (fgets(line, sizeof(line), fd))
    {
        //strcpy(temp, line);

        value = strtok(line, ":");
        aux = strtok(NULL, "\n");
        if (strcmp(value, "Name") == 0)
        {
            strcpy(name, aux);
        }
        if (strcmp(value, "State") == 0)
        {
            strcpy(state, aux);
        }
         if (strcmp(value, "VmSize") == 0)
        {
            strcpy(vmSize, aux);
        }
        if (strcmp(value, "VmExe") == 0)
        {
            strcpy(vmExe, aux);
        }
       

        if (strcmp(value, "VmData") == 0)
        {
            strcpy(vmData, aux);
        }
        if (strcmp(value, "VmStk") == 0)
        {
            strcpy(vmStk, aux);
        }

        if (strcmp(value, "voluntary_ctxt_switches") == 0)
        {
            strcpy(v_ctx_swt, aux);
        }
        if (strcmp(value, "nonvoluntary_ctxt_switches") == 0)
        {
            strcpy(nv_ctx_swt, aux);
        }

        i++;
        value = memset(value, 0, strlen(value));
        aux = memset(aux, 0, strlen(aux));
    }

    fclose(fd); // Se cierra el archivo status que se estaba leyendo

    printf("-------OUTPUT-------\n");
    printf("Nombre del proceso: %s\n", name); // Finalmente se imprime la información extraída del archivo
    printf("Estado: %s\n", state);
    printf("Tamaño total de la imagen de memoria: %s\n", vmSize);
    printf("\tTamaño de la memoria de la región TEXT:  %s\n", vmData);
    printf("\tTamaño de la memoria de la región DATA: %s\n", vmStk);
    printf("\tTamaño de la memoria de la región STACK: %s\n", vmExe);
    printf("Número de cambios de contexto realizados (voluntarios - no voluntarios): %s - %s\n",
     v_ctx_swt,nv_ctx_swt);

}
