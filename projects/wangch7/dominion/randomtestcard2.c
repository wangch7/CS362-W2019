/************************************************************************************
** randomtestcard2.c
** This card test is designed to test card Great Hall.
** Great Hall - add 1 card and add 1 action.
**
** Include the following lines in makefile:
** randomtestcard2: randomtestcard2.c dominion.o rngs.o
**      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
*************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "Great Hall"
#define MAX_TESTS 1000

int main() 
{
	struct gameState G, testG;
    int player = 0, numPlayers = 0, testIndex = 0;
    int seed = 1000;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	double time_spent = 0.0;

	printf ("\n--------------------Start Testing Card: %s --------------------\n", TESTCARD);

	clock_t begin = clock();

	for(testIndex = 0; testIndex < MAX_TESTS; testIndex++)
	{
		// Randomly generate the number of players. 2 - 4 players allowed.
		numPlayers = random() % 3 + 2;
		printf ("Test# %d - Testing %d players.\n", testIndex + 1, numPlayers);
		// initialize a game state and player cards.
		initializeGame(numPlayers, k, seed, &G);
		// copy game state to test state for comparison later.
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(great_hall, choice1, choice2, choice3, &G, handpos, &bonus);
		player = whoseTurn(&testG);

		// Test1: Check if Great Hall card is played. If so, played card count should incremeted by 1.
		printf("Testing card count after Great Hall is played.\n");
		int playedCardCountDiff = G.playedCardCount - testG.playedCardCount;
		// if(testG.playedCardCount == G.playedCardCount - 1)
		// {
		// 	printf("	TEST PASSED - played card count current = %d. Expected = %d; Actual = %d.\n", testG.playedCardCount, testG.playedCardCount + 1, G.playedCardCount);
		// }
		// else
		// {
		// 	printf("	TEST FAILED - played card count current = %d. Expected = %d; Actual = %d.\n", testG.playedCardCount, testG.playedCardCount + 1, G.playedCardCount);
		// }
		assert(playedCardCountDiff == 1 && "	TEST FAILED - hand count does not match.\n");
		printf("	TEST PASSED - played card count current = %d. Expected = %d; Actual = %d.\n", testG.playedCardCount, testG.playedCardCount + 1, G.playedCardCount);
		printf("\n");

		// Test2: Check if hand count after Great Hall is played. It should remain the same - discard one and gain one.
		printf("Testing hand count after Great Hall is played.\n");
		int handCountDiff = G.handCount[player] - testG.handCount[player];
		// if(testG.handCount[player] == G.handCount[player] + 1 - 1)
		// {
		// 	printf("	TEST PASSED - hand count current = %d. Expected = %d; Actual = %d.\n", testG.handCount[player], testG.handCount[player] + 1 - 1, G.handCount[player]);
		// }
		// else
		// {
		// 	printf("	TEST FAILED - hand count current = %d. Expected = %d; Actual = %d.\n", testG.handCount[player], testG.handCount[player] + 1 - 1, G.handCount[player]);
		// }
		assert(handCountDiff == 0 && "	TEST FAILED - hand count does not match.\n");
		printf("	TEST PASSED - hand count current = %d. Expected = %d; Actual = %d.\n", testG.handCount[player], testG.handCount[player] + 1 - 1, G.handCount[player]);
		printf("\n");
		
		// Test3: Check if Action is added by 1.
		printf("Checking Action is added +1.\n");
		int numActionDiff = G.numActions - testG.numActions;
		// if(testG.numActions == G.numActions - 1)
		// {
		// 	printf("	TEST PASSED - action count current = %d. Expected = %d; Actual = %d.\n", testG.numActions, testG.numActions + 1, G.numActions);
		// }
		// else
		// {
		// 	printf("	TEST FAILED - action count current = %d. Expected = %d; Actual = %d.\n", testG.numActions, testG.numActions + 1, G.numActions);
		// }
		assert(numActionDiff == 1 && "	TEST FAILED - action count is NOT added by 1.\n");
		printf("	TEST PASSED - action count current = %d. Expected = %d; Actual = %d.\n", testG.numActions, testG.numActions + 1, G.numActions);
		printf("\n");
		
		
		// Test4: Discard Test: Check if Great Hall card was discarded
		printf("Checking if Great Hall is discarded after played.\n");
		int difference = testG.discardCount[player] - G.discardCount[player];
		// switch(difference)
		// {
		// 	case 0:
		// 		printf("	TEST PASSED - Great Hall was discarded.\n");	
		// 		break;

		// 	default:
		// 		printf("	TEST FAILED - Great Hall was NOT discarded.\n");
		// 		break;
		// }
		assert(difference == 0 && "	TEST FAILED - Great Hall was NOT discarded.\n");
		printf("	TEST PASSED - Great Hall was discarded.\n");	
		printf("\n");
	}

	printf ("\n--------------------End Testing Card: %s --------------------\n", TESTCARD);
	printf("\nTEST SUCCESSFULLY COMPLETED\n");

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time elpased is %f seconds.\n", time_spent);

	return 0;
}


