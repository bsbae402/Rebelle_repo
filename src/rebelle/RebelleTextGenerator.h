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
#include "mg\text\GameText.h"

static const int IDX_TEXT_NOT_REGISTERED = -1;

class RebelleTextGenerator : public TextGenerator
{
private:
	bool toolbarTextRegistrationDone = false;
	bool upgradeTextRegistrationDone = false;
	bool donateTextRegistrationDone = false;

	// THIS IS THE TEXT THIS OBJECT WILL UPDATE EACH FRAME
	wstring scorelabel;
	RenderText *scorelabelRT;

	wstring moneylabel;
	RenderText *moneylabelRT;

	wstring healthlabel;
	RenderText *healthlabelRT;

	wstring heallabel;
	RenderText *heallabelRT;

	wstring safetywarning;
	RenderText *safetywarningRT;

	wstring safetykey;
	RenderText *safetykeyRT;

	wstring additional;
	RenderText *additionalRT;

	wstring upgrades;
	RenderText *upgradesRT;

	wstring upgrademoney;
	RenderText *upgrademoneyRT;

	wstring donatemoney;
	RenderText *donatemoneyRT;

	wstring donatescore;
	RenderText *donatescoreRT;

	// THESE ARE HELPER METHODS FOR GENERATING THE TEXT, CALLED
	// EACH FRAME BY updateText
	void printTime();
	void printSafety();
	void printHealth();
	void printScore();
	void printMoney();
	void printHeal();
	void printUpgrades();
	void printUpgrademoney();
	void printDonatemoney();
	void printDonateScore();

public:
	// NOTHING TO INITIALIZE OR DESTROY
	RebelleTextGenerator()		{}
	~RebelleTextGenerator()	{}

	void startUp();
	void update();
	void setdebug(wstring newdebug);
	void setTime(int time);
	void setHeal(wstring heal);
};