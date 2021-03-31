/* INCLUDES */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* DEFINES */

/* maximum numbers of characters */
#define DESCMAX 50
#define USEACTMAX 20
#define TASKSMAX 10000

/* STRUCTURES */

typedef struct{
    int id, dur, start;
    char desc[DESCMAX], user[USEACTMAX], act[USEACTMAX]; 
} task;

/* FUNCTIONS PROTOTYPES */

void command(int c);

/* MAIN */

int main()
{
    int c;
    task system[TASKSMAX];

    while ((c = getchar()) != 'q'){
        command(c);
    }

    return 0;
}

void command(int c)
{
    switch (c)
    {
    case 't':
        /*function*/
        break;
    
    case 'l':
        /*function*/
        break;

    case 'n':
        /*function*/
        break;

    case 'u':
        /*function*/
        break;

    case 'm':
        /*function*/
        break;

    case 'd':
        /*function*/
        break;

    case 'a':
        /*function*/
        break;

    }
}