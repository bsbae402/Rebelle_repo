/*	
	RebelleKeyEventHandler.h
	edit: team Lawless
	
	>Based on: BugsKeyEventHandler.cpp
	>Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	This is a custom key event handler. Each game can choose
	to use different keyboard keys and respond differently to when
	they are pressed. This class will handle key presses for
	this particular game following the KeyEventHandler pattern.
*/

#pragma once
#include "rebelle_VS\stdafx.h"
#include "mg\input\KeyEventHandler.h"

class Game;

// USED FOR MOVEMENT AND OTHER KEYBOARD RESPONSES
const unsigned int W_KEY = (unsigned int)'W';
const unsigned int A_KEY = (unsigned int)'A';
const unsigned int S_KEY = (unsigned int)'S';
const unsigned int D_KEY = (unsigned int)'D';
const unsigned int P_KEY = (unsigned int)'P';
const unsigned int T_KEY = (unsigned int)'T';
const unsigned int L_KEY = (unsigned int)'L';
const unsigned int F_KEY = (unsigned int)'F';
const unsigned int U_KEY = (unsigned int)'U';
const unsigned int V_KEY = (unsigned int)'V';
const unsigned int G_KEY = (unsigned int)'G';
//// -- for partial physics activation
const unsigned int K_KEY = (unsigned int)'K';
//// -------- 
const unsigned int UP_KEY = VK_UP;
const unsigned int DOWN_KEY = VK_DOWN;
const unsigned int LEFT_KEY = VK_LEFT;
const unsigned int RIGHT_KEY = VK_RIGHT;
const unsigned int SPACE_KEY = VK_SPACE;

// THIS IS JUST FOR SHOWING HOW THE CURSOR CAN BE CHANGED
const unsigned int C_KEY = (unsigned int)'C';

class RebelleKeyEventHandler : public KeyEventHandler
{

public:
	RebelleKeyEventHandler()		{}
	~RebelleKeyEventHandler()		{}
	void handleKeyEvents();
	bool moveviewport = false;
};