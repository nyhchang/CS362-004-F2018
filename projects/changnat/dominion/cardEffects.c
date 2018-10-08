#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

adventurerEffect(int *drawntreasure, struct gameState *state, int *currentPlayer, int *cardDrawn, ) {    
      while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawntreasure++;
	else{
	  temphand[z]=cardDrawn;
	  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	  z++;
	}
      }
      while(z-1>=0){
	state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	z=z-1;
      }
      return 0;
}

smithyEffect(struct gameState *state, int currentPlayer, int handPos) {
			int i;
	      //+3 Cards
      for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}

void villageEffect(struct gameState *state, int currentPlayer, int handPos){
	      //+1 Card
      drawCard(currentPlayer, state);
			
      //+2 Actions
      state->numActions = state->numActions + 2;
			
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
}


void cutpurseEffect(struct gameState *state, int currentPlayer){
			int i, j, k;
      updateCoins(currentPlayer, state, 2);
      for (i = 0; i < state->numPlayers; i++)
	{
	  if (i != currentPlayer)
	    {
	      for (j = 0; j < state->handCount[i]; j++)
		{
		  if (state->hand[i][j] == copper)
		    {
		      discardCard(j, i, state, 0);
		      break;
		    }
		  if (j == state->handCount[i])
		    {
		      for (k = 0; k < state->handCount[i]; k++)
			{
			  if (DEBUG)
			    printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
			}	
		      break;
		    }		
		}
					
	    }
				
	}
}		

void salvagerEffect(struct gameState *state, int currentPlayer, int handPos, int choice1){
	      //+1 buy
      state->numBuys++;
			
      if (choice1)
	{
	  //gain coins equal to trashed card
	  state->coins = state->coins + getCost( handCard(choice1, state) );
	  //trash card
	  discardCard(choice1, currentPlayer, state, 1);	
	}
			
      //discard card
      discardCard(handPos, currentPlayer, state, 0);
}