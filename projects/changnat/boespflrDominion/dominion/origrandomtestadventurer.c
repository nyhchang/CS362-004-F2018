/*************************************** 
 * Name: Robert Boespflug (boespflr)
 ** Class: CS362 - Assignment 4
 ** Date: 11/14/2018
 ** Desc: Random tester for smithy,
 ** some code burrowed from testDrawCard.c and
 ** the initializeGame() funcion in dominion.c
 *********************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "testStateChange.h"

int equal(int a, int b) {
  if (a == b)
    return 1;
  else
    return 0;
}

int testAdventurer( int p, struct gameState * g, int tempHand[]) {
	//init test game state testg to compare aginst g
	struct gameState testg;

	//copy game state
        memcpy(&testg, g, sizeof(struct gameState));
	int bonus = 0, fcount = 0;

	//call playAdventurer through cardeffect
	cardEffect(adventurer, 0, 0, 0, &testg, 0, &bonus);

	//test state of other players for changes
	for(int x = 0; x < 4; x++) {
		if(x != p) {	
			int y = testStateChange(x, &testg, g);
			if(y) 
				fcount++;
		}
	}

	//check that something was discarded
	if(testg.discardCount[p] <= g->discardCount[p])
		fcount++;//printf("TEST PASSED\n");

	//check that handcount is one more
	if(testg.handCount[p] != g->handCount[p]+1)
			fcount++;//	printf("TEST PASSED\n");

	//discard should have adventurer
	int found = 0;
	for(int x = 0; x < testg.discardCount[p]; x++) {
		if(testg.discard[p][x] == adventurer) 
			found = 1;
	}
	if(!found) 
		fcount++;
 
	return fcount;
}

int main(int argc, char** argv) {
        struct gameState g;
        //int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
          // sea_hag, feast, smithy, council_room};
        int p, n, i;//, deckCount, discardCount, handCount;
	int temphand[MAX_HAND];
	int t[] = {gold, gold, gold};
	int tCount;
        SelectStream(2);
        PutSeed(3);
	int min = 5;
	int total = 0;
        printf("********Testing adventurer********\n");
        for (n = 0; n < 2000; n++) {
                for (i = 0; i < sizeof(struct gameState); i++) {
                        ((char*)&g)[i] = floor(Random() * 256);
                }
		g.numPlayers = MAX_PLAYERS;
		int deck, hand, discard = 0;
		deck = floor(Random() * ((MAX_DECK-min)+1)+min);
		hand = floor(Random() * ((MAX_HAND-min) + 1) + min);

		//fill up every players hand, deck, and discard count so we can compare
		//changes to other players states after calling card effect
		for(int y = 0; y < g.numPlayers; y++) {	
			g.handCount[y] = hand;
			g.deckCount[y] = deck;	
			g.discardCount[y] = discard;
		}
		
		//pick random player 
                p = floor(Random() * MAX_PLAYERS);
		g.whoseTurn = p;
        	tCount = floor(Random() * ((g.deckCount[p] - min) + 1) + min);

		//ensure at least a couple treasure cards or will not find any when drawing
                for (int x = 0; x < tCount; x++) {
			int coin = floor(Random() * 3);
			//printf("coin: %d\n", coin);
			g.deck[p][x] = t[coin];
		}

		//add total number of failures from this turn to counter	
                total += testAdventurer(p, &g, temphand);
        }
        printf ("Total failures: %d\n", total);
}

