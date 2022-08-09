#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "note.h"
#include "task.h"
#include "linklist.h"
#include "com.h"

int menu1(char *dirname)
{
    static int first = 1;
    int choice = 0;
    char *notename, *tmp;
    linklist notes;

    if (first)
    {
        first = 0;
        notes = lopen();
        read_notes(dirname, notes);
    }
    list_notes(notes);
    choice = choose_number(1, notes->count + 3);
    if (choice == 1)
    {
        add_note(dirname, notes);
        return 1;
    }
    else if (choice == 2)
    {
        remove_note(dirname, notes);
        return 1;
    }
    else if (choice == 3)
    {
        return 0;
    }
    else
    {
        notename = lget(notes, choice - 4);
        tmp = make_path(dirname, notename);

        while (menu2(tmp, notename))
        {
        }
        return 1;
    }
}

char *make_path(char *dirname, char *notename)
{
    int len_dir, len_note;
    char *tmp;

    len_dir = strlen(dirname);
    len_note = strlen(notename);
    tmp = check_malloc(len_dir + len_note + 1);

    strncpy(tmp, dirname, len_dir);
    tmp[len_dir] = '/';
    strncpy(tmp + len_dir + 1, notename, len_note);
    tmp[len_dir + len_note + 1] = 0;

    return tmp;
}

void remove_note(char *dirname, linklist notes)
{
    int choice;
    char *note, *tmp;

    choice = choose_number(3, notes->count + 3);
    note = (char *)lget(notes, choice - 4);
    tmp = make_path(dirname, note);

    if (remove(tmp) == 0)
    {
        printf("the note is removed\n");
    }
    else
    {
        ldel(notes, choice - 4);
        check_free(tmp);
        check_free(note);
        printf("error in removing the note\n");
    }
}
void add_note(char *dirname, linklist notes)
{
    int len_note;
    char new_note[256], *tmp;
    FILE *fp;

    printf("note name: ");
    get_line_from_console(new_note, 256);

    tmp = make_path(dirname, new_note);

    fp = fopen(tmp, "w");
    if (!fp)
    {
        printf("error in adding the note\n");
    }
    else
    {
        fclose(fp);

        check_free(tmp);

        len_note = strlen(new_note);
        tmp = (char *)check_malloc(len_note + 1);

        strncpy(tmp, new_note, len_note);
        tmp[len_note] = 0;

        ladd(notes, LLAST, tmp);
        printf("the note is saved\n");
    }
}
void read_notes(char *dirname, linklist notes)
{
    DIR *dir;
    struct dirent *file;
    char *filename;
    int len;

    dir = opendir(dirname);

    if (!dir)
    {
        error("error in opening the directory");
    }

    while ((file = readdir(dir)) != NULL)
    {
        if (file->d_name[0] != '.')
        {
            len = strlen(file->d_name) + 1;
            filename = check_malloc(len);
            strncpy(filename, file->d_name, len);
            ladd(notes, LLAST, filename);
        }
    }

    closedir(dir);
}

void list_notes(linklist notes)
{
    int n = 4;
    char *filename;
    literator it;

    printf("---------------[Notes]---------------\n\n");
    if (!lempty(notes))
    {
        it = lat(notes, LFIRST);
        while (it)
        {
            filename = (char *)it->data;
            printf("%d  %s\n", n++, filename);
            linc(&it);
        }
        printf("\n");
    }
    else
    {
        printf("No notes\n\n");
    }

    printf("1  Add\n");
    printf("2  Remove\n");
    printf("3  Exit\n");
}
