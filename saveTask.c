#include <stdio.h>
#include "ToDoList.h"

void saveTasks()
{
    FILE *fp = fopen("tasks.txt", "w");

    if (fp == NULL)
    {
        printf("Error: Could not open file for saving tasks!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (fprintf(fp, "%d\n", Tasks[i].id) < 0 ||
            fprintf(fp, "%s\n", Tasks[i].TaskName) < 0 ||
            fprintf(fp, "%s\n", Tasks[i].status) < 0)
        {
            printf("Error: Failed to write to file!\n");
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}
