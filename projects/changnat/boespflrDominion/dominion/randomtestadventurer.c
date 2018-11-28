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

  for(i = 0; i < 50; i++){ //50 runs
    //initialize 2 to 4 player game
    int numPlayers = rand()%4+2;
    initializeGame(numPlayers, k, seed, &g1);
    printf("game init\n");
    int currentPlayer = whoseTurn(&g1);

    //move cards around, make sure supply isnt always in same spot.
    shuffle(currentPlayer, &g1); 

    //make hand size vary, discard 1 to 3 cards
    // for (m = 1; m < (rand()%3+1); m++){
    //   discardCard(1, currentPlayer, &g1, 0);
    // }

    //make adventurer first card in players hand
    g1.hand[currentPlayer][0] = adventurer;

    //track hand count before and after card is played
    currentHandCount = g1.handCount[currentPlayer];
    cardEffect(adventurer, 0, 0, 0, &g1, 0, 0);
    newHandCount = g1.handCount[currentPlayer];
    printf("cardplayed\n");

    //test
    if (asserttrue(currentHandCount, (newHandCount - 2)) == 0)
    printf("Adventurer Card: PASS. Added 2 cards to hand. \n");
    else
    printf("Adventurer Card: FAIL. Added %d cards to hand. \n", (newHandCount - currentHandCount));

    if (asserttrue(currentPlayer, whoseTurn(&g1)) == 0)
    printf("Adventurer Card: PASS. Still the first player's turn. \n");
    else
    printf("Adventurer Card: FAIL. Not the first player's turn. \n");
  }
}