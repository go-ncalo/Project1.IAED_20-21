/* Goncalo Botelho Mateus, 99225*/
/* INCLUDES */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* DEFINES */

/* maximum numbers of characters (ver casos q tem de ser +1)*/
#define DESCMAX 50
#define USEACTMAX 21
#define TASKSMAX 10000
#define MAXACTIVITIES 10
#define MAXUSERS 50
#define TO_DO "TO DO"
#define IN_PROGRESS "IN PROGRESS"
#define DONE "DONE"
#define DUR_ERROR "invalid duration"
#define TASK_ERROR "too many tasks"
#define DESC_ERROR "duplicate description"
/* define dos erros, de todos os printf */

/* STRUCTURES */

struct activity{
    char act[USEACTMAX];
};

struct user
{
    char us[USEACTMAX];
};

struct task{
    int id, dur, start;
    char desc[DESCMAX];
    struct activity activ;
    struct user user;
};

struct Kanban{
    struct task tasks[TASKSMAX];
    struct activity act[MAXACTIVITIES];
    struct user users[MAXUSERS];
} system; /* main system */

/* GLOBAL VARIABLES */

int id_counter = 0, user_counter = 0, act_counter = 0;

/* FUNCTIONS PROTOTYPES */

void read_desc(char desc[]);
void command(int c);


/* MAIN */

int main()
{
    int c;

    system.tasks[0].id = 1;
    while ((c = getchar()) != 'q'){
        command(c);
    }

    return 0;
}

/* fazer funçao q inicializa sistema */

void read_desc(char desc[])
{
    int state = 0, i = 0; /* state: 0 - outside string, 1 - inside */
    char c;
    while ((c = getchar()) != '\n'){
        if(state == 0 && (c == ' ' || c == '\t')){
            continue;
        } 
        state = 1;
        desc[i] = c;
        i++;
    }
    desc[i] = '\0'; /* all string need to end with '\0' */
    return;
}

int command_t(int dur, char desc[]){
    int res, i;

    if (id_counter + 1 > TASKSMAX)
        printf("%s\n", TASK_ERROR);

    for (i = 0; i < id_counter; ++i){
        if (strcmp(system.tasks[i].desc, desc) != 0)
            printf("%s", DESC_ERROR);
    }

    if (dur < 0)
        printf("%s\n", DUR_ERROR);

    printf("%d", res);
    return 0;
}

void command(int c)
{
    int i = 0, duration, chr, idlst[TASKSMAX];
    char description[DESCMAX] /*,user[USEACTMAX], activity[USEACTMAX]*/;
    switch (c)
    {
    case 't':
        scanf("%d", &duration);
        read_desc(description);
        command_t(duration, description);
        break;
    
    case 'l':
        while ((chr = getchar()) != '\n'){
            scanf("%d", &idlst[i]);
            i++;
        }
        break;

    case 'n':
        printf("n");
        break;

    case 'u':
        printf("u");
        break;

    case 'm':
        printf("m");
        break;

    case 'd':
        printf("d");
        break;

    case 'a':
        printf("a");
        break;

    }
}