/*
	RebelleKeyEventHandler.cpp
	edit: team Lawless
	
	>Based on: BugsKeyEventHandler.cpp
	>Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	See RebelleKeyEventHandler.h for a class description.
*/

#include "rebelle_VS\stdafx.h"
#include "rebelle\RebelleApp.h"
#include "rebelle\RebelleKeyEventHandler.h"
#include "mg\clock\GameClock.h"
#include "mg\game\Game.h"
#include "mg\game\WStringTable.h"
#include "mg\graphics\GameGraphics.h"
#include "mg\gsm\physics\Physics.h"
#include "mg\gsm\physics\PhysicalProperties.h"
#include "mg\gsm\sprite\AnimatedSprite.h"
#include "mg\gsm\state\GameState.h"
#include "mg\gsm\state\GameStateManager.h"
#include "mg\gui\Cursor.h"
#include "mg\gui\GameGUI.h"
#include "mg\input\GameInput.h"


#include "rebelle\RebelleTextGenerator.h"
#include "mg\gsm\sprite\PlayerSprite.h"
#include "mg\gsm\world\World.h"

/*
	handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
	gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
	key states since the last frame, which can allow us to respond to key presses, including when keys
	are held down for multiple frames.
*/
void RebelleKeyEventHandler::handleKeyEvents()
{
	Game *game = Game::getSingleton();

	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	PlayerSprite *player = gsm->getSpriteManager()->getPlayer();
	///// PhysicalProperties *pp = player->getPhysicalProperties();
	Viewport *viewport = game->getGUI()->getViewport();
	TextGenerator *generator = game->getText()->getTextGenerator();
	
	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		//// --- PLAYER MOVEMENTS
		//// set player sprite's state according to the key input types
		// up key
		if (input->isKeyDown(VK_UP))
		{
			wstring wStrState(MG_PLAYER_ANIMATION_STATE_WALK_FRONT.begin(), MG_PLAYER_ANIMATION_STATE_WALK_FRONT.end());
			player->setCurrentState(wStrState);
			player->setPlayerState(ENUM_PLAYER_MOVING);
			player->setPlayerDirection(ENUM_PLAYER_DIRECTION_UP);
			player->setPlayerInputStorage(VK_UP);
		}
		// down key
		if (input->isKeyDown(VK_DOWN))
		{
			wstring wStrState(MG_PLAYER_ANIMATION_STATE_WALK_BACK.begin(), MG_PLAYER_ANIMATION_STATE_WALK_BACK.end());
			player->setCurrentState(wStrState);
			player->setPlayerState(ENUM_PLAYER_MOVING);
			player->setPlayerDirection(ENUM_PLAYER_DIRECTION_DOWN);
			player->setPlayerInputStorage(VK_DOWN);
		}
		// left key
		if (input->isKeyDown(VK_LEFT))
		{
			wstring wStrState(MG_PLAYER_ANIMATION_STATE_WALK_LEFT.begin(), MG_PLAYER_ANIMATION_STATE_WALK_LEFT.end());
			player->setCurrentState(wStrState);
			player->setPlayerState(ENUM_PLAYER_MOVING);
			player->setPlayerDirection(ENUM_PLAYER_DIRECTION_LEFT);
			player->setPlayerInputStorage(VK_LEFT);
		}
		// right key
		if (input->isKeyDown(VK_RIGHT))
		{
			wstring wStrState(MG_PLAYER_ANIMATION_STATE_WALK_RIGHT.begin(), MG_PLAYER_ANIMATION_STATE_WALK_RIGHT.end());
			player->setCurrentState(wStrState);
			player->setPlayerState(ENUM_PLAYER_MOVING);
			player->setPlayerDirection(ENUM_PLAYER_DIRECTION_RIGHT);
			player->setPlayerInputStorage(VK_RIGHT);
		}
		//// --- end ---

		if (input->isKeyDownForFirstTime(P_KEY))
		{
			gsm->getPhysics()->togglePhysics();
		}
		if (input->isKeyDownForFirstTime(T_KEY))
		{
			gsm->getPhysics()->activateForSingleUpdate();
		}
		
		if (moveviewport)
		{
			//// I'm changing this code because I want that the viewport location is
			//// decided depending on the player sprite's location
			/*
			bool viewportMoved = false;
			float viewportVx = 0.0f;
			float viewportVy = 0.0f;
			if (input->isKeyDown(UP_KEY))
			{
				viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
				viewportMoved = true;
			}
			if (input->isKeyDown(DOWN_KEY))
			{
				viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
				viewportMoved = true;
			}
			if (input->isKeyDown(LEFT_KEY))
			{
				viewportVx -= MAX_VIEWPORT_AXIS_VELOCITY;
				viewportMoved = true;
			}
			if (input->isKeyDown(RIGHT_KEY))
			{
				viewportVx += MAX_VIEWPORT_AXIS_VELOCITY;
				viewportMoved = true;
			}
			if (viewportMoved)
				viewport->moveViewport((int)floor(viewportVx + 0.5f), (int)floor(viewportVy + 0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());
			*/

			//// ----the problem of this implementation is that the viewport only moves 
			//// when there is keyboard input. => solution is that makes a key input storage in the player sprite class.
			PhysicalProperties *playerPP = player->getPhysicalProperties();
			int playerSpriteWidth = player->getSpriteType()->getTextureWidth();
			int playerSpriteHeight = player->getSpriteType()->getTextureHeight();
			int playerCenterX = playerPP->getX() + playerSpriteWidth / 2;
			int playerCenterY = playerPP->getY() + playerSpriteHeight / 2;

			int futureViewportLeft = playerCenterX - viewport->getViewportWidth() / 2;
			int futureViewportTop = playerCenterY - viewport->getViewportHeight() / 2;
			
			int futureViewportRight = playerCenterX + viewport->getViewportWidth() / 2;
			int futureViewportBottom = playerCenterY + viewport->getViewportHeight() / 2;

			World *world = game->getGSM()->getWorld();

			//// viewport x axis reached world edge
			if (futureViewportLeft <= 0 || futureViewportRight >= world->getWorldWidth())
			{
				//// no viewport move on x axis
			}
			//// if x axis is okay to move
			else
			{
				//// move viewport x,y = future x,y to the center location 
				viewport->setViewportX(futureViewportLeft);
			}

			//// viewport y axis reached world edge
			if (futureViewportTop <= 0 || futureViewportBottom >= world->getWorldHeight())
			{
				//// no viewport move on x axis
			}
			//// if y axis is okay to move
			else
			{
				//// move viewport x,y = future x,y to the center location 
				viewport->setViewportY(futureViewportTop);
			}
		}

		if (input->isKeyDownForFirstTime(K_KEY))
		{
			gsm->getPhysics()->toggleBotPhysics();
		}

		if (input->isKeyDownForFirstTime(L_KEY))
		{
			gsm->getPhysics()->togglePlayerPhysics();
		}

		if (input->isKeyDownForFirstTime(U_KEY))
		{
			moveviewport = !moveviewport;
		}
		//viewport->toggleDebugView();
		//game->getGraphics()->toggleDebugTextShouldBeRendered();
		if (game->getGSM()->getSafety() != NULL)
		{
			if (input->isKeyDown(game->getGSM()->getIntKey()))
			{
				//generator->setdebug(L"sdfsfdssd");
			}
			else
			{
				//generator->setdebug(L"");
			}
		}
		
	}

	// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
	// THIS CHANGES THE CURSOR IMAGE
	if ((input->isKeyDownForFirstTime(C_KEY))
		&& input->isKeyDown(VK_SHIFT))
	{
		Cursor *cursor = game->getGUI()->getCursor();
		unsigned int id = cursor->getActiveCursorID();
		id++;
		if (id == cursor->getNumCursorIDs())
			id = 0;		
		cursor->setActiveCursorID(id);
	}

	// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
	GameClock *clock = game->getClock();
	int fps = clock->getTargetFPS();

	// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
	// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
	// A BETTER PLAYER EXPERIENCE
	if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
		clock->setTargetFPS(fps + FPS_INC);

	// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
	else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
		clock->setTargetFPS(fps - FPS_INC);
}