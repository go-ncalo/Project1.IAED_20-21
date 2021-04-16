/* Goncalo Botelho Mateus, 99225*/
/* INCLUDES */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* DEFINES */

/* maximum numbers of characters*/
#define DESCMAX 51
#define USEACTMAX 21

/* maximum numbers of tasks/users/activities */
#define MAXTASKS 10000
#define MAXACTIVITIES 10
#define MAXUSERS 50

/* activities */
#define TO_DO "TO DO"
#define IN_PROGRESS "IN PROGRESS"
#define DONE "DONE"

/* errors */
#define DUR_ERROR "invalid duration"
#define TASK_ERROR "too many tasks"
#define DESC_ERROR "duplicate description"
#define TIME_ERROR "invalid time"
#define USEREXIST_ERROR "user already exists"
#define USERCOUNT_ERROR "too many users"
#define ACTEXIST_ERROR "duplicate activity"
#define ACTDESC_ERROR "invalid description"
#define ACTCOUNT_ERROR "too many activities"
#define NOTASK_ERROR "no such task"
#define TASKSTARTED_ERROR "task already started"
#define USER_ERROR "no such user"
#define ACT_ERROR "no such activity"

/* general */
#define TASK "task"

/* implementation for quick sort */
#define key(A) (A)
#define less(A, B) (strcmp(system.tasks[A].desc, system.tasks[B].desc) < 0)
#define exch(A, B) { Item t = A; A = B; B = t; }

/* STRUCTURES */

struct activity{
    char act[USEACTMAX];
};

struct user{
    char us[USEACTMAX];
};

struct task{
    int id, dur, start;
    char desc[DESCMAX];
    struct activity activ;
    struct user user;
};

struct Kanban{
    struct task tasks[MAXTASKS];
    struct activity activ[MAXACTIVITIES];
    struct user users[MAXUSERS];
} system; /* main system */

typedef int Item;

/* FUNCTIONS PROTOTYPES */

void initialize_system();
void read(char string[]);
void read_word(char string[]);
void command(int c);
void command_t(char desc[]);
int compare(char desc[]);
void command_l_numbers();
void command_l();
void command_n();
void command_u_users(char user[]);
void command_u();
void command_a_activities(char activity[]);
int activity_exists(char activity[]);
int description_error(int size, char activity[]);
void command_a();
void sort_array();
void index(int array[]);
void command_m();
void move(int id, char user[], char activity[]);
void move_to_done(int id, char user[], char activity[]);
int no_task(int id);
int started_task(int id, char activity[]);
int no_user(char user[]);
int no_activity(char activity[]);
void command_d();
int index_act(int array[], char activity[]);
void quicksort(int a[], int left, int right);
int partition(int a[], int left, int right);

/* GLOBAL VARIABLES */

int id_counter = 0, user_counter = 0, act_counter = 3, system_time = 0;

/* MAIN */

int main(){
    int c;

    initialize_system();

/* when the input is 'q' the program ends */
    while ((c = getchar()) != 'q'){ 
        command(c);
    }

    return 0;
}

/* FUNCTIONS */

/* initialize_system: starts the system with the three initial activites */
void initialize_system(){
    strcpy(system.activ[0].act, TO_DO);
    strcpy(system.activ[1].act, IN_PROGRESS);
    strcpy(system.activ[2].act, DONE);
}

/* read: reads and stores in a string one or more words given in the input */
void read(char string[]){
    int state = 0, i = 0; /* state: 0 - outside string, 1 - inside */
    char c;

    while ((c = getchar()) != '\n'){
        /* ignores the white spaces in the beggining */
        if (state == 0 && (isspace(c) != 0)){
            continue;
        } 

        state = 1;
        string[i] = c;
        i++;
    }

    string[i] = '\0'; /* all strings need to end with '\0' */
}

/* read_word: reads and stores in a string only one word given in the input */
void read_word(char string[]){
    int i = 0;
    char c;

    while (!isspace(c = getchar())){
        string[i] = c;
        i++;
    }

    string[i] = '\0'; /* all strings need to end with '\0' */
}

/* command: function that deals with the command given by the user */
void command(int c){
    int chr;
    char description[DESCMAX], user[USEACTMAX], activity[USEACTMAX];

    switch (c)
    {
    case 't':
        command_t(description);
        break;
    
    case 'l':
    /*checks if were given arguments or not */
        if ((chr = getchar()) == '\n'){
            command_l();
        } else{
            command_l_numbers();
        }
        break;

    case 'n':
        command_n();
        break;

    case 'u':
    /*checks if were given arguments or not */
        if ((chr = getchar()) == '\n'){
            command_u();
        } else{
            command_u_users(user);
        }
        break;

    case 'm':
        command_m();
        break;

    case 'd':
        command_d();
        break;

    case 'a':
    /*checks if were given arguments or not */
        if ((chr = getchar()) == '\n'){
            command_a();
        } else{
            command_a_activities(activity);
        }
        break;
    }
}

/* compare: auxiliary function for command t error, that check if there
is a task with the same description */
int compare(char desc[]){
    int i;

    for (i = 0; i < id_counter; ++i){
        if (!strcmp(system.tasks[i].desc, desc))
            return 1;
    }

    return 0;
}

/* command_t: adds a new task to the system */
void command_t(char desc[]){
    int dur;

    scanf("%i", &dur);
    read(desc);

    if (id_counter + 1 > MAXTASKS){
        printf("%s\n", TASK_ERROR);
    } else if (compare(desc)){
        printf("%s\n", DESC_ERROR);
    } else if (dur <= 0){
        printf("%s\n", DUR_ERROR);
    } else{
        /* inital setup of the new task */
    system.tasks[id_counter].id = id_counter + 1;
    system.tasks[id_counter].dur = dur;
    system.tasks[id_counter].start = 0;
    strcpy(system.tasks[id_counter].desc, desc);
    system.tasks[id_counter].activ = system.activ[0]; /* activity 
                                                        TO DO */
    ++id_counter;

    printf("%s %i\n", TASK, id_counter);
    return;
    }
}

/* command_l: lists all the tasks sorted by description */
void command_l(){
    int i;
    int index_array[MAXTASKS];

    index(index_array);
    /* sort by description */
    quicksort(index_array, 0, id_counter - 1);

    for (i= 0; i < id_counter; ++i)
        printf("%i %s #%i %s\n", system.tasks[index_array[i]].id, \
            system.tasks[index_array[i]].activ.act, \
            system.tasks[index_array[i]].dur, \
            system.tasks[index_array[i]].desc);
}

/* command_l_numbers: lists the tasks with the ID's given by the user */
void command_l_numbers(){
    int chr, i;

    while ((chr) != '\n'){
        scanf("%i", &i);
        chr = getchar(); /* the getchar is inside the while so it doesnt
                            skip the first number */
        
        if (i <= 0 || i > id_counter){
            printf("%i: no such task\n", i);
        } else if (i <= id_counter){
            printf("%i %s #%i %s\n", system.tasks[i - 1].id, \
            system.tasks[i - 1].activ.act, system.tasks[i - 1].dur, \
            system.tasks[i - 1].desc);
        }
    }

    return;
}

/* index: stores in an array the id's of all the tasks in the system */
void index(int array[]){
    int i;

    for (i = 0; i < id_counter; ++i){
        array[i] = i;
    }
}

/* command_n: function that progresses the time of the system */
void command_n(){
    int time;

    scanf("%i", &time);

    if (time > 0){
        system_time += time;
    } else if (time == 0){
        printf("%i\n", system_time);
        return;
    } else if (time < 0){
        printf("%s\n", TIME_ERROR);
        return;
    }

    printf("%i\n", system_time);
}

/* command_u_users: creates a new user with the name given in the input */
void command_u_users(char user[]){
    int i;
    
    read(user);

    for (i = 0; i < user_counter; ++i){
        if (!strcmp(system.users[i].us, user)){
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

/* command_u: lists all the users present in the system */
void command_u(){
    int i;

    for (i = 0; i < user_counter; ++i){
        printf("%s\n", system.users[i].us);
    }
}

/* command_a_activites: adds a new activity to the system */
void command_a_activities(char activity[]){
    int size;

    read(activity);
    size = strlen(activity);

    if (activity_exists(activity)){
        printf("%s\n", ACTEXIST_ERROR);
        return;
    } else if (description_error(size, activity)){
        printf("%s\n", ACTDESC_ERROR);
        return;
    } else if (act_counter + 1 > MAXACTIVITIES){
        printf("%s\n", ACTCOUNT_ERROR);
        return;
    }

    strcpy(system.activ[act_counter].act, activity);
    ++act_counter;
}

/* activity_exists: auxiliary function for command a error, that checks if
there is an activity with the same description of the one they are 
trying to add*/
int activity_exists(char activity[]){
    int i;
    for (i = 0; i < act_counter; ++i){
        if (!strcmp(system.activ[i].act, activity))
            return 1;
    }
    return 0;
}

/* description_error: auxiliary function for command a error, that checks if
the description given is valid or not*/
int description_error(int size, char activity[]){
    int i;
    for (i = 0; i < size; ++i){
        /* checks if description has lower case letters */
        if (activity[i] >= 'a' && activity[i] <= 'z')
            return 1;
    }
    return 0;
}

/* command_a: lists all the activities present in the system */
void command_a(){
    int i;

    for (i= 0; i < act_counter; ++i)
        printf("%s\n", system.activ[i].act);
}

/* command_m: moves one task from an activity to other */
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
    } else if (started_task(id, activity)){
        printf("%s\n", TASKSTARTED_ERROR);
        return;
    } else if (no_user(user)){
        printf("%s\n", USER_ERROR);
        return;
    } else if (no_activity(activity)){
        printf("%s\n", ACT_ERROR);
        return;
    }
    /* if they move a task for the activity it already is in, it updates
    the user */
    if (!strcmp(system.tasks[id - 1].activ.act, activity)){
        strcpy(system.tasks[id - 1].user.us, user);
    } else if (!strcmp(activity, DONE)){
        move_to_done(id, user, activity);
    /* if the tasks they want to move is in the activity TO DO, it gives a 
    start time to that task */
    } else if (!strcmp(system.tasks[id - 1].activ.act, TO_DO)){
        move(id, user, activity);
        system.tasks[id - 1].start = system_time;
    } else{
        move(id, user, activity);
    }
}

/* move: updates the user and the activity of a task after it's moved*/
void move(int id, char user[], char activity[]){
    strcpy(system.tasks[id - 1].user.us, user);
    strcpy(system.tasks[id - 1].activ.act, activity);
}

/* move_to_done: calculates the duration and slack of the task*/
void move_to_done(int id, char user[], char activity[]){
    int duration, slack;

    /* if an activity moves from TO DO -> DONE their duration is always 0
    so this checks if the task is in the activity TO DO */
    if (!strcmp(system.tasks[id - 1].activ.act, TO_DO)){
        duration = 0;
        system.tasks[id - 1].start = system_time;
    } else{
        duration = system_time - system.tasks[id - 1].start;
    }

    move(id, user, activity);
    
    slack = duration - system.tasks[id - 1].dur;

    printf("duration=%i slack=%i\n", duration, slack);
}

/* no_task: auxiliary function for command m error, that check if the task
exists in the system */
int no_task(int id){
    if (id > id_counter || id <= 0){
        return 1;
    }
    return 0;
}

/* started_task: auxiliary function for command m error, that check if they
are trying to move a task back to TO DO */
int started_task(int id, char activity[]){
    if ((strcmp(system.tasks[id - 1].activ.act, TO_DO)) && \
    ((!strcmp(activity, TO_DO)))){
        return 1;
    }
    return 0;
}

/* no_user: auxiliary function for command m error, that check if the user
exists in the system */
int no_user(char user[]){
    int i;

    for (i = 0; i < user_counter; ++i){
        if (!strcmp(system.users[i].us, user))
            return 0;
    }
    return 1;
}

/* no_activity: auxiliary function for command m/d error, that check if the
activity exists in the system */
int no_activity(char activity[]){
    int i;

    for (i = 0; i < act_counter; ++i){
        if (!strcmp(system.activ[i].act, activity))
            return 0;
    }
    return 1;
}

/* command_d: lists all the tasks in an activity */
void command_d(){
    int i, j, k, right, index_array[MAXTASKS];
    char activity[USEACTMAX];

    read(activity);
    i = index_act(index_array, activity); /* size of the index_array */

    if (no_activity(activity)){
        printf("%s\n", ACT_ERROR);
        return;
    }
    /* if two tasks have the same start time it sorts by description */
    for (j = 0; j < i; ++j){
        for (k = j; k <= i; ++k)
            if (system.tasks[index_array[j]].start == \
                system.tasks[index_array[k]].start){
                right = k;
            }
        quicksort(index_array, j, right);
    }
    for (j = 0; j <= i; ++j){
        printf("%i %i %s\n", system.tasks[index_array[j]].id, \
        system.tasks[index_array[j]].start, \
        system.tasks[index_array[j]].desc);
    }
}

/* index_act: stores in an array all the id's of the tasgs that have the
activity given in the argument and returns the size of the array */
int index_act(int array[], char activity[]){
    int i, j = -1;

    for (i = 0; i < id_counter; ++i){
        if (!strcmp(system.tasks[i].activ.act, activity)){
            ++j;
            array[j] = i;
        }
    }

    return j;
}

/* quicksort/partition: implementation of the quicksort algorithm
given in class to sort the tasks by their description*/
void quicksort(Item a[], int left, int right)
{
    int i;

    if (right <= left) return;
    i = partition(a, left, right);

    quicksort(a, left, i - 1);
    quicksort(a, i + 1, right);
}

int partition(Item a[], int left, int right)
{
    int i = left - 1;
    int j = right;
    Item v = a[right];

    while (i < j){
        while (less(a[++i], v));
        while (less(v, a[--j]))
            if (j == left)
                break;
        if (i < j)
            exch(a[i], a[j]);
    }

    exch(a[i], a[right]);
    return i;
}