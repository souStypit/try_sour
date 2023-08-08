#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define STANDART_CUBE 19 + 1

#define MAX_STRING_LENGTH 128
#define CHAR_BEER_QUEST 0
#define CHAR_END_BEER_QUEST 2
#define ACT_1__BEER_QUEST 3

int find_str(FILE *scenary, int strNum);
void write_phrase(FILE *scenary, int strNum);
int make_action(FILE *scenary, int strNum);

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "ru");

    int modAttack = 5;
    int modShadow = 2;
    int modCharisma = 3;

    char *scenary_name = "scenary.txt";
    FILE *scenary = fopen(scenary_name, "r");
    if (!scenary) return 1;

    int choice;

    write_phrase(scenary, CHAR_BEER_QUEST + 0);
    make_action(scenary, ACT_1__BEER_QUEST + 0);

    printf("Выберите: ");
    if (scanf("%d", &choice) != 1) return 1;
    printf("\n");

    int randomValue = rand() % STANDART_CUBE;
    switch (choice) {
        case 1: {
            if (randomValue + modAttack + modShadow > 10) {
                write_phrase(scenary, CHAR_BEER_QUEST + 1);
            } else {
                write_phrase(scenary, CHAR_BEER_QUEST + 2);
            }
        }
        break;
        case 2: {
            if (randomValue + modAttack > 12) {
                write_phrase(scenary, CHAR_BEER_QUEST + 1);
            } else {
                write_phrase(scenary, CHAR_BEER_QUEST + 2);
            }
        }
        break;
        case 3: {
            if (randomValue + modCharisma > 13) {
                write_phrase(scenary, CHAR_BEER_QUEST + 1);
            } else {
                write_phrase(scenary, CHAR_BEER_QUEST + 2);
            }
        }
        break;
    }

    fclose(scenary);
    return(0);
}

int make_action(FILE *scenary, int strNum) {
    fseek(scenary, SEEK_SET, find_str(scenary, strNum));

    char bufferAmount[24], bufferActionText[256];
    fgets(bufferAmount, (int)sizeof(bufferAmount), scenary);
    
    int amountOfActions = atoi(bufferAmount);
    printf("\n");
    for (int i = 0; i < amountOfActions; i++) {
        fgets(bufferActionText, (int)sizeof(bufferActionText), scenary);
        printf("%s", bufferActionText);
    }
    printf("\n");
}

void write_phrase(FILE *scenary, int strNum) {
    fseek(scenary, SEEK_SET, find_str(scenary, strNum));
    
    char ch;
    int counter = 0;

    while ((ch = getc(scenary)) != '\n') {
        if (counter++ > MAX_STRING_LENGTH && ch == ' ') {
            printf("\n");
            counter = 0;
        } else {
            printf("%c", ch);
        }
    }
    printf("\n");  
}

int find_str(FILE *scenary, int strNum) {
    fseek(scenary, SEEK_SET, 0);
    int counterStr = 0, counterMain = 0;
    while (counterStr < strNum) {
        if (getc(scenary) != '\n') counterMain++;
        else counterStr++;
    }
    return counterMain;
}