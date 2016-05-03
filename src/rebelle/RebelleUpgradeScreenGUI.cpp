/*
	create: Bongsung Bae
	2016/04/23
*/

#include "mg_VS\stdafx.h"
#include "mg\game\Game.h"
#include "mg\gsm\state\GameStateManager.h"
#include "mg\gsm\sprite\SpriteManager.h"
#include "mg\graphics\GameGraphics.h"
#include "mg\graphics\TextureManager.h"
#include "mg\gui\OverlayImage.h"

#include "rebelle\RebelleUpgradeScreenGUI.h"
#include "rebelle\RebelleApp.h"


RebelleUpgradeScreenGUI::RebelleUpgradeScreenGUI()
{
}


RebelleUpgradeScreenGUI::~RebelleUpgradeScreenGUI()
{
}

void RebelleUpgradeScreenGUI::initialize(unsigned int initScreenX, unsigned int initScreenY,
	unsigned int initStatListX, unsigned int initStatListY,
	unsigned int initYdistBetweenStats,
	unsigned int initStatLineHeight,
	unsigned int initStatTitleWidth,
	unsigned int initUpgradeButtonWidth)
{
	screenX = initScreenX;
	screenY = initScreenY;
	statListX = initStatListX;
	statListY = initStatListY;
	ydistBetweenStats = initYdistBetweenStats;
	statLineHeight = initStatLineHeight;
	statTitleWidth = initStatTitleWidth;
	upgradeButtonWidth = initUpgradeButtonWidth;
}

void RebelleUpgradeScreenGUI::loadPlayerStats()
{
	Game* game = Game::getSingleton();
	GameStateManager* gsm = game->getGSM();
	SpriteManager* spriteMgr = gsm->getSpriteManager();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	PlayerSprite *player = spriteMgr->getPlayer();
	int speed = player->getSpeed();
	int attack = player->getAttack();
	int defense = player->getDefense();
	unsigned int speedIconTID = guiTextureManager->loadTexture(SPEED_ICON_PATH);
	unsigned int attackIconTID = guiTextureManager->loadTexture(ATTACK_ICON_PATH);
	unsigned int defenseIconTID = guiTextureManager->loadTexture(DEFENSE_ICON_PATH);

	//// - first speed icon will be rendered at 20px right to upgrade button
	int speedIconY = statListY + statLineHeight + ydistBetweenStats;
	int nextSpeedIconX = statListX + statTitleWidth + statTitleWidth + upgradeButtonWidth + 20;
	for (int i = 0; i < speed; i++)
	{
		OverlayImage *speedIcon = new OverlayImage();
		speedIcon->alpha = 255;
		speedIcon->width = STAT_ICON_WIDTH;
		speedIcon->height = STAT_ICON_HEIGHT;
		speedIcon->x = nextSpeedIconX;
		speedIcon->y = speedIconY;
		speedIcon->z = 0;
		speedIcon->imageID = speedIconTID;

		this->addOverlayImage(speedIcon);
		nextSpeedIconX += STAT_ICON_WIDTH + 3;
	}

	//// attack icons should be next to Attack stat title and the button.
	int attackIconY = speedIconY + statLineHeight + ydistBetweenStats;
	int nextAttackIconX = statListX + statTitleWidth + statTitleWidth + upgradeButtonWidth + 20;
	for (int i = 0; i < attack; i++)
	{
		OverlayImage *attackIcon = new OverlayImage();
		attackIcon->alpha = 255;
		attackIcon->width = STAT_ICON_WIDTH;
		attackIcon->height = STAT_ICON_HEIGHT;
		attackIcon->x = nextAttackIconX;
		attackIcon->y = attackIconY;
		attackIcon->z = 0;
		attackIcon->imageID = attackIconTID;

		this->addOverlayImage(attackIcon);
		nextAttackIconX += STAT_ICON_WIDTH + 3;
	}

	//// defense icons
	int defenseIconY = attackIconY + statLineHeight + ydistBetweenStats;
	int nextDefenseIconX = statListX + statTitleWidth + statTitleWidth + upgradeButtonWidth + 20;
	for (int i = 0; i < attack; i++)
	{
		OverlayImage *defenseIcon = new OverlayImage();
		defenseIcon->alpha = 255;
		defenseIcon->width = STAT_ICON_WIDTH;
		defenseIcon->height = STAT_ICON_HEIGHT;
		defenseIcon->x = nextDefenseIconX;
		defenseIcon->y = defenseIconY;
		defenseIcon->z = 0;
		defenseIcon->imageID = defenseIconTID;

		this->addOverlayImage(defenseIcon);
		nextDefenseIconX += STAT_ICON_WIDTH + 3;
	}
}

void RebelleUpgradeScreenGUI::reloadPlayerStats()
{
}

void RebelleUpgradeScreenGUI::unloadPlayerStats()
{
	Game* game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	unsigned int speedIconTID = guiTextureManager->loadTexture(SPEED_ICON_PATH);
	unsigned int attackIconTID = guiTextureManager->loadTexture(ATTACK_ICON_PATH);
	unsigned int defenseIconTID = guiTextureManager->loadTexture(DEFENSE_ICON_PATH);

	list<OverlayImage*>* overlayImageList = this->getOverlayImageList();

	list<OverlayImage*>::iterator it = overlayImageList->begin();
	while (it != overlayImageList->end())
	{
		OverlayImage* image = *it;
		it++;

		if (image->imageID == speedIconTID
			|| image->imageID == attackIconTID
			|| image->imageID == defenseIconTID)
		{
			overlayImageList->remove(image);
			delete image;
		}
	}
}
