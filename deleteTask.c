#include <stdio.h>
#include <stdlib.h>
#include "ToDoList.h"

void deleteTasks()
{
    int id, found, i, j;
    char confirm;
    if(count == 0)
    {
        printf("\nNo tasks to delete!\n");
        return;
    }
    while(1)
    {
        printf("\nEnter Task ID to delete (or -1 to stop): ");
        scanf("%d", &id);
        if(id == -1)
        {
            printf("\nExited deletion mode.\n");
            break;
        }
        found = 0;
        for(i = 0; i < count; i++)
        {
            if(Tasks[i].id == id && Tasks[i].TaskName[0] != '\0')
            {
                found = 1;
                printf("Delete task: \"%s\" ? (Y/y = Yes, N/n = No): ", Tasks[i].TaskName);
                scanf(" %c", &confirm);
                if(confirm == 'Y' || confirm == 'y')
                {
                    for(j = i; j < count - 1; j++)
                    {
                        Tasks[j] = Tasks[j + 1];
                    }
                    count--;
                    if(count > 0)
                    {
                        struct ToDoList *temp = (struct ToDoList*)realloc(Tasks, count * sizeof(struct ToDoList));
                        if(temp != NULL)
                        {
                            Tasks = temp;
                            saveTasks();
                        }
                        else
                        {
                            printf("Warning: Reallocation failed. Memory not shrunk.\n");
                        }
                    }
                    else
                    {
                        free(Tasks);
                        Tasks = NULL;
                    }
                    printf("Task with ID %d deleted successfully!\n", id);
                }
                else
                {
                    printf("Deletion cancelled.\n");
                }
                break;
            }
        }
        if(found == 0)
        {
            printf("Task with ID %d not found!\n", id);
        }
    }
}
