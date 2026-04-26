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
    printf("Enter Task's id");
    while(1){
    scanf("%d",&id);
        for(int i=0;i<count;i++)
        {
            if(id==Tasks[i].id)
            d=1;
        }
        if(d==1){
            printf("Id already in use , Enter another id");
            d=0;
        }
        else
        break;
    }
    Tasks[count].id=id;
    printf("Enter Task Name ");
    scanf(" %[^\n]", Tasks[count].TaskName);
    strncpy(Tasks[count].status, "Pending", sizeof(Tasks[count].status) - 1);
    Tasks[count].status[sizeof(Tasks[count].status) - 1] = '\0';
    count++;
    saveTasks();
    printf("Task added successfully!\n");
}

void saveTasks()
{
    FILE *fp = fopen("tasks.txt", "w");

    if (fp == NULL)
    {
        printf("Error: Could not open file for saving tasks!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (fprintf(fp, "%d\n", Tasks[i].id) < 0 ||
            fprintf(fp, "%s\n", Tasks[i].TaskName) < 0 ||
            fprintf(fp, "%s\n", Tasks[i].status) < 0)
        {
            printf("Error: Failed to write to file!\n");
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

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


int main()
{    
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
