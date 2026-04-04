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
    printf("\nID\tTask Name\t\tStatus\n");
    printf("--------------------------------------------\n");
    for(int i=0;i<count;i++){
        printf("%d\t%s\t\t%s\n", Tasks[i].id, Tasks[i].TaskName, Tasks[i].status);
    }
    printf("\n");
}

void updateTasks()
{
    char ch;
    int id,fl=0,choice=0;
    printf("\nEnter the Task ID that needs to be updated: ");
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
        printf("\nWrong ID is entered!");
        return;
    }
    if(fl==2)
    {
        printf("\nTask is empty");
        return;
    }
    printf("\nPress 1 to change the name and 2 to change the status: ");
    scanf("%d",&choice);
    if(choice==1)
    {
        getchar();
        printf("\nDo you want to change the task name? Press Y/y for yes or N/n for no: ");
        scanf("%c",&ch);

        if(ch=='N' || ch=='n')
        {
            printf("\nThe Task name was not updated!");
            return;
        }
        else if(ch=='Y' || ch=='y')
        {
            for(int i=0;i<count;i++)
            {
                if(Tasks[i].id==id)
                {
                    getchar();
                    char temp[100];
                    printf("Enter new Task name: ");
                    scanf("%[^\n]", temp);
                    strcpy(Tasks[i].TaskName, temp);
                    printf("\nTask name changed!");
                    break;
                }
            }
        }
        else
        {
            printf("\nWrong Input!");
            return;
        }
    }
    else if(choice==2)
    {
        printf("\nIs the task completed? Press Y/y for Yes and N/n for No: ");
        scanf(" %c",&ch);

        if(ch=='N' || ch=='n')
        {
            printf("\nThe Task status was not updated!");
            return;
        }
        else if(ch=='Y' || ch=='y')
        {
            for(int i=0;i<count;i++)
            {
                if(Tasks[i].id==id)
                {
                    strcpy(Tasks[i].status,"Completed!");
                    printf("\nTask marked complete!");
                    break;
                }
            }
        }
        else
        {
            printf("\nWrong Input!");
            return;
        }
    }
    else
    {
        printf("\nWrong choice! Please enter 1 or 2.");
        return;
    }
}


int main()
{    
    int choice;
    loadTasks();
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
         saveTasks();
         exit(0);
        break;
        default:
        printf("Wrong input");
     }
    }
}
