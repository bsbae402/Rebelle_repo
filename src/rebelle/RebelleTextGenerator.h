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
#include "mg\text\TextGenerator.h"

class RebelleTextGenerator : public TextGenerator
{
private:
	// THIS IS THE TEXT THIS OBJECT WILL UPDATE EACH FRAME
	wstring leftTextToGenerate;
	wstring rightTextToGenerate;

	// THESE ARE HELPER METHODS FOR GENERATING THE TEXT, CALLED
	// EACH FRAME BY updateText

	// FOR THE LEFT COLUMN
	void appendMouseCoords();
	void appendClock();
	void appendBotCount();

	// AND THE RIGHT COLUMN
	void appendBotRecycler();

public:
	// NOTHING TO INITIALIZE OR DESTROY
	RebelleTextGenerator()		{}
	~RebelleTextGenerator()	{}

	void startUp();
	void update();

	//// following methods are defined virtual in the TextGenerator (parent) class
	//// so we need to define them anyway. If not, there will be compile error.
	void setdebug(wstring newdebug) {}
	void setTime(int time) {}
};