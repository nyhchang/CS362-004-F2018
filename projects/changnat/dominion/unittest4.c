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
int main ()
{
  struct gameState* g1;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  initializeGame(2, k, 3, g1);

  int currentPlayer = whoseTurn(g1);
  if(asserttrue(currentPlayer, 0))
    printf("whoseTurn(): PASS. Player 1 goes first. \n");
  else
    printf("whoseTurn(): FAIL. Player 1 does not go first. \n");
  endTurn(g1);
  int newCurrent = whoseTurn(g1);
  if(asserttrue(newCurrent, 1));
    printf("whoseTurn(): PASS. Player 2 goes after player 1. \n");
  else
    printf("whoseTurn(): FAIL. Player 2 does not go after player 1. \n");
  endTurn(g1);
  if(asserttrue(currentPlayer, whoseTurn(g1)))
    printf("whoseTurn(): PASS. Player 1 goes again after Player 2");
  else
    printf("whoseTurn():FAIL. Player 1 does not go again after player 2")
}
