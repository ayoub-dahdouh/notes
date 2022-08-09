#ifndef NOTE_H
#define NOTE_H  

#include "linklist.h"

int menu1(char *dirname);
void read_notes(char *dirname, linklist notes);
void list_notes(linklist notes);
void add_note(char *dirname, linklist notes);
void remove_note(char *dirname, linklist notes);
char *make_path(char *dirname, char *notename);

#endif