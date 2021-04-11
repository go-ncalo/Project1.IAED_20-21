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
#define NOTASK_ERROR "no such task"
#define TASKSTARTED_ERROR "task already started"
#define USER_ERROR "no such user"
#define ACT_ERROR "no such activity"

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

/* FUNCTIONS PROTOTYPES */

void initialize_system();
void read(char string[]);
void read_word(char string[]);
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
void sort_array();
void index(int array[]);
void command_m();
int no_task(int id);
int started_task(int id, char activity[]);
int no_user(char user[]);
int no_activity(char activity[]);

/* GLOBAL VARIABLES */

int id_counter = 0, user_counter = 0, act_counter = 3, system_time = 0;

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

void read_word(char string[]){
    {
    int state = 0, i = 0; /* state: 0 - outside string, 1 - inside */
    char c;

    while (!isspace(c = getchar())){
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
            command_l();
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
        command_m();
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
    } else if (dur <= 0){
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
    int i;
    int index_array[TASKSMAX];
    index(index_array);
    sort_array(index_array);
    for (i= 0; i < id_counter; ++i)
        printf("%i %s #%i %s\n", system.tasks[index_array[i] - 1].id, \
            system.tasks[index_array[i] - 1].activ.act, system.tasks[index_array[i] - 1].dur, \
            system.tasks[index_array[i] - 1].desc);
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

void index(int array[]){
    int i;
    for (i = 0; i < id_counter; ++i){
        array[i] = i + 1;
    }
}

void sort_array(int array[]){
    int i, j, k;
    for(i = 0; i < id_counter - 1; ++i){
        for (j = i + 1; j < id_counter; ++j){
            if(strcmp(system.tasks[i].desc, system.tasks[j].desc) > 0){
                
                k = array[i];
                array[i] = array[j];
                array[j] = k;

            }
        }
    }
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

void command_m(){
    int id;
    char user[USEACTMAX], activity[USEACTMAX];
    scanf("%i", &id);
    getchar(); /* used to read the space between the id and the user */
    read_word(user);
    read(activity);
    if (no_task(id)){
        printf("%s\n", NOTASK_ERROR);
        return;
    }
    if (started_task(id, activity)){
        printf("%s\n", TASKSTARTED_ERROR);
        return;
    }
    if (no_user(user)){
        printf("%s\n", USER_ERROR);
        return;
    }
    if (no_activity(activity)){
        printf("%s\n", ACT_ERROR);
        return;
    }
    if (strcmp(system.tasks[id - 1].activ.act, activity) == 0){
        strcpy(system.tasks[id - 1].user.us, user);
        return;
    } else if(strcmp(activity, DONE) == 0){
        int duration, slack;
        duration = system_time - system.tasks[id - 1].start;
        slack = duration - system.tasks[id - 1].dur;
        printf("duration=%i slack=%i\n", duration, slack);
    
    } else{
        strcpy(system.tasks[id - 1].user.us, user);
        strcpy(system.tasks[id - 1].activ.act, activity);
        system.tasks[id - 1].start = system_time;
    }
}

int no_task(int id){
    if (id > id_counter){
        return 1;
    }
    return 0;
}

int started_task(int id, char activity[]){
    if((strcmp(system.tasks[id - 1].activ.act, TO_DO) != 0) && ((strcmp(activity, TO_DO)) == 0)){
        return 1;
    }
    return 0;
}

int no_user(char user[]){
    int i;
    for (i = 0; i < user_counter; ++i){
        if (strcmp(system.users[i].us, user) == 0)
            return 0;
    }
    return 1;
}

int no_activity(char activity[]){
    int i;
    for (i = 0; i < act_counter; ++i){
        if (strcmp(system.activ[i].act, activity) == 0)
            return 0;
    }
    return 1;
}