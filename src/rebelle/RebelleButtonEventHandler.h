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

class RebelleButtonEventHandler: public ButtonEventHandler
{
public:
	// AS-IS, THIS CLASS HAS NO DATA, SO THERE IS NOTHING
	// TO INITIALIZE OR DESTROY
	RebelleButtonEventHandler()	{}
	~RebelleButtonEventHandler()	{}

	void handleButtonEvents(wstring command);
};