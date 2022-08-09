#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com.h"
#include "task.h"

// extern char buffer[];

void *check_malloc(int size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        error("internal error");
    }
    return ptr;
}

void check_free(void *ptr)
{
    if (!ptr)
    {
        free(ptr);
    }
}

int get_line_from_console(char str[], int max)
{
    int c = 0;
    int i = 0;

    fflush(stdin);
    while (i < max - 1 && (c = getchar()) != EOF && c != '\n')
    {
        str[i++] = c;
    }
    str[i] = '\0';

    // empty the buffer
    if (i == max - 1)
    {
        while (c != EOF && c != '\n')
        {
            c = getchar();
        }
    }
    return i;
}

int get_line_from_file(FILE *fp, char str[], int max)
{
    int c = 0;
    int i = 0;

    while (i < max - 1 && (c = fgetc(fp)) != EOF && c != '\n')
    {
        str[i++] = c;
    }
    str[i] = '\0';

    // empty the buffer
    if (i == max - 1)
    {
        while (c != EOF && c != '\n')
        {
            c = getchar();
        }
    }
    return i;
}

struct task *parse_line(char *line)
{
    struct task *tmp;
    int len;

    tmp = (struct task *)check_malloc(sizeof(struct task));

    if (line[0] == 'y' || line[0] == 'n')
    {
        tmp->status = line[0];
    }
    else
    {
        error("note has invalid format: 'y' or 'n' as expected");
    }
    if (line[1] != ';')
    {

        error("note has invalid format: ';' was expected");
    }

    len = strlen(line + 2);
    tmp->name = check_malloc(len + 1);

    strncpy(tmp->name, line + 2, len);
    tmp->name[len] = 0;
    return tmp;
}

void error(char *msg)
{
    printf("%s: error: %s\n", PROGRAM, msg);
    exit(EXIT_FAILURE);
}

int choose_number(int min, int max)
{
    long int choice = 0;
    char str[256];

    do
    {
        printf("number: ");
        get_line_from_console(str, 256);
        choice = atoi(str);
        if (choice < 1 || choice > max)
        {
            printf("incorrect number\n");
        }
    } while (choice < min || choice > max);

    return choice;
}