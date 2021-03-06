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
    list_t lista;
    list_init(&lista);
    if (argc < 3)
        return perror("Falta un argumento"), 1;
    if (strcmp(argv[1], "-l") != 0)
        return perror("se esperaba el flag -l"), 1;

    char statFileName[128]; /* /proc/PIC/status - I think 512 bytes is far enough */

    for (int i = 2; i < argc; i++)
    {
        sprintf(statFileName, "/proc/%s/status", argv[i]);

        data response = get_info(statFileName, &flag);
        list_nondup_end_insert(&lista, response);
    }
    if (flag == 0)
    {
        printf("-- Información recolectada!!!\n");
        display(&lista);
    }
}
