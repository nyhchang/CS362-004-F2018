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

//test village card

int main()
{
  struct gameState g1;
  int k[10] = {smithy, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, adventurer};
  initializeGame(2, k, 3, &g1);
  int currentPlayer = whoseTurn(&g1);
  g1.hand[currentPlayer][0] = village;
  int beforeCardHand = g1.handCount[currentPlayer];
  int currentActionCount = g1.numActions;
  playCard(0, 0, 0, 0, &g1);
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