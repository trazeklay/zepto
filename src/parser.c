#include "parser.h"
#include <string.h>

/* Parse the YAML file and store data in ScriptCollection */
void parse_yaml(const char *filename, ScriptCollection *collection) {
    FILE *fh = fopen(filename, "rb");
    if (!fh) {
        perror("Failed to open file");
        return;
    }

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        fclose(fh);
        return;
    }

    yaml_parser_set_input_file(&parser, fh);

    char current_category[MAX_NAME_LENGTH] = "";
    int category_index = -1;
    int expecting_command_value = 0;
    int depth = 0;  // Tracks YAML nesting depth
    int in_scripts_section = 0;  // Ensures we're inside "scripts"

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error: %d\n", parser.error);
            break;
        }

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                depth++; // Entering a new nested structure
                break;

            case YAML_MAPPING_END_EVENT:
                depth--; // Exiting a nested structure
                if (depth == 1) {
                    category_index = -1;  // Exiting a category
                } else if (depth == 0) {
                    in_scripts_section = 0; // Leaving "scripts" section
                }
                break;

            case YAML_SCALAR_EVENT: {
                char *value = (char *)event.data.scalar.value;

                if (depth == 1 && strcmp(value, "scripts") == 0) {
                    in_scripts_section = 1;
                } else if (in_scripts_section && depth == 2) {
                    // Inside the 'scripts' section, expecting a category
                    category_index++;
                    strncpy(collection->categories[category_index].name, value, MAX_NAME_LENGTH - 1);
                    collection->categories[category_index].command_count = 0;
                    collection->category_count++;
                } else if (in_scripts_section && depth == 3) {
                    // Inside a category, expecting a command key or value
                    if (expecting_command_value) {
                        int cmd_idx = collection->categories[category_index].command_count - 1;
                        strncpy(collection->categories[category_index].commands[cmd_idx].value,
                                value, MAX_VALUE_LENGTH - 1);
                        expecting_command_value = 0;
                    } else {
                        // Store command name
                        int cmd_idx = collection->categories[category_index].command_count;
                        strncpy(collection->categories[category_index].commands[cmd_idx].name,
                                value, MAX_NAME_LENGTH - 1);
                        collection->categories[category_index].command_count++;
                        expecting_command_value = 1;  // Next value should be command value
                    }
                }
                break;
            }

            case YAML_STREAM_END_EVENT:
                yaml_event_delete(&event);
                goto cleanup;

            default:
                break;
        }

        yaml_event_delete(&event);
    }

cleanup:
    yaml_parser_delete(&parser);
    fclose(fh);
}

/* Print parsed scripts */
void print_scripts(const ScriptCollection *collection) {
    printf("Parsed Scripts:\n");
    for (int i = 0; i < collection->category_count; i++) {
        printf("Category: %s\n", collection->categories[i].name);
        for (int j = 0; j < collection->categories[i].command_count; j++) {
            printf("  Command: %s -> %s\n",
                   collection->categories[i].commands[j].name,
                   collection->categories[i].commands[j].value);
        }
    }
}
