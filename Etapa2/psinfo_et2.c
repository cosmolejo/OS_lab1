#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "linkedlist.c"
#include "info_getter.c"

int main(int argc, char *argv[])
{
    list_t lista;
    list_init(&lista);
    if (argc < 3)
        return perror("Falta un argumento"), 1;
    if (argv[1] == "-l")
        return perror("se esperaba el flag -l"), 1;

    char statFileName[128]; /* /proc/PIC/status - I think 512 bytes is far enough */

    for (int i = 2; i < argc; i++)
    {
        sprintf(statFileName, "/proc/%s/status", argv[i]);

        data response = get_info(statFileName);
        list_nondup_end_insert(&lista,response);
        
        
    }
    printf("-- Información recolectada!!!\n");
    display(&lista);
}
