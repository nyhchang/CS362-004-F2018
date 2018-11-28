/***********************************
 * Name: Robert Boespflug (boespflr)
 * CS362 - Assignment 4
 * Date: 11/14/2018
 * Desc: Random tester for smithy,
 * some code burrowed from testDrawCard.c and 
 * the initializeGame() funcion in dominion.c
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

int equal(int a, int b) {
  if (a == b)
    return 1;
  else 
    return 0;
}

int testSmithy(int p, struct gameState * G, int k[], int iter) {
	struct gameState testG;
	memcpy(&testG, G, sizeof(struct gameState));
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int failureCount = 0;

	//call cardeffect to call playSmithy
	cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);

	//test current player darws three cards
	if(testG.handCount[p] != (G->handCount[p])+3)
		failureCount++; //printf(" HandCount not +3 \n"); }

	//testing that no other players states are affected	
        for(int x = 0; x < 4; x++) {
                if(x != p) {
                        int y = testStateChange(x, &testG, G);
                        if(y)
                                failureCount++;
                }
        }

	//test kingdom cards unchanged
	int i;
	for(i = 0; i < 10; i++) {
		if(!equal(testG.supplyCount[k[i]], G->supplyCount[k[i]])) {
			failureCount++;	printf("Kingdom cards not same between states\n");	
		}
	}


	//testing victory cards unchanged
	if(testG.supplyCount[duchy] != G->supplyCount[duchy]) {
		failureCount++; printf("Victory Cards not same between states\n");
	} 

	return failureCount;	
}

int main(int argc, char** argv) {
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	   sea_hag, feast, smithy, council_room}; 
	int p, n, i;//, deckCount, discardCount, handCount;
	int totalFailureCount = 0;
	SelectStream(2);
	PutSeed(3);
	printf("********Testing smithy********\n");
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {      //from testDrawCard 
			((char*)&G)[i] = floor(Random() * 256);
		}	
		//randomly set up a turn with randlm values for 
		//the varaibles that might interact with the turn
		G.playedCardCount = floor(Random() * (MAX_DECK - 1)); //max_deck - 1, not every card can be played
                int deck = floor(Random() * (MAX_DECK));
                int hand =  floor(Random() * (MAX_HAND));
                int discard = floor(Random() * MAX_DECK);
		G.numPlayers = MAX_PLAYERS;
                for(int x = 0; x < G.numPlayers; x++) {		      //have every player have a hand
                        G.deckCount[x] = deck;			      //to test if their state changed at all
                        G.handCount[x] = hand;			      //when calling card on another player
                        G.discardCount[x] = discard;
                }
		G.supplyCount[duchy] = floor(Random() * 12);	      //adds random number of supply cards
		G.supplyCount[estate] = floor(Random() * 12);
		G.supplyCount[province] = floor(Random() * 12);
		p = floor(Random() * MAX_PLAYERS); 		      //pick a player from all the players
		G.whoseTurn = p;				      //make that player the current turn
		totalFailureCount += testSmithy(p, &G, k, n);
	}
	printf ("TOTAL NUMBER OF FAILURES: %d\n", totalFailureCount);
}
