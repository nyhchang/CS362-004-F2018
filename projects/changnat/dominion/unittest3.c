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

//test supplyCount()
int main ()
{
  struct gameState* g1;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  initializeGame(2, k, 3, g1);
  int silverCount = supplyCount(silver, g1);
  asserttrue(silverCount, 40);
  int goldCount = supplyCount(gold, g1);
  asserttrue(goldCount, 30);
  int copperCount = supplyCount(copper, g1);
  asserttrue(copperCount, 60-(7*2));

}
