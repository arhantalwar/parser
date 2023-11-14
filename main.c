#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// to hold variable info
typedef struct atom {

    char* data_type;
    char* var_name;
    char* var_value;

} atom;

static int atom_list_count = 0;

// i32 token
static char* i32 = "i32";
bool is_i32 = false;

// = token
static char* equals = "=";

// + token
static char* addition = "+";

// to hold var_name until we parse it's value and then store in atom
static char* var_name = "";

// to hold var_value and then store it in the atom
static char* var_value = "";

// to hold variables (for now we could hold 10 var)
atom var_list[10];

bool check_for_token(char* token, char curr_char) {

    if(strcmp(i32, token) == 0) {
        is_i32 = true;
        return true;
    }

    if(equals[0] == curr_char) {
        var_name = strdup(strtok(token, "="));
        return true;
    }

    if(addition[0] == curr_char) {
        var_name = strdup(strtok(token, "+"));
        return true;
    }

    return false;

}

void read_source(FILE* source_file) {

    char line[128];
    char token[128] = "";

    while(fgets(line, sizeof(line), source_file) != NULL) {
        for(int i = 0; i < sizeof(line); i++) {

            // if EOL (End of line) 
            if(line[i] == ';') {

                if(is_i32) {
                    var_value = strdup(token);

                    atom* var = (atom*) malloc(sizeof(atom));
                    var->var_value = strdup(var_value);
                    var->var_name = strdup(var_name);
                    var->data_type = i32;

                    var_list[atom_list_count++] = *var;

                    printf("----------------\n");
                        printf("%s\n", var->data_type);
                        printf("%s\n", var->var_name);
                        printf("%s\n", var->var_value);
                    printf("----------------\n");

                    is_i32 = false;
                    strncpy(token, "", sizeof(token));

                }


            } else {

                // get next char and search for token
                if(line[i] != ' ') {

                    strncat(token, &line[i], 1);
                    bool is_token_found = check_for_token(token, line[i]);

                    if(is_token_found) {
                        strncpy(token, "", sizeof(token));
                    }

                }


            }

        }
    }

}

int main(int argc, char* argv[]) {

    // IF FILE IS NOT PASSED
    if(argc < 2) {
        printf("Supply input file IDIOT!!\n");
        exit(EXIT_FAILURE);
    }

    FILE* source_file = fopen(argv[1], "r");

    // READING THE SOURCE CODE
    read_source(source_file);
    fclose(source_file);

    for(int i = 0; i < atom_list_count; i++) {
        free(var_list[i].var_name);
        free(var_list[i].var_value);
    }

    return 0;

}
