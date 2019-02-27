/*******************************************************************************************
** randomtestadventurer.c
** This card test is designed to test card Adventurer.
** Adventurer - Reveal cards from player's deck until reveal 2 Treasure cards.
**				Put those Treasure cards into player's hand and discard the other
**				revealed cards.
**
** Include the following lines in makefile:
** randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
**      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
*******************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Adventurer"
#define MAX_TESTS 1000

int main() 
{
	struct gameState G, testG;
    int player = 0, numPlayers = 0, testIndex = 0;
    int seed = 1000;
    // int i = 0, adventurerInHandTestG = 0, adventurerInHandG = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	printf ("\n--------------------Start Testing Card: %s --------------------\n", TESTCARD);

	for(testIndex = 0; testIndex < MAX_TESTS; testIndex++)
	{
		// Randomly generate number of players. Valid number of players is 2 - 4.
		numPlayers = random() % 3 + 2;
		printf("Test# %d - Testing %d players.\n", testIndex + 1, numPlayers);
		// Initialize a game state and player cards.
		initializeGame(numPlayers, k, seed, &G);
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
		player = whoseTurn(&testG);

		// Test1: Player hand count should +1 after Adventurer card is played. Gain 2 Treasure card and discard Adventurer card.
		printf("Testing hand count after Adventurer is played.\n");
		//int handCountDiff = G.handCount[player] - testG.handCount[player];
		if(testG.handCount[player] + 1 == G.handCount[player])
		{
			printf("	TEST PASSED - hand count is correct. Current hand count = %d. Expected hand count = %d; Actual hand count = %d.\n", testG.handCount[player], testG.handCount[player] + 2 - 1, G.handCount[player]);
		}
		else
		{
			printf("	TEST FAILED - hand count is incorrect. Current hand count = %d. Expected hand count = %d; Actual hand count = %d.\n", testG.handCount[player], testG.handCount[player] + 2 - 1, G.handCount[player]);
		}
		//assert(handCountDiff == 1 && "	TEST FAILED - hand count does not match.\n");
		//printf("	TEST PASSED - hand count is correct. Current hand count = %d. Expected hand count = %d; Actual hand count = %d.\n", testG.handCount[player], testG.handCount[player] + 2 - 1, G.handCount[player]);
		printf("\n");



		// Test2: Player deck count should -2 since 2 Treasure card is drawn.
		printf("Testing deck count after Adventurer is played.\n");
		int deckCountDiff = testG.deckCount[player] - G.deckCount[player];
		// if(testG.deckCount[player] == G.deckCount[player] + 2)
		// {
		// 	printf("	TEST PASSED - deck count is correct. Deck count current = %d. Expected = %d; Actual = %d.\n", testG.deckCount[player], testG.deckCount[player] - 2, G.deckCount[player]);
		// }
		// else
		// {
		// 	printf("	TEST FAILED - deck count is correct. Deck count current = %d. Expected = %d; Actual = %d.\n", testG.deckCount[player], testG.deckCount[player] - 2, G.deckCount[player]);
		//}
		assert(deckCountDiff == 2 && "	TEST FAILED - deck count is not accurate.\n");
		printf("	TEST PASSED - deck count is correct. Deck count current = %d. Expected = %d; Actual = %d.\n", testG.deckCount[player], testG.deckCount[player] - 2, G.deckCount[player]);
		printf("\n");



		// Test3: Check if Adventurer card is played. If so, playedCardCount should +1.
		printf("Testing played card count after Adventurer is played.\n");
		if(testG.playedCardCount == G.playedCardCount - 1)
		{
			printf("	TEST PASSED - Played card count current = %d. Expected = %d; Actual = %d.\n", testG.playedCardCount, testG.playedCardCount + 1, G.playedCardCount);
		}
		else
		{
			printf("	TEST FAILED - Played card count current = %d. Expected = %d; Actual = %d.\n", testG.playedCardCount, testG.playedCardCount + 1, G.playedCardCount);
		}
		printf("\n");



		// Test4: Check if Adventurer card is discarded.
		printf("Checking if Adventurer is discarded after played.\n");
		int difference = testG.discardCount[player] - G.discardCount[player];
		// switch(difference)
		// {
		// 	case 0:
		// 		printf("	TEST PASSED - Adventurer was discarded.\n");	
		// 		break;

		// 	default:
		// 		printf("	TEST FAILED - Adventurer was NOT discarded.\n");
		// 		break;
		// }
		assert(difference == 0 && "	TEST FAILED - Adventurer was NOT discarded.\n");
		printf("	TEST PASSED - Adventurer was discarded.\n");
		printf("\n");
	}

	printf ("\n--------------------End Testing Card: %s --------------------\n", TESTCARD);
	printf("\nTEST SUCCESSFULLY COMPLETED\n");

	return 0;
}

