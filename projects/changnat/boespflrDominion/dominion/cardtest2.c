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

//test smithy card

int main()
{
  struct gameState g1;
  int k[10] = {smithy, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, adventurer};
  initializeGame(2, k, 3, &g1);
  int currentPlayer = whoseTurn(&g1);
  g1.hand[currentPlayer][0] = smithy;
  int beforeCardHand = g1.handCount[currentPlayer];
  playCard(0, 0, 0, 0, &g1);
  int afterCardHand = g1.handCount[currentPlayer];

  if (asserttrue(afterCardHand, (beforeCardHand + 3)) == 0)
    printf("Smithy Card: PASS. Added 2 cards total to hand (draw 3 discard 1) \n");
  else
    printf("Smithy Card: FAIL. Added %d cards total to hand \n", (afterCardHand - beforeCardHand));
  if (asserttrue(currentPlayer, whoseTurn(&g1)) == 0)
    printf("Smithy Card: PASS. Still the first player's turn. \n");
  else
    printf("Smithy Card: FAIL. Not the first player's turn. \n");
}