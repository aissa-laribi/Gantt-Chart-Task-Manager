#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


enum month {january,february,march,april,may,june,july,august,september,october,november,december, dependencies}; // {0,1,2,3,4,5,6,7,8,9,10,11}


struct task
{
    char taskName[20];
    int startMonth;
    int endMonth;
    int numDependencies;
    int dependentTasks[9];
};
/* Structs to define points on x-axis and y-axis*/
struct point{
	int x;
	int y;
};
/*This struct define two points to be joined*/
struct line{
	struct point p1;
	struct point p2;
};

void functionEdit(struct task tasks[], int nTasks);
bool functionTest (struct task tasks[], int nTasks);
bool hasCircularDependency(struct task tasks[], int nTasks, int taskIndex, bool visited[]);
void printMonths();
void printFunction(struct task tasks[], int ntasks);

bool functionTest (struct task tasks[], int nTasks){
    bool visited[nTasks]; //array to track which tasks have been checked
    // initialise all elements in array to false as none have been visited
    for (int i = 0; i < nTasks; ++i) {
        visited[i] = false;
    }

    for (int i = 0; i < nTasks; ++i) {
        //if the ith task hasnt been visited/checked
        if (!visited[i]) {
            //we then use another function to check if this task has a circular dependancy
            if (hasCircularDependency(tasks, nTasks, i, visited)) {
                //it takes in i as the task index and visited, the array to tell us which task has been visited
                return false; //return false if circular dependency found
            }
        }
    }
    return true; // true if no circular dependancy found
}

bool hasCircularDependency(struct task tasks[], int nTasks, int taskIndex, bool visited[]){
    visited[taskIndex] = true;
    for (int i = 0; i < tasks[taskIndex].numDependencies; ++i) {
        int dependentTask = tasks[taskIndex].dependentTasks[i];
        if (!visited[dependentTask]) {
            if (hasCircularDependency(tasks, nTasks, dependentTask, visited)) {
                return true;
            }
        } else if (visited[dependentTask]) {
            return true; // Circular dependency found
        }
    }
    visited[taskIndex] = false;
    return false;
}



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
    /* TODO: Ensuring if the user enters characters that it woill not loop indefinitely */

    struct task tasks[nTasks];  /* Array of tasks Suggestion creating a blank struct such as in lecture 11 page 10: struct task
    							blank = "", 0, 0 , 0 , 0 */

    /*Create a blank task*/
    struct task blank = { " ", 0 , 0, 0, {0}};

    /*Initialize all the tasks with blank*/
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
    int userChoice;
    printf("enter 1 to edit the Gantt, 2 to test if your gant is possible, 3 to quit:\n");
    scanf("%d", &userChoice);
    switch (userChoice) {
        case 1:
            functionEdit(tasks, nTasks);
            break;
        case 2:
            if(functionTest(tasks, nTasks)){
                printf("no circular dependencies found\n");
            }
            else if(!functionTest(tasks, nTasks)){
                printf("Gantt not possible due to circular dependency\n");
            }
            break;
        case 3:
            printf("leaving programme\n");
            return 0;
        default:
            break;
    }
    printMonths();
    printFunction(tasks, nTasks);


}
void printMonths(){
	enum month today;
	today = january;

	/*Length of line*/
	int segment = 200;

	/*Print 200 "_" as a continuous line*/
	for(int i = 0; i < segment; i++){
		printf("_");
		}
	puts("");
	printf("%-21s", " ");
	for(today; today < dependencies + 1; today++){

	switch(today){
					case(january):
						printf("%-10s","|January");
						break;
					case(february):
						printf("%-10s","|February");
						break;
					case(march):
						printf("%-10s","|March");
						break;
					case(april):
						printf("%-10s","|April");
						break;
					case(may):
						printf("%-10s","|May");
						break;
			        case(june):
						printf("%-10s","|June");
						break;
			        case(july):
						printf("%-10s","|July");
						break;
			        case(august):
						printf("%-10s","|August");
						break;
			        case(september):
						printf("%-10s","|September");
						break;
			        case(october):
						printf("%-10s","|October");
						break;
			        case(november):
						printf("%-10s","|November");
						break;
			         case(december):
						printf("%-10s","|December");
						break;
			         case(dependencies):
			        		 printf("%-10s","|Dependencies");
			         		 break;

					default:
						break;

				}

	}
	puts("");


}
void printFunction(struct task tasks[], int nTasks){
		/*Length of line*/
		int segment = 200;
		enum month today;

		for(int i = 0; i < (int) segment; i++){
					printf("-");
				}



		for(int i = 0; i < nTasks; i++){
			printf("\n");
			printf("%-21s", tasks[i].taskName);
			for(today = january; today < dependencies + 1; today++){
				if(today >= tasks[i].startMonth && today <= tasks[i].endMonth){
					printf( "%-10s","|  XXX");
				} else{
					printf("%-10s","|");
				}
			}
			puts("");
			for(int i = 0; i < (int) segment; i++){
				printf("-");
			}
		/*for(int i = 0; i < nTasks; i++){
                printf("\n");
                printf("%-21s", tasks[i].taskName);
                for(today = january; today < dependencies + 1; today++){
                    if (tasks[i].startMonth - 1 == today){
                        printf("%-10s","|   XXX");
                        while(tasks[i].startMonth != tasks[i].endMonth){
                        printf("%-10s","|   XXX");
                        today++;
                        tasks[i].startMonth++;
                        }
                    }
                    else {printf("%-10s","|");}
                }
                puts("");
                for(int i = 0; i < (int) segment; i++){
                                    printf("-");
                                }*/


			/*TO COMPLETE: Counting the underscores will help to print the "|"
			 * I am thinking about a blank struct for that as well
			 */
		}
}
