#ifndef TODOLIST_H
#define TODOLIST_H

struct ToDoList
{
    int id;
    char TaskName[100];
    char status[20]; 
};

extern struct ToDoList *Tasks;
extern int count;
extern int capacity;

void addTasks();
void viewTasks();
void updateTasks();
void deleteTasks();
void saveTasks();
void loadTasks();

#endif
