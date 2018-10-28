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

//test whoseTurn()
int main()
{
  struct gameState g1;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};
  initializeGame(2, k, 3, &g1);

  int currentPlayer = whoseTurn(&g1);
  if (asserttrue(currentPlayer, g1.whoseTurn) == 0)
    printf("whoseTurn(): PASS. Function call matches state \n");
  else
    printf("whoseTurn(): FAIL. whoseTurn() = %d, state.whoseTurn = %d. \n", currentPlayer, g1.whoseTurn);
  endTurn(&g1);
  int newCurrent = whoseTurn(&g1);
  if (asserttrue(currentPlayer, g1.whoseTurn) == 1)
    printf("whoseTurn(): PASS. New player's turn. Correctly follows state \n");
  else
    printf("whoseTurn(): FAIL. Does not follow state.. \n");
}
