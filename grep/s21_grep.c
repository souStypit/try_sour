#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024
#define WRITE_FILE_NAME (mask & 1)

#define IFLAG (mask & 1 << 1)
#define VFLAG (mask & 1 << 2)
#define CFLAG (mask & 1 << 3)
#define NFLAG (mask & 1 << 4)
#define LFLAG (mask & 1 << 5)

void printFile(int mask, char *fileName, int *reti, regex_t *regex, char **patterns, int patCount);
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
    int fileCount = 0;
    char **patterns;
    int patCount = 0;

    while (argv[i][0] == '-' || sem) {
        if (!sem) {
            parseFlag(&mask, argv[i], &sem);
        } else {
            void *tmp = realloc(patterns, sizeof(char *) * (patCount + 1));
            error_msg(!tmp, "Realloc mistake.\n");
            patterns = tmp;
            patterns[patCount++] = strdup(argv[i]);
            sem = 0;
        }
        i++;
    }

    //reti = regcomp(&regex, patterns, mask);
    
    if ((fileCount = argc - i) > 1) mask |= 1;
    
    while (i < argc) {
        printFile(mask, argv[i++], &reti, &regex, patterns, patCount);
    }

    if (patterns) {
        for (int i = 0; i < patCount; i++) {
            free(patterns[i]);
        }
        free(patterns);
    }
    regfree(&regex);
    return 0;
}

void printFile(int mask, char *fileName, int *reti, regex_t *regex, char **patterns, int patCount) {
    FILE *fp = fopen(fileName, "r");
    error_msg(fp == NULL, "No such file: '%s'\n", fileName);
    
    char *line;
    int line_number = 1, google = 0, matchCount = 0;

    //*reti = regexec(regex, patterns, 0, NULL, 0);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        int i = 0;
        while (i < patCount) {
            if (!regcomp(regex, patterns[i], mask)) {
                if (VFLAG) {
                    if (regexec(regex, line, 0, NULL, 0)) {
                        google = 1;
                    }
                } else {
                    if (!regexec(regex, line, 0, NULL, 0)) {
                        google = 1;
                    }
                }
            }
            i++;
        }
        if (google) {
            matchCount++;
            if (!CFLAG && !LFLAG) {
                if (WRITE_FILE_NAME) printf("%s:", fileName);
                if (NFLAG) printf("%d:", line_number);
                printf("%s", line);
                fflush(stdout);
                google = 0;
            }
        }

        line_number++;
    }

    if (CFLAG) {
        if (WRITE_FILE_NAME) printf("%s:", fileName);
        printf("%d", matchCount);
    } else if (LFLAG) {
        printf("%s\n", fileName);
    }
    google = 0;

    fclose(fp);
}

void parseFlag(int *mask, char *flag, int *sem) {
    for (int i = 1; i < (int)strlen(flag); i++) {
        switch (flag[i]) {
            case 'i': 
                *mask |= (1 << 1);
                break;
            case 'v':
                *mask |= (1 << 2);
                break;
            case 'c':
                *mask |= (1 << 3);
                break;
            case 'n':
                *mask |= (1 << 4);
                break;
            case 'l':
                *mask |= (1 << 5);
                break;
            case 'e':
                *mask |= (1 << 6);
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