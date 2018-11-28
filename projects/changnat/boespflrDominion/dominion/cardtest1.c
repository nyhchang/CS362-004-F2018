#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int asserttrue(int a, int b)
{
  if (a == b)
    return 0;
  else
    return 1;
}

//test adventurer card
int main()
{
  struct gameState g1;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 3, &g1);
  int currentPlayer = whoseTurn(&g1);
  g1.hand[currentPlayer][0] = adventurer;
  int currentHandCount = g1.handCount[currentPlayer];
  playCard(0, 0, 0, 0, &g1);
  int newHandCount = g1.handCount[currentPlayer];
  if (asserttrue(currentHandCount, (newHandCount - 2)) == 0)
    printf("Adventurer Card: PASS. Added 2 cards to hand. \n");
  else
    printf("Adventurer Card: FAIL. Added %d cards to hand. \n", (newHandCount - currentHandCount));

  if (asserttrue(currentPlayer, whoseTurn(&g1)) == 0)
    printf("Adventurer Card: PASS. Still the first player's turn. \n");
  else
    printf("Adventurer Card: FAIL. Not the first player's turn. \n");
}