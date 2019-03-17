/************************************************************************************
** cardtest3.c
** This card test is designed to test card Great Hall.
** Great Hall - add 1 card and add 1 action.
**
** Include the following lines in makefile:
** cardtest3: cardtest3.c dominion.o rngs.o
**      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
*************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Great Hall"

int main() 
{
	struct gameState G, testG;
    int player = 0, numPlayers = 0;
    int seed = 1000;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	printf ("\n--------------------Start Testing Card: %s --------------------\n", TESTCARD);

	for(numPlayers = 2; numPlayers < 5; numPlayers++)
	{
		printf ("\nTesting %d players.\n", numPlayers);
		
		// initialize a game state and player cards.
		initializeGame(numPlayers, k, seed, &G);
		// copy game state to test state for comparison later.
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(great_hall, choice1, choice2, choice3, &G, handpos, &bonus);
		player = whoseTurn(&testG);

		// Test1: Check if Great Hall card is played. If so, played card count should incremeted by 1.
		printf("Testing card count after Great Hall is played.\n");
		if(testG.playedCardCount == G.playedCardCount - 1)
		{
			printf("	TEST PASSED - played card count current = %d. Expected = %d; Actual = %d.\n", testG.playedCardCount, testG.playedCardCount + 1, G.playedCardCount);
		}
		else
		{
			printf("	TEST FAILED - played card count current = %d. Expected = %d; Actual = %d.\n", testG.playedCardCount, testG.playedCardCount + 1, G.playedCardCount);
		}
		printf("\n");

		// Test2: Check if hand count after Great Hall is played. It should remain the same - discard one and gain one.
		printf("Testing hand count after Great Hall is played.\n");
		if(testG.handCount[player] == G.handCount[player] + 1 - 1)
		{
			printf("	TEST PASSED - hand count current = %d. Expected = %d; Actual = %d.\n", testG.handCount[player], testG.handCount[player] + 1 - 1, G.handCount[player]);
		}
		else
		{
			printf("	TEST FAILED - hand count current = %d. Expected = %d; Actual = %d.\n", testG.handCount[player], testG.handCount[player] + 1 - 1, G.handCount[player]);
		}
		printf("\n");
		
		// Test2: Check if Action is added by 1.
		printf("Checking Action is added +1.\n");
		if(testG.numActions == G.numActions - 1)
		{
			printf("	TEST PASSED - action count current = %d. Expected = %d; Actual = %d.\n", testG.numActions, testG.numActions + 1, G.numActions);
		}
		else
		{
			printf("	TEST FAILED - action count current = %d. Expected = %d; Actual = %d.\n", testG.numActions, testG.numActions + 1, G.numActions);
		}
		printf("\n");
		
		
		// Test3: Discard Test: Check if Great Hall card was discarded
		printf("Checking if Great Hall is discarded after played.\n");
		int difference = testG.discardCount[player] - G.discardCount[player];
		switch(difference)
		{
			case 0:
				printf("	TEST PASSED - Great Hall was discarded.\n");	
				break;

			default:
				printf("	TEST FAILED - Great Hall was NOT discarded.\n");
				break;
		}
		printf("\n");
	}

	printf ("\n--------------------End Testing Card: %s --------------------\n", TESTCARD);
	printf("\nTEST SUCCESSFULLY COMPLETED\n");

	return 0;
}


