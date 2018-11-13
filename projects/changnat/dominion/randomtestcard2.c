#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

int asserttrue(int a, int b)
{
  if (a == b)
    return 0;
  else
    return 1;
}



int main()
{
  int i, m, currentHandCount, newHandCount;
  struct gameState g1;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};
  int seed = time(NULL);
  srand(seed);
  for(i = 0; i < 1000; i++){ //1000 runs
    //initialize 2 to 4 player game
    int numPlayers = rand()%4+2;
    initializeGame(numPlayers, k, seed, &g1);
    int currentPlayer = whoseTurn(&g1);
    //move cards around, make sure supply isnt always in same spot.
    shuffle(currentPlayer, &g1); 
    //make hand size vary, discard 1 to 3 cards
    for (m = 1; m < (rand()%3+1); m++){
      discardCard(1, currentPlayer, &g1, 0);
    }
    //set starting numactions between 1 and 6
    g1.numActions = rand()%6+1;
    currentHandCount = g1.handCount[currentPlayer];
    g1.hand[currentPlayer][0] = village;
    int beforeCardHand = g1.handCount[currentPlayer];
    int currentActionCount = g1.numActions;
    cardEffect(village, 0, 0, 0, &g1, 0, 0);
    int afterCardHand = g1.handCount[currentPlayer];
    int afterActionCount = g1.numActions;
    if (asserttrue(afterCardHand, beforeCardHand) == 0)
      printf("Village Card: PASS. Added one card to hand and discarded one card \n");
    else
      printf("Village Card: FAIL. handCount change: %d\n", (afterCardHand - beforeCardHand));

    if (asserttrue(afterActionCount, currentActionCount + 2))
      printf("Village Card: PASS. Added 2 actions to play \n");
    else
      printf("Village Card: FAIL. numActions change: %d\n", (afterActionCount - currentActionCount));
    }
}