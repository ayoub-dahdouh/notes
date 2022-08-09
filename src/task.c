#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "task.h"
#include "com.h"
#include "linklist.h"

void list_tasks(char *notename, linklist tasks);
void read_tasks(char *notepath, linklist tasks);
void add_task(linklist tasks);
void remove_task(linklist tasks);
void setdone_task(linklist tasks);
void save_task(char *notepath, linklist tasks);
void return_to_menu1(int modified, char *notepath, linklist tasks);

int menu2(char *notepath, char *notename)
{
    static int first = 1, modified = 0, show = 1;
    int choice = 0;
    linklist tasks;

    if (first)
    {
        first = 0;
        tasks = lopen();
        read_tasks(notepath, tasks);
    }
    if (show)
    {
        list_tasks(notename, tasks);
    }

    choice = choose_number(1, 5);
    if (choice == 1)
    {
        add_task(tasks);
        modified = 1;
        show = 1;
        return 1;
    }
    else if (choice == 2)
    {
        remove_task(tasks);
        modified = 1;
        show = 1;
        return 1;
    }
    else if (choice == 3)
    {
        setdone_task(tasks);
        modified = 1;
        show = 1;
        return 1;
    }
    else if (choice == 4)
    {
        if (modified)
        {
            save_task(notepath, tasks);
        }
        else
        {
            printf("nothing change\n");
        }
        show = 0;
        modified = 0;
        return 1;
    }
    else if (choice == 5)
    {
        return_to_menu1(modified, notepath, tasks);
        first = 1;
        return 0;
    }
    else
    {
        printf("unknown option\n");
        return 0;
    }
}

void return_to_menu1(int modified, char *notepath, linklist tasks)
{
    char line[10];
    literator it;
    struct task *tmp;

    if (modified)
    {
        printf("save the changes? ? y/N ");
        get_line_from_console(line, 10);
        if (line[0] == 'y')
        {
            save_task(notepath, tasks);
        }
    }
    it = lat(tasks, LFIRST);
    while (it)
    {
        tmp = (struct task *)it->data;
        check_free(tmp->name);
        check_free(tmp);
        linc(&it);
    }
}
void save_task(char *notepath, linklist tasks)
{
    FILE *fp;
    literator it;
    struct task *tmp;

    if (remove(notepath) != 0)
    {
        error("error in saving tasks");
    }

    fp = fopen(notepath, "w");
    it = lat(tasks, LFIRST);
    while (it)
    {
        tmp = (struct task *)it->data;
        fprintf(fp, "%c;%s\n", tmp->status, tmp->name);
        linc(&it);
    }
    fclose(fp);

    printf("changes are saved\n");
}

void setdone_task(linklist tasks)
{
    int choice;
    struct task *tmp;

    choice = choose_number(6, tasks->count + 6);

    tmp = (struct task *)lget(tasks, choice - 6);

    if (tmp->status == 'y')
    {
        tmp->status = 'n';
    }
    else
    {
        tmp->status = 'y';
    }
}

void remove_task(linklist tasks)
{
    int choice;
    struct task *tmp;

    choice = choose_number(6, tasks->count + 6);

    tmp = (struct task *)lget(tasks, choice - 6);

    ldel(tasks, choice - 6);

    check_free(tmp->name);
    check_free(tmp);
}

void add_task(linklist tasks)
{
    int len;
    char new_task[256];
    struct task *tmp;

    printf("task name: ");
    get_line_from_console(new_task, 256);

    tmp = (struct task *)check_malloc(sizeof(struct task));

    len = strlen(new_task);
    tmp->name = (char *)check_malloc(len + 1);
    tmp->status = 'n';

    strncpy(tmp->name, new_task, len);
    tmp->name[len] = 0;

    ladd(tasks, LLAST, tmp);
}

void read_tasks(char *notepath, linklist tasks)
{
    char line[1024];
    struct task *tmp;
    FILE *fp;

    fp = fopen(notepath, "r");
    if (!fp)
    {
        error("error in opening the note");
    }
    while (get_line_from_file(fp, line, 1024))
    {
        // printf("read: %s\n", line);
        tmp = parse_line(line);

        ladd(tasks, LLAST, tmp);
    }

    fclose(fp);
}

void list_tasks(char *notename, linklist tasks)
{
    int n = 6;
    struct task *tmp;
    literator it;

    printf("---------------[%s]---------------\n\n", notename);
    if (!lempty(tasks))
    {
        it = lat(tasks, LFIRST);
        while (it)
        {
            tmp = (struct task *)it->data;
            if (tmp->status == 'y')
            {
                printf("%d  %s\n", n++, tmp->name);
            }
            else
            {
                printf("%d* %s\n", n++, tmp->name);
            }

            linc(&it);
        }
        printf("\n");
    }
    else
    {
        printf("No tasks\n\n");
    }

    printf("1  Add\n");
    printf("2  Remove\n");
    printf("3  Set (not) done\n");
    printf("4  Save\n");
    printf("5  Return\n");
}
