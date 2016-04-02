#include "rebelle_VS\stdafx.h"
#include "rebelle\RebelleMouseEventHandler.h"
#include "mg\game\Game.h"
#include "mg\gsm\sprite\SpriteManager.h"
#include "mg\gsm\state\GameStateManager.h"
#include "mg\gui\Viewport.h"

void RebelleMouseEventHandler::handleMousePressEvent(int mouseX, int mouseY)
{
	Game *game = Game::getSingleton();
	if (game->getGSM()->isGameInProgress())
	{
		Viewport *viewport = game->getGUI()->getViewport();
		
		// DETERMINE WHERE ON THE MAP WE HAVE CLICKED
		int worldCoordinateX = mouseX + viewport->getViewportX();
		int worldCoordinateY = mouseY + viewport->getViewportY();

		// CHECK TO SEE IF THE USER HAS CLICKED ON A SPRITE
		GameStateManager *gsm = game->getGSM();
		SpriteManager *spriteManager = gsm->getSpriteManager();
		BotRecycler *botRecycler = spriteManager->getBotRecycler();
		list<Bot*>::iterator botIterator = spriteManager->getBotsIterator();
		list<Bot*>::iterator endBotIterator = spriteManager->getEndOfBotsIterator();
		bool found = false;
		while ((botIterator != endBotIterator) && !found)
		{
			Bot *bot = (*botIterator);
			PhysicalProperties *pp = bot->getPhysicalProperties();
			AnimatedSpriteType *ast = bot->getSpriteType();
			if (	(worldCoordinateX > pp->getX()) &&
					(worldCoordinateY > pp->getY()) &&
					(worldCoordinateX < (pp->getX() + ast->getTextureWidth())) &&
					(worldCoordinateY < (pp->getY() + ast->getTextureHeight()))) {
				// BOT FOUND THAT'S BEEN CLICKED ON
				bot->setBotState(BotState::DYING);
				//bot->setCurrentState(L"DYING");
				found = true;
			}
			botIterator++;
		}
	}
}

void RebelleMouseEventHandler::handleMouseMoveEvent(int mouseX, int mouseY)
{
	Game *game = Game::getSingleton();

	// DETERMINE WHAT THE PATHFINDING GRID CELL
	// IS THAT THE MOUSE CURRENTLY IS ABOVE
	if (game->getGSM()->isGameInProgress())
	{
		// IF YOU LIKE YOU COULD DO SOME MOUSE OVER DEBUGGING STUFF HERE
	}
}