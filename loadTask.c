#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ToDoList.h"

void loadTasks()
{
    FILE *fp = fopen("tasks.txt", "r");
    
    if (fp == NULL)
    {
        return;
    }
    
    count = 0;
    int id;
    char idStr[20];
    char taskName[100];
    char status[20];
    
    while (fgets(idStr, sizeof(idStr), fp) != NULL)
    {
        id = atoi(idStr);
        
        if (count >= capacity)
        {
            int oldCapacity = capacity;
            capacity *= 2;
            struct ToDoList *temp = (struct ToDoList*)realloc(Tasks, capacity * sizeof(struct ToDoList));
            if (temp == NULL)
            {
                printf("Memory reallocation failed during loading\n");
                break;
            }
            Tasks = temp;
            for(int j = oldCapacity; j < capacity; j++) {
                Tasks[j].id = 0;
                Tasks[j].TaskName[0] = '\0';
                Tasks[j].status[0] = '\0';
            }
        }
        
        if (fgets(taskName, sizeof(taskName), fp) == NULL) break;
        int len = strlen(taskName);
        if (len > 0 && taskName[len-1] == '\n') {
            taskName[len-1] = '\0';
        }
        
        if (fgets(status, sizeof(status), fp) == NULL) break;
        len = strlen(status);
        if (len > 0 && status[len-1] == '\n') {
            status[len-1] = '\0';
        }
        
        Tasks[count].id = id;
        strncpy(Tasks[count].TaskName, taskName, sizeof(Tasks[count].TaskName) - 1);
        Tasks[count].TaskName[sizeof(Tasks[count].TaskName) - 1] = '\0';
        strncpy(Tasks[count].status, status, sizeof(Tasks[count].status) - 1);
        Tasks[count].status[sizeof(Tasks[count].status) - 1] = '\0';
        count++;
    }
    
    fclose(fp);
}
