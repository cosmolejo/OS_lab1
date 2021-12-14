#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "linkedlist.h"

data get_info(char statFileName[], int *flag)
{

    data datos;
    FILE *fd = fopen(statFileName, "r");

    char
        *value,
        *aux,
        pid[15],
        name[32],
        state[80],
        line[512],
        temp[512],
        vmSize[512],
        vmData[512],
        vmStk[512],
        vmExe[512],
        v_ctx_swt[512],
        nv_ctx_swt[512];
    int i = 0;
    if (fd == NULL){
        perror("No puedo encontrar el proceso especificado");
        *flag = 1;
        return datos;
    }
    while (fgets(line, sizeof(line), fd))
    {

        value = strtok(line, ":");
        aux = strtok(NULL, "\n");
        if (strcmp(value, "Pid") == 0)
        {
            strcpy(pid, aux);
        }
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

    fclose(fd);

    strcpy(datos.pid, pid);
    strcpy(datos.name, name);
    strcpy(datos.state, state);
    strcpy(datos.line, line);
    strcpy(datos.temp, temp);
    strcpy(datos.vmSize, vmSize);
    strcpy(datos.vmData, vmData);
    strcpy(datos.vmStk, vmStk);
    strcpy(datos.vmExe, vmExe);
    strcpy(datos.v_ctx_swt, v_ctx_swt);
    strcpy(datos.nv_ctx_swt, nv_ctx_swt);

   return datos;
}