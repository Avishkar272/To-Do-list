#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ToDoList.h"

void addTasks(){
    if(count == capacity){
        int oldCapacity = capacity;
        capacity *= 2;
        struct ToDoList *temp = realloc(Tasks, capacity * sizeof(struct ToDoList));
        if(temp == NULL){
            printf("Memory reallocation failed\n");
            return;
        }
        Tasks = temp;
        for(int j = oldCapacity; j < capacity; j++) {
            Tasks[j].id = 0;
            Tasks[j].TaskName[0] = '\0';
            Tasks[j].status[0] = '\0';
        }
    }

    int id,d=0;
    printf("Enter Task's id: ");
    while(1){
    scanf("%d",&id);
        for(int i=0;i<count;i++)
        {
            if(id==Tasks[i].id)
            d=1;
        }
        if(d==1){
            printf("\nId already in use , Enter another id\n");
            d=0;
        }
        else
        break;
    }
    Tasks[count].id=id;
    printf("Enter Task Name: ");
    scanf(" %[^\n]", Tasks[count].TaskName);
    strncpy(Tasks[count].status, "Pending", sizeof(Tasks[count].status) - 1);
    Tasks[count].status[sizeof(Tasks[count].status) - 1] = '\0';
    count++;
    saveTasks();
    printf("Task added successfully!\n");
}
