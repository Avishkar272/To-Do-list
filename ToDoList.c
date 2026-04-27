#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ToDoList.h"

struct ToDoList *Tasks=NULL;
int count=0;
int capacity=2;


int main()
{   
    int tries=0;
    char saved_pass[]="pass@123";
    char username[]="Harshit Saklani";
    char input_pass[50];

    printf("Enter the password for %s\n",username);

    while(tries!=3){
        scanf(" %[^\n]",input_pass);
        if(strcmp(saved_pass,input_pass)==0)
            break;
        else
        printf("Wrong Password! There are now %d tries left\n",(2-tries));
        tries++;
        if(tries==3){
            printf("You have reached the max limit to enter the password");
            exit(0);
        }
    }
    printf("Correct password entered!\n");

    
    Tasks = (struct ToDoList *)calloc(capacity, sizeof(struct ToDoList));
    if (Tasks == NULL) { 
        printf("Memory allocation failed\n"); exit(1);
    }
    loadTasks();
    int choice;
    while (1){
        printf("\n--------TO DO LIST-------\n");
        printf("1. Add a task\n");
        printf("2. View tasks\n");
        printf("3. Update Task\n");
        printf("4. Delete a task\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
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
                updateTasks();
                break;
            case 4:
                deleteTasks();
                break;
            case 5:
                free(Tasks);
                exit(0);
                break;
                default:
                printf("\nWrong input\n");
     }
    }
}
