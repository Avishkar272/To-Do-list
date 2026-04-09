#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ToDoList
{
    int id;
    char TaskName[100];
    char status[20]; 
};
struct ToDoList *Tasks=NULL;
int count=0;
int capacity=2;

void addTasks();
void viewTasks();
void updateTasks();
void deleteTasks();
void saveTasks();
void loadTasks();

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

void addTasks(){
    if(count == capacity){
        capacity *= 2;
        struct ToDoList *temp = realloc(Tasks, capacity * sizeof(struct ToDoList));
        if(temp == NULL){
            printf("Memory reallocation failed\n");
            return;
        }
        Tasks = temp;
    }
    Tasks[count].id=count+1;
    printf("Enter Task Name ");
    scanf(" %[^\n]", Tasks[count].TaskName);
    strcpy(Tasks[count].status, "Pending");
    count++;
    printf("Task added successfully!\n");
}

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
    Tasks = malloc(capacity * sizeof(struct ToDoList));
    if (Tasks == NULL) { 
        printf("Memory allocation failed\n"); exit(1);
    }
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
        free(Tasks);
        exit(0);
        break;
        default:
        printf("Wrong input");
     }
    }
}
