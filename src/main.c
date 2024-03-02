#include <stdio.h>
#include <stdlib.h>
#include <string.h>



enum month {january,february,march,april,may,june,july,august,september,october,november,december};

struct task
{
    char taskName[20];
    int startMonth;
    int endMonth;
    int numDependencies;
    int dependentTasks[9];
};

void functionEdit(struct task tasks[], int nTasks);
void test (struct task tasks[]);
void quit (struct task tasks[]);
void printFunction(struct task tasks[], int ntasks);

void functionEdit(struct task tasks[], int nTasks){
    char change[20];
    int taskToChange, found = 0;
    printf("Please enter the task name you want to change exactly\n" );
    scanf("%s", change);
    for(taskToChange = 0; taskToChange < nTasks; taskToChange++){
        if(strcmp(change, tasks[taskToChange].taskName) == 0){
            found = 1;
            printf("Enter the new task name (max 20 characters)\n");
            scanf("%s", &tasks[taskToChange].taskName[20]);

            do{
                printf("Enter start month:\n");
                fflush(stdout);
                scanf("%d", &tasks[taskToChange].startMonth);
                if(tasks[taskToChange].startMonth > 12 || tasks[taskToChange].startMonth < 1){
                    printf("number must be between 1 and 12\n");
                    fflush(stdout);
                }
            } while(tasks[taskToChange].startMonth > 12 || tasks[taskToChange].startMonth < 1);

            do{
                printf("Enter end month:\n");
                fflush(stdout);
                scanf("%d", &tasks[taskToChange].endMonth);
                if(tasks[taskToChange].endMonth > 12 || tasks[taskToChange].endMonth < 1 || tasks[taskToChange].startMonth > tasks[taskToChange].endMonth){
                    printf("number must be between 1 and 12\n");
                    fflush(stdout);
                }
            } while(tasks[taskToChange].endMonth > 12 || tasks[taskToChange].endMonth < 1 || tasks[taskToChange].endMonth < tasks[taskToChange].startMonth);

            printf("Enter number of dependencies:\n");
            scanf("%d", &tasks[taskToChange].numDependencies);

            if(tasks[taskToChange].numDependencies > nTasks - 1){
                printf("must be less than number of tasks\n");
                fflush(stdout);
                printf("Enter number of dependencies:\n");
                scanf("%d", &tasks[taskToChange].numDependencies);
            }

            for(int j = 0; j < tasks[taskToChange].numDependencies; j++){
                printf("Enter dependency:\n");
                scanf("%d", &tasks[taskToChange].dependentTasks[j]);
                if(tasks[taskToChange].dependentTasks[j] > nTasks){
                    printf("must be less than number of tasks\n");
                    fflush(stdout);
                    printf("Enter dependency:\n");
                    scanf("%d", &tasks[taskToChange].dependentTasks[j]);
                }
            }

        }
    }
    if (!found){
        printf("Task not found");
    }
}


void test (struct task tasks[]){printf("test\n");}
void quit (struct task tasks[]){printf("quit\n");}



int main(void){
    int nTasks;

    /* Force the user to enter a valid number
     * of tasks */
    do{
        printf("enter number of tasks:\n");
        fflush(stdout);
        scanf("%d", &nTasks);
        if(nTasks > 10 || nTasks < 1)
            printf("Please enter at least 1 task and at most 10 tasks\n");
    } while(nTasks > 10 || nTasks < 1);

    struct task tasks[nTasks];  /* Array of tasks Suggestion creating a blank struct such as in lecture 11 page 10: struct task
    							blank = "", 0, 0 , 0 , 0 */

    /*Create a blank task*/
    struct task blank = { " ", 0 , 0, 0, 0};

    /*Initialise all the tasks with blank*/
    for(int i = 0; i < nTasks; i++){
    	tasks[i] = blank;
        }

    for(int i = 0; i < nTasks; i++){
        /*To enforce the user of not entering more than 20 characters and avoid a security flaw
         * is trickier and this is what the last lecture was about maybe we could add a to do
         * TODO: Ensuring the user does not exceed 20 characters to avoid a security breach */

        printf("Enter the task name (max 20 characters)\n");
        scanf("%s", tasks[i].taskName);

        /*Force the user to enter a valid starting month*/

        do{
            printf("Enter start month:\n");
            fflush(stdout);
            scanf("%d", &tasks[i].startMonth);
            if(tasks[i].startMonth > 12 || tasks[i].startMonth < 1){
                printf("number must be between 1 and 12\n");
                fflush(stdout);
            }
        } while(tasks[i].startMonth > 12 || tasks[i].startMonth < 1);

        /*Force the user to enter a valid ending month*/

        do{
            printf("Enter end month:\n");
            fflush(stdout);
            scanf("%d", &tasks[i].endMonth);
            if(tasks[i].endMonth > 12 || tasks[i].endMonth < 1){
                printf("number must be between 1 and 12\n");
                fflush(stdout);
            }
        } while(tasks[i].endMonth > 12 || tasks[i].endMonth < 1 || tasks[i].endMonth < tasks[i].startMonth); // had start month instead of end month and added last case

        printf("Enter number of dependencies:\n");
        scanf("%d", &tasks[i].numDependencies);

        if(tasks[i].numDependencies > nTasks - 1){
            printf("must be less than number of tasks\n");
            fflush(stdout);
            printf("Enter number of dependencies:\n");
            scanf("%d", &tasks[i].numDependencies);
        }

        for(int j = 0; j < tasks[i].numDependencies; j++){
            printf("Enter dependency:\n");
            scanf("%d", &tasks[i].dependentTasks[j]);
            if(tasks[i].dependentTasks[j] > nTasks){
                printf("must be less than number of tasks\n");
                fflush(stdout);
                printf("Enter dependency:\n");
                scanf("%d", &tasks[i].dependentTasks[j]);
            }
        }
    }
    printFunction(tasks, nTasks);
    functionEdit(&tasks[nTasks], nTasks);

}
void printFunction(struct task tasks[], int nTasks){
	for(int i = 0; i < nTasks;i++){
	    	printf("%-10s %-4d %-4d %-2d \n", tasks[i].taskName, tasks[i].startMonth, tasks[i].endMonth, tasks[i].numDependencies);
	    }
}
