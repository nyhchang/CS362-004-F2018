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
    currentHandCount = g1.handCount[currentPlayer];
    g1.hand[currentPlayer][0] = smithy;
    currentHandCount = g1.handCount[currentPlayer];
    cardEffect(smithy, 0, 0, 0, &g1, 0, 0);
    newHandCount = g1.handCount[currentPlayer];
    if (asserttrue(currentHandCount, (newHandCount + 3)) == 0)
    printf("Smithy Card: PASS. Added 2 cards total to hand (draw 3 discard 1) \n");
    else
    printf("Smithy Card: FAIL. Added %d cards total to hand \n", (newHandCount - currentHandCount));

    if (asserttrue(currentPlayer, whoseTurn(&g1)) == 0)
    printf("Smithy Card: PASS. Still the first player's turn. \n");
    else
    printf("Smithy Card: FAIL. Not the first player's turn. \n");
  }
}