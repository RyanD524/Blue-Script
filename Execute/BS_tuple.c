#pragma once

#include <stdio.h>
#include <string.h>

static struct { char strVal[200]; int intVal; } tuple[200];
static int tupleCount = 0;

void listTuples(void) {
    printf("==========\nTuple count is %d\n", tupleCount);
    for (int i = 0; i < tupleCount; ++i)
        printf("   [%s] -> %d\n", tuple[i].strVal, tuple[i].intVal);
    puts("==========");
}

int getTuple(char *str){
    for(int i = 0; i < tupleCount; i++)
    {
        if (*tuple[i].strVal == *str)
        {
            return tuple[i].intVal;
        }
    }

    return -1;

}
void addTuple(char *str, int val) {
    //printf("Adding '%s', mapped to %d\n", str, val);
    strcpy(tuple[tupleCount].strVal, str);
    tuple[tupleCount++].intVal = val;
}

void deleteTuple(char *str) {
    int index = 0;
    while (index < tupleCount) {
        if (strcmp(str, tuple[index].strVal) == 0) break;
        ++index;
    }
    if (index == tupleCount) return;

    //printf("Deleting '%s', mapped to %d\n", str, tuple[index].intVal);
    if (index != tupleCount - 1) {
        strcpy(tuple[index].strVal, tuple[tupleCount - 1].strVal);
        tuple[index].intVal = tuple[tupleCount - 1].intVal;
    }
    --tupleCount;
}