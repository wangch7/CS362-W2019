/************************************************************************************
** unittest2.c
** This unit test is designed to test getCost function.
**
** Include the following lines in makefile:
** unittest2: unittest2.c dominion.o rngs.o
**      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
*************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"



struct Card
{
	char name[50];
	int cost;
	int position;
};



int main() 
{	
	struct Card cardArray[27];
	int cardCost;
	int i = 0, j = 0;

	// Initialize cardArray to all possible cards.
	strcpy(cardArray[0].name, "curse");
	cardArray[0].cost = 0;
	strcpy(cardArray[1].name, "estate");
	cardArray[1].cost = 2;
	strcpy(cardArray[2].name, "duchy");
	cardArray[2].cost = 5;
	strcpy(cardArray[3].name, "province");
	cardArray[3].cost = 8;
	strcpy(cardArray[4].name, "copper");
	cardArray[4].cost = 0;
	strcpy(cardArray[5].name, "silver");
	cardArray[5].cost = 3;
	strcpy(cardArray[6].name, "gold");
	cardArray[6].cost = 6;
	strcpy(cardArray[7].name, "adventurer");
	cardArray[7].cost = 6;
	strcpy(cardArray[8].name, "council_room");
	cardArray[8].cost = 5;
	strcpy(cardArray[9].name, "feast");
	cardArray[9].cost = 4;
	strcpy(cardArray[10].name, "gardens");
	cardArray[10].cost = 4;
	strcpy(cardArray[11].name, "mine");
	cardArray[11].cost = 5;
	strcpy(cardArray[12].name, "remodel");
	cardArray[12].cost = 4;
	strcpy(cardArray[13].name, "smithy");
	cardArray[13].cost = 4;
	strcpy(cardArray[14].name, "village");
	cardArray[14].cost = 3;
	strcpy(cardArray[15].name, "baron");
	cardArray[15].cost = 4;
	strcpy(cardArray[16].name, "great_hall");
	cardArray[16].cost = 3;
	strcpy(cardArray[17].name, "minion");
	cardArray[17].cost = 5;
	strcpy(cardArray[18].name, "steward");
	cardArray[18].cost = 3;
	strcpy(cardArray[19].name, "tribute");
	cardArray[19].cost = 5;
	strcpy(cardArray[20].name, "ambassador");
	cardArray[20].cost = 3;
	strcpy(cardArray[21].name, "cutpurse");
	cardArray[21].cost = 4;
	strcpy(cardArray[22].name, "embargo");
	cardArray[22].cost = 2;
	strcpy(cardArray[23].name, "outpost");
	cardArray[23].cost = 5;
	strcpy(cardArray[24].name, "salvager");
	cardArray[24].cost = 4;
	strcpy(cardArray[25].name, "sea_hag");
	cardArray[25].cost = 4;
	strcpy(cardArray[26].name, "treasure_map");
	cardArray[26].cost = 4;

	for(j = 0; j < 26; j++)
	{
		cardArray[j].position = j;
	}


    printf ("\n--------------------Start Testing getCost()--------------------\n");

    for(i = 2; i < 26; i++)
    {
		cardCost = getCost(cardArray[i].position);
		printf("Cost for card %s = %d, expected card cost = %d\n", cardArray[i].name, cardCost, cardArray[i].cost);
		assert(cardCost == cardArray[i].cost);
	}

	printf("TEST SUCCESSFULLY COMPLETED");
	printf ("\n--------------------End Testing getCost()--------------------\n");

	return 0;
}





