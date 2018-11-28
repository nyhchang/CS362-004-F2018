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

//test mine card

int main()
{
  struct gameState g1;
  int k[10] = {smithy, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, adventurer};
  initializeGame(2, k, 3, &g1);
  int currentPlayer = whoseTurn(&g1);
  g1.hand[currentPlayer][0] = mine;
  g1.hand[currentPlayer][1] = copper;
  int beforeCardHand = g1.handCount[currentPlayer];
  int currentCoinCount = g1.coins;
  playCard(0, 1, gold, 0, &g1);
  int afterCardHand = g1.handCount[currentPlayer];
  int afterCoinCount = g1.coins;

  if (asserttrue(afterCardHand, beforeCardHand - 1) == 0)
    printf("Mine Card: PASS. Added one card to hand and discarded one card \n");
  else
    printf("Mine Card: FAIL. handCount change: %d (should be -1)\n", (afterCardHand - beforeCardHand));

  if (asserttrue(afterCoinCount, currentCoinCount))
    printf("Mine Card: PASS. Coins remain unchanged \n");
  else
    printf("Mine Card: FAIL. coin change: %d\n", (afterCoinCount - currentCoinCount));

  if (asserttrue(currentPlayer, whoseTurn(&g1)) == 0)
    printf("Mine Card: PASS. Still the first player's turn. \n");
  else
    printf("Mine Card: FAIL. Not the first player's turn. \n");
}