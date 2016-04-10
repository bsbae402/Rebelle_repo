/*	
	RebelleTextGenerator.cpp
	edit: team Lawless

	>based on: BugsTextGenerator.cpp
	>Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	This class is a custom text generator for the EmptyGame
	application. Basically, by defining the initText and updateText
	methods, we can have it display whatever text we like.
*/

#pragma once
#include "rebelle_VS\stdafx.h"
#include "mg\text\TextGenerator.h"

class RebelleTextGenerator : public TextGenerator
{
private:
	// THIS IS THE TEXT THIS OBJECT WILL UPDATE EACH FRAME
	wstring scorelabel;
	wstring moneylabel;
	wstring healthlabel;
	wstring safetywarning;
	wstring safetykey;

	wstring additional;

	// THESE ARE HELPER METHODS FOR GENERATING THE TEXT, CALLED
	// EACH FRAME BY updateText

	

	void printTime();
	void printSafety();
	void printHealth();
	void printScore();
	void printMoney();
	

public:
	// NOTHING TO INITIALIZE OR DESTROY
	RebelleTextGenerator()		{}
	~RebelleTextGenerator()	{}

	void startUp();
	void update();
	void setdebug(wstring newdebug);
	void setTime(int time);

};