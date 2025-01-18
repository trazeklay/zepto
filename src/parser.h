#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <yaml.h>

#define MAX_CATEGORIES 50
#define MAX_COMMANDS 50
#define MAX_NAME_LENGTH 100
#define MAX_VALUE_LENGTH 512

/* Structure to store a command */
typedef struct {
    char name[MAX_NAME_LENGTH];
    char value[MAX_VALUE_LENGTH];
} Command;

/* Structure to store a category with its commands */
typedef struct {
    char name[MAX_NAME_LENGTH];
    Command commands[MAX_COMMANDS];
    int command_count;
} Category;

/* Structure to store all categories */
typedef struct {
    Category categories[MAX_CATEGORIES];
    int category_count;
} ScriptCollection;

void parse_yaml(const char *filename, ScriptCollection *collection);
void print_scripts(const ScriptCollection *collection);

#endif
