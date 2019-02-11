/************************************************************************************
** cardtest1.c
** This card test is designed to test card Smithy.
** Smithy - add three cards.
**
** Include the following lines in makefile:
** cardtest1: cardtest1.c dominion.o rngs.o
**      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() 
{
	struct gameState G, testG;
    int i = 0;
    int player = 0, numPlayers = 0;
    int seed = 1000;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int smithyInHandG = 0, smithyInHandTestG = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	printf ("\n--------------------Start Testing Card: %s --------------------\n", TESTCARD);

	for(numPlayers = 2; numPlayers < 5; numPlayers++)
	{
		printf ("\nTesting %d players.\n", numPlayers);
		
		// initialize a game state and player cards.
		initializeGame(numPlayers, k, seed, &G);
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
		player = whoseTurn(&testG);

		// Test1: check the player hands count after Smithy card is played.
		printf("Testing hand count after Smithy is played.\n");
		if(testG.handCount[player] - 1 == G.handCount[player])
		{
			printf("	TEST PASSED - hand count is correct. Current hand count = %d. Expected hand count = %d; Actual hand count = %d.\n", testG.handCount[player], testG.handCount[player] - 1, G.handCount[player]);
		}
		else
		{
			printf("	TEST FAILED - hand count is incorrect. Current hand count = %d. Expected hand count = %d; Actual hand count = %d.\n", testG.handCount[player], testG.handCount[player] - 1, G.handCount[player]);
		}
		printf("\n");

		
		// Test2: Check Smithy is added to player's hand.
		printf("Testing Smithy is added to player's hand.\n");
		if(G.hand[player][testG.handCount[player]] != -1)
		{
			printf("	TEST PASSED - Smithy card was added to the players hand.\n");
		}
		else
		{
			printf("	TEST FAILED - Smithy card was NOT added to the players hand.\n");
		}
		printf("\n");

		// Test3: Check if Smithy card is played - if so, player's card count will increase by 2.
		printf("Testing card count after Smithy is played.\n");
		if(testG.playedCardCount + 2 == G.playedCardCount)
		{
			printf("	TEST PASSED - Current card count = %d. Expected card count = %d; Actual card count = %d.\n", testG.playedCardCount, testG.playedCardCount + 2, G.playedCardCount);
		}
		else
		{
			printf("	TEST FAILED - Current card count = %d. Expected card count = %d; Actual card count = %d.\n", testG.playedCardCount, testG.playedCardCount + 2, G.playedCardCount);
		}
		printf("\n");
		
		// Test4: Check Smithy card count is correct after it's played. Difference should be 1.
		printf("Checking Smithy card count after one played.\n");
		// Count all Smithy in hand before it's played.
		for (i = 0; i < testG.handCount[0]; i++)
		{
	        if(testG.hand[0][i] == smithy)
			{
				smithyInHandTestG++;
			}
		}

		// Count all Smithy in hand after it's played.
		for (i = 0; i < G.handCount[0]; i++)
		{
	        if(G.hand[0][i] == smithy)
			{
				smithyInHandG++;
			}
		}

		int smithyCountDiff = smithyInHandTestG - smithyInHandG;
		switch(smithyCountDiff)
		{
			case 1:
				printf("	TEST PASSED - Smithy count before: %d; after: %d; expected after: %d.\n", smithyInHandTestG, smithyInHandG, (smithyInHandTestG - 1));
				break;
			default:
				printf("	TEST FAILED - Smithy count before: %d; after: %d; expected after: %d.\n", smithyInHandTestG, smithyInHandG, (smithyInHandTestG - 1));
				break;
		}
		printf("\n");
		
		
		// Test5: Discard Test: Check if card was discarded
		printf("Checking if Smithy is discarded after played.\n");
		int difference = testG.discardCount[player] - G.discardCount[player];
		switch(difference)
		{
			case 0:
				printf("	TEST PASSED - Smithy was discarded.\n");	
				break;

			default:
				printf("	TEST FAILED - Smithy was NOT discarded.\n");
				break;
		}
		printf("\n");
	}

	printf ("\n--------------------End Testing Card: %s --------------------\n", TESTCARD);
	printf("\nTEST SUCCESSFULLY COMPLETED\n");

	return 0;
}


