/************************************************************************************
** unittest1.c
** This unit test is designed to test updateCoins function.
** This unit test is build on a past student's test provided & approved by professor.
**
** Include the following lines in makefile:
** unittest1: unittest1.c dominion.o rngs.o
**      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define ASSERTS 1

int main() 
{
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < maxHandCount; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("\n--------------------Start Testing updateCoins()--------------------\n");

    // function should throw error when bonus is negative. 
    printf("Test player 1 with 5 copper treasure card(s) and -1 bonus.\n");
    bonus = -1;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[1] = maxHandCount;                 // set the number of cards on hand

    memcpy(G.hand[1], coppers, sizeof(int) * MAX_HAND); // set all the cards to copper
    updateCoins(1, &G, bonus);
#if (NOISY_TEST == 1)
                printf("Copper G.coins = %d, expected = N/A because bonus cannot be negative", G.coins);
#endif

    if(G.coins == maxHandCount * 1 + bonus)
    {
        printf("\nTEST FAILED - Bonus cannot be negative\n");
    }
    else
    {
        printf("\nTEST SUCCESSFULLY COMPLETED\n");
    }



    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", (p + 1), handCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                memcpy(G.hand[p], coppers, sizeof(int) * MAX_HAND); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("Copper G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
#if(ASSERTS == 1)
                assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct
#endif

                memcpy(G.hand[p], silvers, sizeof(int) * MAX_HAND); // set all the cards to silver
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("Silver G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif
#if(ASSERTS == 1)
                assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct
#endif

                memcpy(G.hand[p], golds, sizeof(int) * MAX_HAND); // set all the cards to gold
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("Gold G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
#if(ASSERTS == 1)
                assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
#endif
            }
        }
    }

    printf("\nTEST SUCCESSFULLY COMPLETED\n");
    printf ("\n--------------------End Testing updateCoins()--------------------\n");

    return 0;
}