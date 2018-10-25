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

//testing compare()
void main()
{
  int *k = 1;
  int *l = 2;
  int *m = 3;

  int test1 = compare(k, k);
  asserttrue(test1 == 0);
  int test2 = compare(k, l);
  asserttrue(test2 == -1);
  int test3 = compare(l, k);
  asserttrue(test3 == 1);

  printf("Compare() test complete");
}