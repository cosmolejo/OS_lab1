#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "linkedlist.c"
#include "info_getter.c"

int main(int argc, char *argv[])
{
    int flag;
    flag = 0;
    FILE *output;
    list_t lista;
    list_init(&lista);
    if (argc < 3)
        return perror("Falta un argumento"), 1;
    if (strcmp(argv[1], "-r") != 0)
    {
        return perror("se esperaba el flag -r"), 1;
    }
    char statFileName[128]; /* /proc/PIC/status - I think 512 bytes is far enough */
    char pids[128];
    strcat(pids, "psinfo-report");
    for (int i = 2; i < argc; i++)
    {
        char aux[10];
        sprintf(aux, "-%s", argv[i]);
        strcat(pids, aux);
        sprintf(statFileName, "/proc/%s/status", argv[i]);

        data response = get_info(statFileName, &flag);
        list_nondup_end_insert(&lista, response);
    }
    strcat(pids, ".info");
    if (flag == 0)
    {
        printf("Archivo de salida generado: %s\n", pids);
        output = fopen(pids, "w+");
        report(&lista, output);
    }
}
