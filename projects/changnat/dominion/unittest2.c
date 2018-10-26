#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//test kingdomCards()
int main() {
  int* deckOne = kingdomCards(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  int* deckTwo = kingdomCards(10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
  int i, j;
  int test1 = 0, test2 = 0, test3 = 0;

  for (i = 0; i < 10; i++)
  {
    if (&deckOne[i] == NULL)
    {
      printf("kingdomCards(): FAIL. Did not create card %d in deck one\n", i);
      test1 = 1;
      break;
    }
  }
  if(test1 == 0)
    printf("kingdomCards(): PASS. Created all cards in deck one\n");

  for (i = 0; i < 10; i++)
  {
    if (&deckTwo[i] == NULL)
    {
      printf("kingdomCards(): FAIL. Did not create card %d in deck two\n", i);
      test2 = 1;
      break;
    }
  }
  if (test2 == 0)
    printf("kingdomCards(): PASS. Created all cards in deck two\n");

  
  for (i = 0, j=9; i < 10; i++)
  {
    if (deckOne[i] != deckTwo[j])
    {
      printf("kingdomCards(): FAIL. Deck one does not match deck two \n");
      test3 = 1;
      break;
    }
    j--;
  }
  if(test3 == 0)
    printf("kingdomCards(): PASS. Cards in deck one match cards in deck two\n");
}