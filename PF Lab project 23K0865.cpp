#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_LENGTH 100

char tasks[MAX_TASKS][MAX_TASK_LENGTH];
int taskCount = 0;

void addTask(char task[]) {
    strcpy(tasks[taskCount++], task);
}

void viewTasks() {
    for(int i = 0; i < taskCount; i++) {
        printf("%d. %s\n", i+1, tasks[i]);
    }
}

void deleteTask(int taskNumber) {
    for(int i = taskNumber; i < taskCount; i++) {
        strcpy(tasks[i], tasks[i+1]);
    }
    taskCount--;
}

void saveTasks() {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    for(int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\n", tasks[i]);
    }
    fclose(file);
}

void loadTasks() {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }
    char line[MAX_TASK_LENGTH];
    taskCount = 0;
    while(fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        strcpy(tasks[taskCount++], line);
    }
    fclose(file);
}

int main() {
    loadTasks();
    while(1) {
        printf("1. Add Task\n2. View Tasks\n3. Delete Task\n4. Save and Exit\n");
        int option;
        scanf("%d", &option);
        switch(option) {
            case 1: {
                printf("Enter task: ");
                char task[MAX_TASK_LENGTH];
                scanf(" %[^\n]", task);
                addTask(task);
                break;
            }
            case 2:
                viewTasks();
                break;
            case 3: {
                printf("Enter task number to delete: ");
                int taskNumber;
                scanf("%d", &taskNumber);
                deleteTask(taskNumber-1);
                break;
            }
            case 4:
                saveTasks();
                return 0;
        }
    }
}
