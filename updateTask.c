#include <stdio.h>
#include <string.h>
#include "ToDoList.h"

void updateTasks()
{
    char ch;
    int id,fl=0,choice=0;
    printf("\nEnter the Task ID that needs to be updated: ");
    scanf("%d",&id);
    for(int i=0;i<count;i++)
    {
        if(Tasks[i].id==id && Tasks[i].TaskName[0]!='\0'){
            fl=1;
            break;
        }
        if(Tasks[i].id==id && Tasks[i].TaskName[0]=='\0'){
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
        printf("\nDo you want to change the task name? Press Y/y for yes or N/n for no: ");
        scanf(" %c",&ch);

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
                    char temp[100];
                    printf("Enter new Task name: ");
                    scanf(" %[^\n]", temp);
                    strncpy(Tasks[i].TaskName, temp, sizeof(Tasks[i].TaskName) - 1);
                    Tasks[i].TaskName[sizeof(Tasks[i].TaskName) - 1] = '\0';
                    printf("\nTask name changed!");
                    saveTasks();
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
                    strncpy(Tasks[i].status, "Completed!", sizeof(Tasks[i].status) - 1);
                    Tasks[i].status[sizeof(Tasks[i].status) - 1] = '\0';
                    printf("\nTask marked complete!");
                    saveTasks();
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
