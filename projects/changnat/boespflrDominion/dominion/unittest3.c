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
int main()
{
  struct gameState g1;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 3, &g1);
  int silverCount = supplyCount(silver, &g1);
  if ((asserttrue(silverCount, 40) == 0))
    printf("supplyCount(): PASS. Proper silver count (40). \n");
  else
    printf("supplyCount(): FAIL. Improper silver count (%d). \n", silverCount);
  int goldCount = supplyCount(gold, &g1);
  if (asserttrue(goldCount, 30) == 0)
    printf("supplyCount(): PASS. Proper gold count (30). \n");
  else
    printf("supplyCount(): FAIL. Improper gold count (%d). \n", goldCount);
  int copperCount = supplyCount(copper, &g1);
  if (asserttrue(copperCount, 60 - (7 * 2)) == 0)
    printf("supplyCount(): PASS. Proper copper count (60-(7*playerCount)). \n");
  else
    printf("supplyCount(): FAIL. Improper copper count (%d). \n", copperCount);
  int estates = supplyCount(estate, &g1);
  int duchys = supplyCount(duchy, &g1);
  int provinces = supplyCount(province, &g1);
  if (asserttrue(estates, duchys) == 0 && asserttrue(duchys, provinces) == 0)
    printf("supplyCount(): PASS. Proper estate, duchy, and province count (8 for 2 player game). \n");
  else
    printf("supplyCount(): FAIL. Improper estate, duchy, and province count (%d, %d, and %d). \n", estates, duchys, provinces);
}
