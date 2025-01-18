#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"

#define YAML_FILE "zepto.yaml"

/* Function to check if the file exists */
bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

/* Function to create the file with default content */
void create_default_yaml(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to create YAML file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "scripts:\n");

    fclose(file);
}

/* Function to find and execute a command */
void execute_command(const ScriptCollection *collection, const char *category, const char *command) {
    int found_category = -1, found_command = -1;

    /* Search for the category */
    for (int i = 0; i < collection->category_count; i++) {
        if (strcmp(collection->categories[i].name, category) == 0) {
            found_category = i;
            break;
        }
    }

    if (found_category == -1) {
        fprintf(stderr, "Error: Category '%s' not found.\n", category);
        exit(EXIT_FAILURE);
    }

    /* Search for the command within the found category */
    for (int j = 0; j < collection->categories[found_category].command_count; j++) {
        if (strcmp(collection->categories[found_category].commands[j].name, command) == 0) {
            found_command = j;
            break;
        }
    }

    if (found_command == -1) {
        fprintf(stderr, "Error: Command '%s' not found in category '%s'.\n", command, category);
        exit(EXIT_FAILURE);
    }

    /* Execute the command */
    system(collection->categories[found_category].commands[found_command].value);
}

int main(int argc, char *argv[]) {
    if (!file_exists(YAML_FILE)) {
        create_default_yaml(YAML_FILE);
    }

    /* Initialize the script collection */
    ScriptCollection scripts = {0};

    /* Parse YAML */
    parse_yaml(YAML_FILE, &scripts);

    /* Ensure we have exactly 3 arguments (program, category, command) */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <category> <command>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Execute the command */
    execute_command(&scripts, argv[1], argv[2]);

    return EXIT_SUCCESS;
}
