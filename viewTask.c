#include <stdio.h>
#include "ToDoList.h"

void viewTasks(){
    if (count == 0) { 
        printf("\nNo tasks available!\n"); return; 
    }
    printf("\nID\tTask Name\t\tStatus\n");
    printf("--------------------------------------------\n");
    for(int i=0;i<count;i++){
        printf("%d\t%s\t\t%s\n", Tasks[i].id, Tasks[i].TaskName, Tasks[i].status);
    }
    printf("\n");
}
