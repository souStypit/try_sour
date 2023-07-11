#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <regex.h>

#define IFLAG (mask & REG_ICASE)

void printFile(int mask, char *fileName);
void parseFlag(int *mask, char *flag);
void option_i(int mask, char ch);
int error_msg(int condition, const char *fmt, ...);

int main(int argc, char **argv) {
    error_msg(argc < 2, "Usage: s21_cat <opt_1> ... <opt_n> <file_1> ... <file_m>\n");

    regex_t regex;
    int reti;
    int mask = 0, mode = 0, i = 1;
    int cflags = 0;

    while (argv[i][0] == '-') parseFlag(&mask, argv[i++]);
    
    if (IFLAG) cflags |= REG_ICASE;

    reti = regcomp(&regex, argv[i], cflags);

    /*
    *
    *
    * 
    */
    
    reti = regexec(&regex, "abc", 0, NULL, 0);
    if (!reti) {
        printf("Match!\n");
    } else {
        printf("Not match!\n");
    }

    //while (i < argc) printFile(mask, argv[i++]);

    regfree(&regex);
    return 0;
}

void parseFlag(int *mask, char *flag) {
    for (int i = 1; i < (int)strlen(flag); i++) {
        switch (flag[i]) {
            case 'i':
                *mask |= REG_ICASE;
                break;
            default:
                error_msg(1, "No such flag: '%s'\n", flag);
        }
    }
}

int error_msg(int condition, const char *fmt, ...) {
    if (condition) { //if condition is unnecessary, equate 'condition' to 1
        va_list argp;
        va_start(argp, fmt);
        vprintf(fmt, argp);
        va_end(argp);
        exit(1);
    }
}