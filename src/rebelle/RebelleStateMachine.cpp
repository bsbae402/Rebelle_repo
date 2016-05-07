#include "mg_VS\stdafx.h"
#include "rebelle\RebelleStateMachine.h"	/// edit back if problem occurs
#include "mg\game\Game.h"
#include "mg\gsm\state\GameStateManager.h"

void RebelleStateMachine::update()
{
	Game *game = Game::getSingleton();
	GameStateManager *gsm = game->getGSM();
	SpriteManager *spriteManager = gsm->getSpriteManager();

	// IS THE GAME GOING ON?
	if (gsm->isGameInProgress())
	{
		// ARE ALL THE BUGS DEAD?
		/*
		if (spriteManager->getNumberOfBots() == 0)
		{
			gsm->goToLoadLevel();
		}
		*/
	}
	else if (gsm->isPreGame())
	{
		gsm->goToLoadLevel();
	}
	else if (gsm->isGameLevelLoading())
	{
		/*
		// NOW WE NEED TO TRANSITION TO THE NEXT LEVEL
		// BUT NOTE WE'RE HARD CODING THIS IN THAT WE
		// KNOW HOW MANY LEVELS THERE ARE, WHICH ISN'T IDEAL
		if ((gsm->getCurrentLevelIndex() == 0) ||
			(gsm->getCurrentLevelIndex() == NO_LEVEL_LOADED))
		{
			// WE'LL GO ONTO LEVEL INDEX 1
			gsm->loadNextLevel();
			gsm->goToGame();
		}
		else
		{
			// WE ONLY HAVE 2 LEVELS SO WHEN WE FINISH
			// THE SECOND ONE JUST GO BACK TO THE MAIN MENU
			gsm->goToMainMenu();
		}
		*/
		////// the original Bugs code above
		////// supposes that the game has only two levels.
		//// Rebelle will have three or more levels.
		int numOfGameLevels = gsm->getNumLevels();
		if (numOfGameLevels <= 0)
		{
			gsm->goToMainMenu();
		}
		else {
			int currentLevelIndex = gsm->getCurrentLevelIndex();
			if (currentLevelIndex == NO_LEVEL_LOADED || currentLevelIndex < numOfGameLevels)
			{
				gsm->loadNextLevel();
				gsm->goToGame();
			}
		}	
	}
}