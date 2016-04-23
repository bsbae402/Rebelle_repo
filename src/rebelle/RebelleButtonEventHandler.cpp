/*
	RebelleButtonEventHandler.cpp
	edit: team Lawless

	>Based on: BugsButtonEventHandler.cpp
	>Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	See RebelleButtonEventHandler.h for a class description.
*/

#include "rebelle_VS\stdafx.h"
#include "rebelle\RebelleApp.h"
#include "rebelle\RebelleButtonEventHandler.h"
#include "mg\game\Game.h"
#include "mg\gsm\state\GameStateManager.h"

void RebelleButtonEventHandler::handleButtonEvents(wstring command)
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
		game->startGame();
	}

	else if (command.compare(RESUME_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToGame();
	}

	//// --- following button commands are for pause menu
	/// user pressed the exit button in the pause menu
	else if (command.compare(PAUSE_MENU_EXIT_COMMAND) == 0)
	{
		game->quitGame();
	}
	/// user pressed show_upgrade button
	else if (command.compare(SHOW_UPGRADE_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToUpgradeScreen();
	}

	//// --- following button commands are for upgrade screen
	/// user pressed back_to_menu button
	else if (command.compare(BACK_TO_PAUSE_MENU_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToIngamePauseMenu();
	}
	
	//// controls clicked
	if (command.compare(CONTROLS_COMMAND) == 0)
	{
		//// TO BE added
	}

}