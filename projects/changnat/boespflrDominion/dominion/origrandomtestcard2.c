/***********************************
 *Name: Robert Boespflug (boespflr)
 *CS362 - Assignment 4
 *Date: 11/14/2018
 *Desc: Random tester for council room,
 *some code burrowed from testDrawCard.c and
 *the initializeGame() funcion in dominion.c
 ********************************/


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

int testCouncilRoom(int p, struct gameState * state) {
	int bonus = 0;
	struct gameState test;
	memcpy(&test, state, sizeof(struct gameState));
	int fcount = 0;

	//call playCouncilRoom in cardeffect
	cardEffect(council_room, 0, 0, 0, &test, 0, &bonus);

	//testing player drew +4 cards
	if(test.handCount[p] == state->handCount[p]+4)
		fcount++;//printf("PASSED\n");
	
	//testing each other player drew a card
	for(int i = 0; i < 4; i++) {
		if(i != p){
			if(test.handCount[i] != state->handCount[i]+1)
				fcount++;//printf("PASSED\n");
		}
	}

	//test numbuys went up by one
	if(test.numBuys != state->numBuys + 1)
		fcount++;

	return fcount;
}

int main(int argc, char** argv) {
	struct gameState G;
	//int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	//   sea_hag, feast, smithy, council_room}; 
	int p, n, i;//, deckCount, discardCount, handCount;
	int totalFailures = 0;
	SelectStream(2);
	PutSeed(3);
	printf("********TESTING COUNCIL ROOM********\n");
	for (n = 0; n < 2000; n++) {
		//printf("ITER: %d\n", n);
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}	
		p = floor(Random() * MAX_PLAYERS);
		int deck = floor(Random() * (MAX_DECK));
		int hand =  floor(Random() * (MAX_HAND));
		int discard = floor(Random() * MAX_DECK);
		G.numPlayers = MAX_PLAYERS;
		
		//make every players deck, hand, and discard the same so we can compare
		for(int x = 0; x < G.numPlayers; x++) {
			G.deckCount[x] = deck;
			G.handCount[x] = hand;
			G.discardCount[x] = discard; 
		}
		G.playedCardCount = floor(Random() * (MAX_DECK - 1));

		//took this from initalizeGame() in dominon.c
		for(int i = 0; i < G.numPlayers; i++)
		{
			G.deckCount[i] = 0;
			for (int j = 0; j < 3; j++)
			{
			  G.deck[i][j] = estate;
			  G.deckCount[i]++;
			}
			for (int j = 3; j < 10; j++)
			{
			  G.deck[i][j] = copper;
			  G.deckCount[i]++;
			}
		}
		G.numBuys = 1;
		G.whoseTurn = p;
		totalFailures += testCouncilRoom(p, &G);
	}
	printf ("Total Failures: %d\n", totalFailures);
}
