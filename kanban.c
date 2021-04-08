/* Goncalo Botelho Mateus, 99225*/
/* INCLUDES */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* DEFINES */

/* maximum numbers of characters (ver casos q tem de ser +1)*/
#define DESCMAX 51
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
#define USEREXIST_ERROR "user already exists"
#define USERCOUNT_ERROR "too many users"
#define ACTEXIST_ERROR "duplicate activity"
#define ACTDESC_ERROR "invalid description"
#define ACTCOUNT_ERROR "too many activities"
#define TASK "task"
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
    struct activity activ[MAXACTIVITIES];
    struct user users[MAXUSERS];
} system; /* main system */

/* GLOBAL VARIABLES */

int id_counter = 0, user_counter = 0, act_counter = 3, system_time = 0;

/* FUNCTIONS PROTOTYPES */

void initialize_system();
void read(char string[]);
void command(int c);
void command_t(int dur, char desc[]);
int compare(char desc[]);
void command_l_numbers();
void command_l();
void command_n();
void command_u_users(char user[]);
void command_u();
void command_a_activities(char activity[]);
void command_a();

/* MAIN */

int main()
{
    int c;

    initialize_system();

/* when the input is 'q' the program ends */
    while ((c = getchar()) != 'q'){ 
        command(c);
    }

    return 0;
}

void initialize_system()
{
    strcpy(system.activ[0].act, TO_DO);
    strcpy(system.activ[1].act, IN_PROGRESS);
    strcpy(system.activ[2].act, DONE);
}

void read(char string[])
{
    int state = 0, i = 0; /* state: 0 - outside string, 1 - inside */
    char c;

    while ((c = getchar()) != '\n'){
        /* ignores the white spaces in the beggining */
        if(state == 0 && (isspace(c) != 0)){
            continue;
        } 
        state = 1;
        string[i] = c;
        i++;
    }
    string[i] = '\0'; /* all string need to end with '\0' */
}

void command(int c)
{
    int duration, chr;
    char description[DESCMAX], user[USEACTMAX], activity[USEACTMAX];

    switch (c)
    {
    case 't':
        scanf("%d", &duration);
        read(description);
        command_t(duration, description);
        break;
    
    case 'l':
        if ((chr = getchar()) == '\n'){
            command_l(); /* falta fazer */
        } else{
            command_l_numbers();
        }
        break;

    case 'n':
        command_n();
        break;

    case 'u': /*verificar o pq de estar a aceitar +20 caracteres */
        if((chr = getchar()) == '\n'){
            command_u();
        } else{
            command_u_users(user);
        }
        break;

    case 'm':
        printf("m");
        break;

    case 'd':
        printf("d");
        break;

    case 'a':
        if((chr = getchar()) == '\n'){
            command_a();
        } else{
            command_a_activities(activity);
        }
        break;

    }
}

int compare(char desc[])
{
    int i;
    for (i = 0; i < id_counter; ++i){
        if (strcmp(system.tasks[i].desc, desc) == 0)
            return 1;
    }
    return 0;
}

void command_t(int dur, char desc[]){
    if (id_counter + 1 > TASKSMAX){
        printf("%s\n", TASK_ERROR);
    } else if (compare(desc)){
        printf("%s\n", DESC_ERROR);
    } else if (dur < 0){
        printf("%s\n", DUR_ERROR);
    } else{
    system.tasks[id_counter].id = id_counter + 1;
    system.tasks[id_counter].dur = dur;
    system.tasks[id_counter].start = system_time;
    strcpy(system.tasks[id_counter].desc, desc);
    system.tasks[id_counter].activ = system.activ[0];
    ++id_counter;

    printf("%s %i\n", TASK, id_counter);
    return;
    }
}

void command_l(){
    printf("1\n");
}

void command_l_numbers(){
    int chr, i;
    while((chr) != '\n'){
        scanf("%i", &i);
        chr = getchar(); /* the getchar is inside the while so it doesnt
                            skip the first number */
        if (i <= id_counter){
            printf("%i %s #%i %s\n", system.tasks[i - 1].id, \
            system.tasks[i - 1].activ.act, system.tasks[i - 1].dur, \
            system.tasks[i - 1].desc);
        } else{
            printf("%i: no such task\n", i);
        }
    }
    return;
}

void command_n(){
    int time;
    scanf("%i", &time);
    if (time != 0 && time >0){
        system_time += time;
    } else if(time < 0){
        printf("invalid time\n");
        return;
    }
    printf("%i\n", system_time);
}

void command_u_users(char user[]){
    int i;
    
    read(user);

    for(i = 0; i < user_counter; ++i){
        if(strcmp(system.users[i].us, user) == 0){
            printf("%s\n", USEREXIST_ERROR);
            return;
        }
    }
    if (user_counter + 1 > MAXUSERS){
        printf("%s\n", USERCOUNT_ERROR);
        return;
    }
    strcpy(system.users[user_counter].us, user);
    ++user_counter;
}

void command_u(){
    int i;
    for (i = 0; i < user_counter; ++i){
        printf("%s\n", system.users[i].us);
    }
}

void command_a_activities(char activity[]){
    int i, size;
    read(activity);
    size = strlen(activity);
    for (i = 0; i < act_counter; ++i){
        if(strcmp(system.activ[i].act, activity) == 0){
            printf("%s\n", ACTEXIST_ERROR);
            return;
        }
    }
    for (i = 0; i < size; ++i){
        if(activity[i] >= 'a' && activity[i] <= 'z'){
            printf("%s\n", ACTDESC_ERROR);
            return;
        }
        
    }
    if (act_counter + 1 > MAXACTIVITIES){
        printf("%s\n", ACTCOUNT_ERROR);
        return;
    }
    strcpy(system.activ[act_counter].act, activity);
    ++act_counter;
}

void command_a(){
    int i;
    for (i= 0; i < act_counter; ++i)
        printf("%s\n", system.activ[i].act);
}