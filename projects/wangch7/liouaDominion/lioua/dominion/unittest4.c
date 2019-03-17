/************************************************************************************
** unittest4.c
** This unit test is designed to test buyCard function.
**
** Include the following lines in makefile:
** unittest4: unittest4.c dominion.o rngs.o
**      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
*************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"



int main() 
{	
	struct gameState state1;
    struct gameState state2;
    struct gameState state3;
    struct gameState state4;
    int supplyPos1 = 1;
    int supplyPos2 = 0;


    printf ("\n--------------------Start Testing buyCard()--------------------\n");

    // state1 - able to buy.
    state1.numBuys = 1;
    state1.coins = 12;

    // state2 - unable to buy due to insufficient number of buys left.
    state2.numBuys = 0;
    state2.coins = 10;

    // state3 - unable to buy because lacking that type of cards.
    state3.numBuys = 0;
    state3.coins = 10;


    // state4 - unable to buy because not enough coins.
    state4.numBuys = 1;
    state4.coins = 0;



    printf("\nTesting able to buy card.\n");
    if(buyCard(supplyPos1, &state1) == 0)
        printf("PASSED: testing coins = %d, buys = %d, supply = %d\n", state1.coins, state1.numBuys, supplyPos1);
    else
        printf("TEST FAILED.\n");



    printf("\nTesting insufficient number of buys.\n");
    if(buyCard(supplyPos1, &state2) == -1)
        printf("PASSED: testing coins = %d, buys = %d, supply = %d\n", state2.coins, state2.numBuys, supplyPos1);
    else
        printf("TEST FAILED.\n");



    printf("\nTesting insufficient number of card left.\n");
    if(buyCard(supplyPos2, &state3) == -1)
        printf("PASSED: testing coins = %d, buys = %d, supply = %d\n", state3.coins, state3.numBuys, supplyPos2);
    else
        printf("TEST FAILED.\n");
        


    printf("\nTesting insufficient coins.\n");
    if(buyCard(supplyPos1, &state4) == -1)
        printf("PASSED: testing coins = %d, buys = %d, supply = %d\n", state4.coins, state4.numBuys, supplyPos1);
    else
        printf("TEST FAILED.\n");



	
	printf("TEST SUCCESSFULLY COMPLETED");
	printf ("\n--------------------End Testing buyCard()--------------------\n");

	return 0;
}





