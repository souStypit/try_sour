#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TFLAG (mask & (1 << 0))
#define SFLAG (mask & (1 << 1))
#define NFLAG (mask & (1 << 2))
#define EFLAG (mask & (1 << 3))
#define BFLAG (mask & (1 << 4))

void printFile(int mask, char *fileName);
void parseFlag(int *mask, int mode, char *flag);
void parseFlagSingle(int *mask, char *flag);
void parseFlagWord(int *mask, char *flag);
void option_e(int mask, char ch);
void option_s(int mask, char prev, char ch, int *flag);
void option_nb(int mask, char prev, char ch, int *line);
int option_tt(int mask, char ch);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: s21_cat <opt_1> ... <opt_n> <file_1> ... <file_m>\n");
        exit(1);
    }

    int mask = 0, i = 1, mode = 0;

    while ((argv[i][0] == '-') || (mode = !strncmp(argv[i], "--", 2))) {    //Надо проверить
        parseFlag(&mask, mode, argv[i++]);
    }

    while (i < argc) {
        printFile(mask, argv[i++]);
    }

    return 0;
}

void parseFlag(int *mask, int mode, char *flag) {
    if (mode)  //К той же проверке
        parseFlagWord(mask, flag);
    else
        parseFlagSingle(mask, flag);
}

void parseFlagWord(int *mask, char *flag) {
    for (int i = 1; i < (int)strlen(flag); i++) {
        if (!strcmp(flag, "--number-nonblank")) {
            *mask |= (1 << 4 | 1 << 2);
        } else if (!strcmp(flag, "--number")) {
            *mask |= 1 << 2;
        } else if (!strcmp(flag, "--squeeze-blank")) {
            *mask |= 1 << 1;
        }
    }
}

void parseFlagSingle(int *mask, char *flag) {
    for (int i = 1; i < (int)strlen(flag); i++) {
        switch (flag[i]) {
            case 'b':
                *mask |= (1 << 4 | 1 << 2);
                break;
            case 'e':
                *mask |= 1 << 3;
                break;
            case 'E':
                *mask |= 1 << 3;
                break;
            case 'n':
                *mask |= 1 << 2;
                break;
            case 's':
                *mask |= 1 << 1;
                break;
            case 't':
                *mask |= 1 << 0;
                break;
            case 'T':
                *mask |= 1 << 0;
                break;
        }
    }
}

void printFile(int mask, char *fileName) {
    FILE *fp = fopen(fileName, "r");
    char ch, prev = '\n';
    int line = 1, flag = 0;
    if (fp == NULL) {
        printf("No such file '%s'.\n", fileName);
        exit(1);
    }

    while ((ch = getc(fp)) != EOF) {
        option_s(mask, prev, ch, &flag);
        if (flag != 2) {
            option_nb(mask, prev, ch, &line);
            option_e(mask, ch);
            if (!option_tt(mask, ch)) {
                printf("%c", ch);
            }
            prev = ch;
        }
    }

    fclose(fp);
}

void option_s(int mask, char prev, char ch, int *flag) {
    if (prev == '\n' && SFLAG) {
        if (ch == '\n')
            *flag = *flag ? 2 : 1;
        else
            *flag = 0;
    }
}

void option_e(int mask, char ch) {
    if (EFLAG && ch == '\n') printf("$");
}

int option_tt(int mask, char ch) {
    if (TFLAG && ch == '\t') {
        printf("^I");
        return 1;
    }
    return 0;
}

void option_nb(int mask, char prev, char ch, int *line) {
    if (prev == '\n' && NFLAG && (!BFLAG || ch != '\n'))
        printf("%6d  ", (*line)++);
}
