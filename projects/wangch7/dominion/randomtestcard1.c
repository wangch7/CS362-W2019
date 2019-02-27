/************************************************************************************
** randomtestcard1.c
** This card test is designed to test card steward.
** Steward - Choose one of the three options below：
**			 1） Gain 2 cards;
**			 2） Gain 2 coins;
**			 3） Trash 2 cards.
**
** This card test is build on a past student's test provided & approved by professor.
**
** Include the following lines in makefile:
** randomtestcard1: randomtestcard1.c dominion.o rngs.o
**      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
*************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "steward"
#define MAX_TESTS 1000

int main() 
{
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m, t, testIndex = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int choice = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	double time_spent = 0.0;


	printf ("\n--------------------Start Testing Card: %s --------------------\n", TESTCARD);

	clock_t begin = clock();

	// Generate 1000 random tests.
	for(t = 0; t < MAX_TESTS; t++)
	{
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		// randomly chooce one option from the Steward card.
		choice1 = random() % 3 + 1;
		testIndex++;
		printf("Test# %d; Choice1 = %d\n", testIndex, choice1);


		switch(choice1)
		{
			case 1:
				// ----------- TEST 1: choice1 = 1 = + 2 cards --------------
				printf("TEST 1: Choice1 = player chooses to gain 2 cards.\n");

				// copy the game state to a test case
				memcpy(&testG, &G, sizeof(struct gameState));
				//choice1 = 1;
				printf("Player's current hand count = %d. deck count = %d. coins = %d\n", testG.handCount[thisPlayer], testG.deckCount[thisPlayer], testG.coins);
				cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

				newCards = 2;
				xtraCoins = 0;
				printf("New hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
				printf("New deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
				printf("New coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
				assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
				assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
				assert(testG.coins == G.coins + xtraCoins);
				printf("TEST 1 PASSED.\n");
				printf("\n");
				break;

			case 2:
				// ----------- TEST 2: choice1 = 2 = + 2 coins --------------
				printf("TEST 2: choice1 = player chooses to gain 2 coins\n");

				// copy the game state to a test case
				memcpy(&testG, &G, sizeof(struct gameState));
				//choice1 = 2;
				printf("Player's current hand count = %d. deck count = %d. coins = %d\n", testG.handCount[thisPlayer], testG.deckCount[thisPlayer], testG.coins);
				cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

				newCards = 0;
				xtraCoins = 2;
				printf("New hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
				printf("New deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
				printf("New coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
				assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
				assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
				assert(testG.coins == G.coins + xtraCoins);
				printf("TEST 2 PASSED.\n");
				printf("\n");
				break;

			default:
				// ----------- TEST 3: choice1 = 3 = trash two cards --------------
				printf("TEST 3: choice1 = player chooses to trash 2 cards\n");
				//choice1 = 3;

				// cycle through each eligible combination of 2 cards to trash
				for (i = 1; i < G.handCount[thisPlayer]; i++) 
				{
					for (j = i + 1; j < G.handCount[thisPlayer]; j++) 
					{

						G.hand[thisPlayer][0] = steward;
						G.hand[thisPlayer][1] = curse;
						G.hand[thisPlayer][2] = adventurer;
						G.hand[thisPlayer][3] = remodel;
						G.hand[thisPlayer][4] = great_hall;

						// copy the game state to a test case
						memcpy(&testG, &G, sizeof(struct gameState));

						printf("Starting cards: ");
						for (m = 0; m < testG.handCount[thisPlayer]; m++) 
						{
							printf("(%d)", testG.hand[thisPlayer][m]);
						}

						choice2 = j;
						choice3 = i;
						remove1 = testG.hand[thisPlayer][i];
						remove2 = testG.hand[thisPlayer][j];
						cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

						printf("; Cards removed: (%d)(%d); ", remove1, remove2);
						printf("Ending cards: ");

						// tests that the removed cards are no longer in the player's hand
						for (m = 0; m < testG.handCount[thisPlayer]; m++)
						{
							printf("(%d)", testG.hand[thisPlayer][m]);
							assert(testG.hand[thisPlayer][m] != remove1);
							assert(testG.hand[thisPlayer][m] != remove2);
						}

						printf("; Expected ending cards: ");
						for (m = 1; m < G.handCount[thisPlayer]; m++) 
						{
							if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) 
							{
								printf("(%d)", G.hand[thisPlayer][m]);
							}
						}
						printf("\n");
					}
					printf("\n");
				
				}
				printf("TEST 3 PASSED.\n");
				printf("\n");
				break;
			}
	}

	printf ("\n--------------------End Testing Card: %s --------------------\n", TESTCARD);
	printf("\nTEST SUCCESSFULLY COMPLETED\n");

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time elpased is %f seconds.\n", time_spent);

	return 0;
}


