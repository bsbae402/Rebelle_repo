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
//// -- Bongsung
#include "rebelle\RebelleUpgradeScreenGUI.h"

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

		//// --- I need to put codes that load upgrade icons here
		GameGUI *gui = game->getGUI();
		ScreenGUI* baseTypeUSGUI = gui->getScreen(GS_UPGRADE_SCREEN);
		RebelleUpgradeScreenGUI *upgradeScreenGUI = static_cast<RebelleUpgradeScreenGUI*>(baseTypeUSGUI);
		upgradeScreenGUI->loadPlayerStats();
	}

	//// --- following button commands are for upgrade screen
	/// user pressed back_to_menu button in the upgrade screen
	else if (command.compare(BACK_TO_PAUSE_MENU_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToIngamePauseMenu();
		
		//// --- I need to unload the upgrade icons here
		GameGUI *gui = game->getGUI();
		ScreenGUI* baseTypeUSGUI = gui->getScreen(GS_UPGRADE_SCREEN);
		RebelleUpgradeScreenGUI *upgradeScreenGUI = static_cast<RebelleUpgradeScreenGUI*>(baseTypeUSGUI);
		upgradeScreenGUI->unloadPlayerStats();
	}

	//// GO_TO_NEXT_LEVEL_COMMAND will be triggered when player
	//// click the resume button on the level complete screen
	else if (command.compare(GO_TO_NEXT_LEVEL_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->unloadCurrentLevel();

		GameGraphics *graphics = game->getGraphics();
		graphics->clearWorldTextures();

		gsm->goToLoadLevel();
	}

	else if (command.compare(DONATE_MONEY_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToDonateScreen();

		//// --- I need to unload the upgrade icons here
		/*GameGUI *gui = game->getGUI();
		ScreenGUI* baseTypeUSGUI = gui->getScreen(GS_DONATE_SCREEN);
		RebelleUpgradeScreenGUI *upgradeScreenGUI = static_cast<RebelleUpgradeScreenGUI*>(baseTypeUSGUI);
		upgradeScreenGUI->unloadPlayerStats();*/
	}
	else if (command.compare(L"increase donate") == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->setDonateMoney(gsm->getDonateMoney() + 100);
		if (gsm->getDonateMoney() > gsm->getMoney())
			gsm->setDonateMoney(gsm->getMoney());
		gsm->getDonateMoney();

	}
	else if (command.compare(L"decrease donate") == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->setDonateMoney(gsm->getDonateMoney() - 100);
		if (gsm->getDonateMoney() < 0)
			gsm->setDonateMoney(0);
	}
	else if (command.compare(L"donate") == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->setScore(gsm->getScore() + gsm->getDonateMoney() * 10);
		gsm->setMoney(gsm->getMoney() - gsm->getDonateMoney());
		gsm->setDonateMoney(0);
	}

	else if (command.compare(SPEED_UPGRADE_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		
		if (gsm->getMoney() >= 200)
		{
			gsm->setMoney(gsm->getMoney() - 200);
			gsm->addUpgrade(L"SPEED");
		}
		

	}
	else if (command.compare(ATTACK_UPGRADE_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		if (gsm->getMoney() >= 200)
		{
			gsm->setMoney(gsm->getMoney() - 200);
			gsm->addUpgrade(L"ATTACK");
		}
	}
	else if (command.compare(DEFENSE_UPGRADE_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		if (gsm->getMoney() >= 200)
		{
			gsm->setMoney(gsm->getMoney() - 200);
			gsm->addUpgrade(L"DEFENSE");
		}
	}
	
	//// controls clicked
	else if (command.compare(CONTROLS_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToControlsMenu();
	}

}