/************************************************************************************
** unittest3.c
** This unit test is designed to test initializeGame function.
**
** Include the following lines in makefile:
** unittest3: unittest3.c dominion.o rngs.o
**      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"



int main() 
{	
	struct gameState G;
	int seed = 1000;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       		sea_hag, tribute, smithy};
	int initGame;
	int numPlayer = 0;


    printf ("\n--------------------Start Testing initializeGame()--------------------\n");

    // When the number of players is valid 2 - 4 inclusive, the game should start normally.
    for(numPlayer = -1; numPlayer < 10; numPlayer++)
    {
    	if(numPlayer < 2 || numPlayer > 4)
    	{
    		printf("Game should NOT start with %d players.\n", numPlayer);
    		initGame = initializeGame(numPlayer, k, seed, &G);
    		assert(initGame == -1);
    	}
    	else
    	{
    		printf("Game should start successfully with %d players.\n", numPlayer);
    		initGame = initializeGame(numPlayer, k, seed, &G);
    		assert(initGame == 0);
    	}
    }
	
	printf("TEST SUCCESSFULLY COMPLETED");
	printf ("\n--------------------End Testing initializeGame()--------------------\n");

	return 0;
}





