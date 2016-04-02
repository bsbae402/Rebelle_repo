/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugsButtonEventHandler.cpp

	See BugsButtonEventHandler.h for a class description.
*/

#include "rebelle_VS\stdafx.h"
#include "rebelle\RebelleApp.h"
#include "rebelle\RebelleButtonEventHandler.h"
#include "mg\game\Game.h"
#include "mg\gsm\state\GameStateManager.h"

void RebelleButtonEventHandler::handleButtonEvents(	wstring command)
{
	Game *game = Game::getSingleton();

	// THE USER PRESSED THE Exit BUTTON ON THE MAIN MENU,
	// SO LET'S SHUTDOWN THE ENTIRE APPLICATION
	if (command.compare(EXIT_COMMAND) == 0)
	{
		game->exitApp();
	}
	// THE USER PRESSED THE MOUSE BUTTON ON THE SPLASH
	// SCREEN, SO LET'S GO TO THE MAIN MENU
	else if (command.compare(GO_TO_MM_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToMainMenu();
	}
	// THE USER PRESSED THE Start BUTTON ON THE MAIN MENU,
	// SO LET'S START THE GAME FROM THE FIRST LEVEL
	else if (command.compare(START_COMMAND) == 0)
	{
		//// game start is disabled currently
		//// game->startGame();
	}
	// THE USER PRESSED THE Quit BUTTON ON THE IN-GAME MENU,
	// SO LET'S UNLOAD THE LEVEL AND RETURN TO THE MAIN MENU
	//// we don't have quit
	/*else if (command.compare(QUIT_COMMAND) == 0)
	{
		game->quitGame();
	}*/

	//// controls clicked
	if (command.compare(CONTROLS_COMMAND) == 0)
	{
		//// TO BE added
	}
}