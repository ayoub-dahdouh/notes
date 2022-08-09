#ifndef COM_H
#define COM_H

#include <stdio.h>
#include "task.h"


#define PROGRAM "notes"
#define PROGRAM_VERSION "pre-alpha"

void *check_malloc(int size);
void check_free(void *ptr);
void error(char *msg);
int choose_number(int min, int max);
int get_line_from_console(char str[], int max);
int get_line_from_file(FILE *fp, char str[], int max);
struct task *parse_line(char *line);

#endif