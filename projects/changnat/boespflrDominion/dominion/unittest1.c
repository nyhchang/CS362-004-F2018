#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int compare(const int* a, const int* b);

int asserttrue(int a, int b)
{
  if (a == b)
    return 0;
  else
    return 1;
}

//testing compare()
int main()
{
  int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int l[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


  int test1 = compare(&k[9], &k[9]);
  if(asserttrue(test1, 0) != 0)
    printf("Compare(): FAIL. Both const equal check \n");
  else{
      printf("Compare(): PASS. Both const equal \n");
      int test2 = compare(&k[9], &l[8]);
      if(asserttrue(test2, 1) != 0)
        printf("Compare(): FAIL. First const greater than 2nd check \n");
      else{
          printf("Compare(): PASS. First const greater than 2nd \n");
          int test3 = compare(&l[8], &k[9]);
          if(asserttrue(test3, -1) != 0)
            printf("Compare() test failed, First const less than 2nd check \n");
          else

            printf("Compare(): PASS. First const less than 2nd \n");
      }
  }
}