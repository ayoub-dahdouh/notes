#ifndef TASK_H
#define TASK_H

struct task
{
    char status; // 'y' : task done, 'n': task not yet done
    char *name;
};


int menu2();

#endif