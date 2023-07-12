#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <regex.h>

#define IFLAG (mask & REG_ICASE)

void printFile(int mask, char *fileName, int *reti, regex_t *regex, char *patterns);
void parseFlag(int *mask, char *flag, int *sem);
void option_i(int mask, char ch);
int error_msg(int condition, const char *fmt, ...);

int main(int argc, char **argv) {
    error_msg(argc < 2, "Usage: s21_cat <opt_1> ... <opt_n> <file_1> ... <file_m>\n");

    regex_t regex;
    int reti;
    int mask = 0, mode = 0, i = 1;
    int cflags = 0;
    int sem = 0;
    char *patterns = NULL;

    while (argv[i][0] == '-' || sem) {
        if (!sem) {
            parseFlag(&mask, argv[i], &sem);
        } else {
            patterns = strdup(argv[i]);
            sem = 0;
        }
        i++;
    }
    
    if (IFLAG) cflags |= REG_ICASE;

    reti = regcomp(&regex, argv[i++], cflags);

    while (i < argc) {
        printFile(mask, argv[i++], &reti, &regex, patterns);
    }
    
    if (patterns) free(patterns);
    regfree(&regex);
    return 0;
}

void printFile(int mask, char *fileName, int *reti, regex_t *regex, char *patterns) {
    FILE *fp = fopen(fileName, "r");
    error_msg(fp == NULL, "No such file: '%s'\n", fileName);
    
    char ch;

    *reti = regexec(regex, patterns, 0, NULL, 0);

    while ((ch = getc(fp)) != EOF && ch != patterns[0]) {
        
    }

    fclose(fp);
}

void parseFlag(int *mask, char *flag, int *sem) {
    for (int i = 1; i < (int)strlen(flag); i++) {
        switch (flag[i]) {
            case 'i':
                *mask |= REG_ICASE;
                break;
            default:
                error_msg(1, "No such flag: '%s'\n", flag);
        }
    }
    *sem = 1;
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