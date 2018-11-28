#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int testStateChange(int player, struct gameState * testG, struct gameState * G) {
	int failed = 0;
	//if(testG->playedCardCount != G->playedCardCount) failed = 1;
	if(testG->whoseTurn != G->whoseTurn){ failed = 1;}
	if(testG->handCount[player] != G->handCount[player]) { failed = 1;}
	if(testG->discardCount[player] != G->discardCount[player]) {failed = 1;}
	if(testG->deckCount[player] != G->deckCount[player]) { failed = 1;}
	//if(testG->playedCards[player] != G->playedCards[player]) failed = 1;
	return failed;
}
