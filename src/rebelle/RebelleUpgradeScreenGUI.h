#pragma once

#include "rebelle_VS\stdafx.h"
#include "mg\gui\ScreenGUI.h"

static const unsigned int STAT_ICON_WIDTH = 30;
static const unsigned int STAT_ICON_HEIGHT = 30;

class Game;

class RebelleUpgradeScreenGUI : public ScreenGUI
{
private:
	unsigned int screenX;
	unsigned int screenY;
	unsigned int statListX;
	unsigned int statListY;
	unsigned int ydistBetweenStats;
	unsigned int statLineHeight;
	unsigned int statTitleWidth;

	unsigned int upgradeButtonWidth;

public:
	RebelleUpgradeScreenGUI();
	~RebelleUpgradeScreenGUI();

	void initialize(unsigned int initScreenX, unsigned int initScreenY,
		unsigned int initStatListX, unsigned int initStatListY,
		unsigned int initYdistBetweenStats, 
		unsigned int initStatLineHeight,
		unsigned int initStatTitleWidth,
		unsigned int initUpgradeButtonWidth);

	unsigned int getScreenX() { return screenX; }
	unsigned int getScreenY() { return screenY; }
	unsigned int getStatTitleWidth() { return statTitleWidth; }
	unsigned int getStatLineHeight() { return statLineHeight; }
	unsigned int getYDistBetweenStats() { return ydistBetweenStats; }
	unsigned int getStatListX() { return statListX; }
	unsigned int getStatListY() { return statListY; }

	void loadPlayerStats();
	void reloadPlayerStats();
	void unloadPlayerStats();
};

