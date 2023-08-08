#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MIN_PLAYERS 2
#define MAX_PLAYERS 6
#define MAX_DECK 5
#define MAX_HAND 2

#define SUITS_IN_DECK 4
#define CARDS_VALUES 13
#define CARDS_IN_DECK (SUITS_IN_DECK*CARDS_VALUES)

void printHands(int i);
void printDeck();

struct playerStruct{
    int hand[MAX_HAND];
    int balance;
    char status[8];
} player[MAX_PLAYERS];

int deck[MAX_DECK];
bool cards[SUITS_IN_DECK * CARDS_VALUES];

int main() {
    srand(time(NULL));

    int playersCount;

    printf("Enter amount of players: ");
    if (!(scanf("%d", &playersCount) == 1)) return 1;
    if (playersCount < MIN_PLAYERS || playersCount > MAX_PLAYERS) return 1;

    for (int i = 0; i < CARDS_IN_DECK; i++)
        cards[i] = false; 

    int randValue;
    for (int i = 0; i < playersCount; i++) {
        for (int j = 0; j < 2; j++) {
            do {
                randValue = rand() % CARDS_IN_DECK;
            } while (cards[randValue] == true);
            cards[randValue] = true;
            player[i].hand[j] = randValue;
        }
    }

    for (int i = 0; i < MAX_DECK; i++) {
        do {
            randValue = rand() % CARDS_IN_DECK;
        } while (cards[randValue] == true);
        deck[i] = randValue;
    }

    for (int i = 0; i < playersCount; i++) {
        printHands(i);
    }
    printf("\n");

    printDeck(deck);
    printf("\n");

    int initDealer = rand() % playersCount;

    int currentDealer = initDealer;
    int currentBet;
    int defaultBlind = 10;
    int defaultCash = 1000;

    for (int i = 0; i < playersCount; i++)
        player[i].balance = defaultCash; 

    //while (playersCount >= MIN_PLAYERS) {
        if (currentDealer > playersCount) currentDealer = 0;
        currentBet = 0;

        int halfBlind = defaultBlind / 2;
        player[currentDealer].balance -= halfBlind;
        strcpy(player[currentDealer].status, "DEALER");
        currentBet += halfBlind;

        player[(currentDealer + 1) % playersCount].balance -= defaultBlind;
        strcpy(player[currentDealer + 1].status, "BLIND");
        currentBet += defaultBlind;

        printf("BET: %5d$\n", currentBet);
        currentDealer++;
    //}
    for (int i = 0; i < playersCount; i++) {
        printf("player-%1d balance: %4d$ \tstatus: %8s\n", i, player[i].balance, player[i].status);
    }

    return 0;
}

void printHands(int i) {
    printf("[ ");
    
    for (int j = 0; j < 2; j++) {
        switch (player[i].hand[j] % CARDS_VALUES) {
            case 0:
                printf("2");
                break;
            case 1:
                printf("3");
                break;
            case 2:
                printf("4");
                break;
            case 3:
                printf("5");
                break;
            case 4:
                printf("6");
                break;
            case 5:
                printf("7");
                break;
            case 6:
                printf("8");
                break;
            case 7:
                printf("9");
                break;
            case 8:
                printf("10");
                break;
            case 9:
                printf("J");
                break;
            case 10:
                printf("Q");
                break;
            case 11:
                printf("K");
                break;
            case 12:
                printf("A");
                break;
        }

        switch (player[i].hand[j] % SUITS_IN_DECK) {
            case 0: 
                printf("♠");
                break;
            case 1: 
                printf("♥");
                break;
            case 2: 
                printf("♣");
                break;
            case 3: 
                printf("♦");
                break;
        }

        printf(" ");
    }
    printf("]  ");
}

void printDeck() {
    printf("[ ");
    
    for (int i = 0; i < 5; i++) {
        switch (deck[i] % CARDS_VALUES) {
            case 0:
                printf("2");
                break;
            case 1:
                printf("3");
                break;
            case 2:
                printf("4");
                break;
            case 3:
                printf("5");
                break;
            case 4:
                printf("6");
                break;
            case 5:
                printf("7");
                break;
            case 6:
                printf("8");
                break;
            case 7:
                printf("9");
                break;
            case 8:
                printf("10");
                break;
            case 9:
                printf("J");
                break;
            case 10:
                printf("Q");
                break;
            case 11:
                printf("K");
                break;
            case 12:
                printf("A");
                break;
        }

        switch (deck[i] % SUITS_IN_DECK) {
            case 0: 
                printf("♠");
                break;
            case 1: 
                printf("♥");
                break;
            case 2: 
                printf("♣");
                break;
            case 3: 
                printf("♦");
                break;
        }

        printf(" ");
    }
    printf("]  ");
}