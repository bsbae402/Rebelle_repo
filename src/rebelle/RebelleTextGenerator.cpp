/*
	RebelleTextGenerator.cpp
	edit: team Lawless

	>based on: BugsTextGenerator.cpp
	>Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	
	See RebelleTextGenerator.h for a class description.
*/

#include "mg_VS\stdafx.h"
#include "rebelle\RebelleApp.h"
#include "rebelle\RebelleTextGenerator.h"
#include "mg\clock\GameClock.h"
#include "mg\game\Game.h"
#include "mg\game\GameTypes.h"
#include "mg\graphics\GameGraphics.h"
#include "mg\gsm\ai\Bot.h"
#include "mg\gsm\ai\BotRecycler.h"
#include "mg\gsm\sprite\SpriteManager.h"
#include "mg\text\GameText.h"
#include "mg\platforms\Windows\WindowsInput.h"

static const int		LEFT_TEXT_X = 50;
static const int		RIGHT_TEXT_X = 750;
static const int		TEXT_Y = 20;
static const wstring	NEW_LINE_TEXT = L"\n";
static const wstring	MOUSE_COORDS_TEXT = L"Mouse: ";
static const wstring	TARGET_FPS_TEXT = L"Target FPS: ";
static const wstring	SLEEPLESS_FPS_TEXT = L"Sleepless FPS: ";
static const wstring	DELTA_TIME_TEXT = L"Delta Time: ";
static const wstring	BOT_COUNT_TEXT = L"Bot Count: ";
static const wstring	BOT_RECYCLER_TEXT = L"Bot Recycler Stats";
static const wstring	RECYCLABLE_BOTS_TEXT = L"-Recyclable Bots: ";

wstring addedtext(L"");
int timetoprint;


void RebelleTextGenerator::printTime()
{
	Game *game = Game::getSingleton();
	GameClock *clock = game->getClock();
	if (timetoprint/40 <= 5 && timetoprint != NULL)
	{
		Game *game = Game::getSingleton();

		wstringstream wss;
		SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
		safetywarning.append(L"Safety Key Changing in: ");
		wss << timetoprint/40;
		wss << NEW_LINE_TEXT;
		safetywarning.append(wss.str());
	}
	else
	{
		safetywarning.append(L"");
	}
}

void RebelleTextGenerator::printSafety()
{
	Game *game = Game::getSingleton();

	wstringstream wss;
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	safetykey.append(L"Safety Key: ");
	wss << game->getGSM()->getKey();
		
	safetykey.append(wss.str());
}

void RebelleTextGenerator::printHealth()
{
	Game *game = Game::getSingleton();

	wstringstream wss;
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	healthlabel.append(L"Health: ");
	wss << L"?";
	wss << L" / 15";


	healthlabel.append(wss.str());
}

void RebelleTextGenerator::printScore()
{
	Game *game = Game::getSingleton();

	wstringstream wss;
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	scorelabel.append(L"Score: ");
	//wss << L"?";
	//wss << L" / 15";


	//healthlabel.append(wss.str());
}

void RebelleTextGenerator::printMoney()
{
	Game *game = Game::getSingleton();

	wstringstream wss;
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	moneylabel.append(L"Money: ");
	//wss << L"?";
	//wss << L" / 15";


	//healthlabel.append(wss.str());
}

/*
	startUp - Provides an example of how to render text to our screen every frame,
	allowing for the text to continually change. This method adds a text object
	to the text manager (GameText), which allows it to be updated each frame. This
	method should be called only once for each object.
*/
void RebelleTextGenerator::startUp()
{
	// FIRST REGISTER THIS GENERATOR WITH GameText
	Game *game = Game::getSingleton();
	GameText *text = game->getText();
	text->setTextGenerator((TextGenerator*)this);

	// THEN GENERATE THE INITIAL TEXT TO DISPLAY
	//appendMouseCoords();
	//appendClock();
	//appendBotCount();
	//appendBotRecycler();
	//printTime();
	

	// AND THEN ADD IT TO THE TEXT MANAGER, SPECIFYING WHERE IT SHOULD BE RENDERED
	//text->addRenderText(&leftTextToGenerate, LEFT_TEXT_X, TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	//text->addRenderText(&rightTextToGenerate, RIGHT_TEXT_X, TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
}

/*
	updateText - updates the text. Note that the text must already have been added
	to the text manager via the initText method. Also not that there should be a
	separate TextGenerator for each line of text we wish to render.
*/
void RebelleTextGenerator::update()
{
	// THE TEXT MANAGER (GameText) HAS A POINTER TO OUR TEXT, SO WE CAN
	// SIMPLY CLEAR IT OUT OF OLD CHARACTER DATA AND FILL IT IN WITH
	// WHAT WE WANT.
	scorelabel.clear();
	moneylabel.clear();
	healthlabel.clear();
	safetywarning.clear();
	safetykey.clear();

	Game *game = Game::getSingleton();
	if (game->getGSM()->isGameInProgress())
	{


		//appendMouseCoords();
		//appendClock();
		//appendBotCount();
		//appendBotRecycler();
		printTime();
		printSafety();
		printHealth();
		printMoney();
		printScore();

		additional.clear();

		Game *game = Game::getSingleton();
		GameText *text = game->getText();

		wstringstream wss2;
		wss2 << addedtext;

		//wss << L"fff\n";
		additional.append(wss2.str());

		text->addRenderText(&scorelabel, LEFT_TEXT_X, TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
		text->addRenderText(&moneylabel, 200, TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
		text->addRenderText(&healthlabel, LEFT_TEXT_X, 50, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());

		text->addRenderText(&safetywarning, RIGHT_TEXT_X, TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
		text->addRenderText(&safetykey, RIGHT_TEXT_X, 50, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());

		text->addRenderText(&additional, 700, 10, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	}
}

void RebelleTextGenerator::setdebug(wstring newdebug)
{
	addedtext = newdebug;

}

void RebelleTextGenerator::setTime(int newtime)
{
	timetoprint = newtime;
	printTime();
}
