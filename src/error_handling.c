#include "../include/error_handling.h"

void syntax_error(char *argv_name) {
    fprintf(stderr, "Usage: %s <input_file> <output_file> <option>\n", argv_name);
    exit(-1);
}

void invalid_option(char *argv_option) {
    fprintf(stderr, "Invalid option: %s\n", argv_option);
    fprintf(stderr, "Available options: -b, -g, -t\n");
    exit(-1);
}