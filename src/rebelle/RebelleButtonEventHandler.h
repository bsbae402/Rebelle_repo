/*	
	RebelleButtonEventHandler.h
	edit: team Lawless

	>Based on: BugsButtonEventHandler.h
	>Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	

	This is a custom button event handler. Each game can choose
	to use different buttons and respond differently to when
	buttons are pressed. This class will handle button presses for
	the BugsGame following the ButtonEventHandler pattern.
*/

#pragma once
#include "rebelle_VS\stdafx.h"
#include "mg\input\ButtonEventHandler.h"

class Game;

const wstring	GO_TO_MM_COMMAND = L"Go To Main Menu";
const wstring	START_COMMAND = L"Start";
const wstring	EXIT_COMMAND = L"Exit";
const wstring	CONTROLS_COMMAND = L"Controls";

//// pause game menu button commands
const wstring	RESUME_COMMAND = L"Resume";
const wstring	PAUSE_MENU_EXIT_COMMAND = L"Exit in Pause Menu";
const wstring	SHOW_UPGRADE_COMMAND = L"Show Upgrade";
const wstring	DONATE_MONEY_COMMAND = L"Donate Money";

//// upgrade screen button commands
const wstring	BACK_TO_PAUSE_MENU_COMMAND = L"Back To Pause Menu";
const wstring	SPEED_UPGRADE_COMMAND = L"Speed Upgrade";
const wstring	ATTACK_UPGRADE_COMMAND = L"Attack Upgrade";
const wstring	DEFENSE_UPGRADE_COMMAND = L"Defense Upgrade";

//// LEVEL COMPLETE screen button command
const wstring	GO_TO_NEXT_LEVEL_COMMAND = L"Go To Next Level";

//// [credits screen -> main menu] command
const wstring	CREDITS_TO_MM_COMMAND = L"From Credits Screen To Main Menu";

class RebelleButtonEventHandler: public ButtonEventHandler
{
public:
	// AS-IS, THIS CLASS HAS NO DATA, SO THERE IS NOTHING
	// TO INITIALIZE OR DESTROY
	RebelleButtonEventHandler()	{}
	~RebelleButtonEventHandler()	{}

	void handleButtonEvents(wstring command);
};