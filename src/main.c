#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include "note.h"
#include "com.h"

void version();
void help();
char *get_default_directory();


int main(int argc, char *argv[])
{
    char *dirname = NULL;
    if (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            if (argv[1][1] == 'v')
            {
                version();
                exit(EXIT_SUCCESS);
            }
            else if (argv[1][1] == 'h')
            {
                help();
                exit(EXIT_SUCCESS);
            }
            else
            {
                error("unknown option");
            }
        }
        else
        {
            dirname = argv[1];
        }
    }
    else
    {
        dirname = get_default_directory();
    }

    while (menu1(dirname))
    {
    }
}

void version()
{
    printf("%s %s\n", PROGRAM, PROGRAM_VERSION);
}

void help()
{
    printf("Usage:\t%s [OPTION] [DIR]\n"
           "DIR:\tdirectory where notes are stored, by default (~/Notes)\n"
           "OPTION:\n\t-h\thelp\n\t-v\tversion\n",
           PROGRAM);
}

char *get_default_directory()
{
    struct passwd *pw;
    char *dirname;
    int len;

    pw = getpwuid(getuid());
    len = strlen(pw->pw_dir);
    dirname = malloc(len + 7);
    strncpy(dirname, pw->pw_dir, len);
    strncpy(dirname + len, "/Notes", 7);
    return dirname;
}