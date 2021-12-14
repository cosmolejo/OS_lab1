#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "linkedlist.c"
#include "info_getter.c"
#include "string_checker.c"

int main(int argc, char *argv[])
{
    FILE *output;
    list_t lista;
    list_init(&lista);
    if (argc < 3)
        return perror("Falta un argumento"), 1;
    int sw, flag;
    sw = 0;

    if (strcmp(argv[1], "-r") != 0 && strcmp(argv[1], "-l") != 0)
    {
        return perror("se esperaba el flag -r o -l"), 1;
    }
    for (int i = 2; i < argc; i++)
    {
        if (StartsWith(argv[i], "-"))
        {
            return perror("Ya se ha ingresado un flag, se esperaba un pid"), 1;
        }
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
    if (flag == 0)
    {
        if (strcmp(argv[1], "-r")==0)
        {
            strcat(pids, ".info");
            printf("Archivo de salida generado: %s\n", pids);
            output = fopen(pids, "w+");
            report(&lista, output);
        }
        else
        {
            printf("-- Información recolectada!!!\n");
            display(&lista);
        }
    }
}
