#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxTasks 100

struct ToDoList
{
    int id;
    char TaskName[100];
    char status[20]; 
};
struct ToDoList Tasks[maxTasks];
int count=0;

void addTasks();
void viewTasks();
void updateTasks();
void deleteTasks();
void saveTasks();
void loadTasks();

void viewTasks(){
    printf("ID\tTaskName\tStatus");
    for(int i=0;i<count;i++){
        printf("%d\t%s\t%s",Tasks[i].id,Tasks[i].TaskName,Tasks[i].status);
    }
}

void updateTasks(){
char ch;
int id,fl=0;
 
printf("Enter the Task ID that needs to be updated");
scanf("%d",&id);
for(int i=0;i<count;i++)
{
    if(Tasks[i].id==id && Tasks[i].TaskName[0]!='\0')
    {
     fl=1;
     break;
    }
    if(Tasks[i].id==id && Tasks[i].TaskName[0]=='\0')
    {
        fl=2;
        break;
    }
}
if(fl==0)
{
    printf("Wrong ID is entered!");
    return;
}
if(fl==2)
{
    printf("Task is empty");
    return;
}
printf("Is the task completed? Input Y for Yes and N for No");
scanf(" %c",&ch);

if(ch=='N' || ch=='n')
{
 printf("the Task was not updated!");
 return;
}
else if(ch=='Y' || ch=='y')
{
    for(int i=0;i<count;i++)
    {
        if(Tasks[i].id==id)
        {
           strcpy(Tasks[i].status,"Completed!");
           printf("Tasks marked complete!");
           saveTasks();
           return;
        }
    }
}
else{
    printf("Wrong Input!");
    return;
}
}

int main(){
    
    int choice;
    loadTasks();
    while (1){
     printf("--------TO DO LIST-------");
     printf("1. Add a task\n");
     printf("2. View tasks\n");
     printf("3. Update Task\n");
     printf("4. Delete a task\n");
     printf("5. Exit\n");
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
         saveTasks();
         exit(0);
        break;
        default:
        printf("Wrong input");
     }
    }
   
}
