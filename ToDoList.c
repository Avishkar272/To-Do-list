#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ToDoList
{
    int id;
    char TaskName[100];
    char status[20]; 
};
struct ToDoList *Tasks;
int maxTasks=0;
int count=0;

void addTasks();
void viewTasks();
void markcomp();
void markincomp();
void deleteTasks();
void saveTasks();
void loadTasks();

int main(){
    Tasks = (struct ToDoList *)malloc(maxTasks*sizeof(struct ToDoList));
    int choice;
    loadTasks();
    while (1){
     printf("--------TO DO LIST-------");
     printf("1. Add a task\n");
     printf("2. View tasks\n");
     printf("3. Mark a task as completed\n");
     printf("4. Mark a task incomplete");
     printf("5. Delete a task\n");
     printf("6. Exit\n");
     scanf("%d", &choice);
    
     switch(choice)
     {
        case 1:
         addTasks();
        break;
        case 2:
         viewTasks();
        break;
        case 3:
         markcomp();
        break;
        case 4:
         markincomp();
        break;
        case 5:
         deleteTasks();
        break;
        case 6:
         saveTasks();
         exit(0);
        break;
        default:
        printf("Wrong input");
     }
    }
    free(Tasks);
}
