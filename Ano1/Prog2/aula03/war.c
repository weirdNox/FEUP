#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Card
{
    int value;
    struct Card *next;
} Card;

typedef struct
{
    int used;
    Card cards[120];
    Card *freeList;
    Card *top;
    Card *bottom;
} Deck;

Card *getNewCard(Deck *deck)
{
    Card *result = 0;
    if(deck->freeList)
    {
        result = deck->freeList;
        deck->freeList = result->next;
    }
    else
    {
        result = &deck->cards[deck->used++];
    }

    result->next = 0;
    return result;
}

Card *pushTop(Deck *deck, int value)
{
    Card *card = getNewCard(deck);
    card->value = value;
    card->next = deck->top;
    deck->top = card;
    if(!deck->bottom)
    {
        deck->bottom = deck->top;
    }
    return card;
}

Card *pushBottom(Deck *deck, int value)
{
    Card *card = getNewCard(deck);
    card->value = value;
    if(deck->bottom)
    {
        deck->bottom->next = card;
    }
    else
    {
        deck->top = card;
    }
    deck->bottom = card;
    return card;
}

int pop(Deck *deck)
{
    Card *card = deck->top;
    if(!card)
    {
        return -1;
    }
    deck->top = card->next;
    if(!deck->top)
    {
        deck->bottom = 0;
    }
    card->next = deck->freeList;
    deck->freeList = card;
    return card->value;
}

void printDeck(Deck *deck)
{
    Card *card = deck->top;
    fprintf(stderr, "Deck: ");
    while(card)
    {
        fprintf(stderr, "%d", card->value);
        if(card->next)
        {
            fprintf(stderr, " -> ");
        }
        card = card->next;
    }
    fprintf(stderr, "\n");
}

int readVal(char buffer[4])
{
    int value = 0;
    if(buffer[0] >= 'A')
    {
        switch(buffer[0])
        {
            case 'J': { value = 11; } break;
            case 'Q': { value = 12; } break;
            case 'K': { value = 13; } break;
            case 'A': { value = 14; } break;
        }
    }
    else
    {
        value = atoi(buffer);
    }
    return value;
}

int main()
{
    Deck p1 = {}, p2 = {};
    int n; // the number of cards for player 1
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char cardp1[4]; // the n cards of player 1
        scanf("%s", cardp1);
        int value = readVal(cardp1);
        pushBottom(&p1, value);
    }
    int m; // the number of cards for player 2
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char cardp2[4]; // the m cards of player 2
        scanf("%s", cardp2);
        int value = readVal(cardp2);
        pushBottom(&p2, value);
    }

    Deck temp1 = {}, temp2 = {};
    int numWars = 0;
    for(;;)
    {
        printDeck(&p1);
        printDeck(&p2);
        pushBottom(&temp1, pop(&p1));
        pushBottom(&temp2, pop(&p2));
        if(temp1.bottom->value > temp2.bottom->value)
        {
            int next;
            while((next = pop(&temp1)) != -1)
            {
                pushBottom(&p1, next);
            }
            while((next = pop(&temp2)) != -1)
            {
                pushBottom(&p1, next);
            }
            ++numWars;
        }
        else if(temp2.bottom->value > temp1.bottom->value)
        {
            int next;
            while((next = pop(&temp1)) != -1)
            {
                pushBottom(&p2, next);
            }
            while((next = pop(&temp2)) != -1)
            {
                pushBottom(&p2, next);
            }
            ++numWars;
        }
        else
        {
            int pat = 0;
            for(int i = 0; i < 3; ++i)
            {
                if(!p1.top || !p2.top)
                {
                    pat = 1;
                    break;
                }
                pushBottom(&temp1, pop(&p1));
                pushBottom(&temp2, pop(&p2));
            }
            if(pat)
            {
                printf("PAT\n");
                break;
            }
        }

        if(!p1.top)
        {
            printf("2 %d\n", numWars);
            break;
        }
        else if(!p2.top)
        {
            printf("1 %d\n", numWars);
            break;
        }
    }

    return 0;
}
