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

int facing = 0;

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
	//if (gsm->isGameInProgress() && (gsm->getSpriteManager()->getPlayer()->getCurrentState().compare(L"DEAD") != 0 &&
	//	gsm->getSpriteManager()->getPlayer()->getCurrentState().compare(L"DYING") != 0))
	if (gsm->isGameInProgress() && gsm->getPhysics()->getGameOver() == false)
	{
		
		//// --- PLAYER MOVEMENTS
		//// set player sprite's state according to the key input types
		// up key
		bool viewportMoved = false;
		float viewportVx = 0.0f;
		float viewportVy = 0.0f;
		
		PhysicalProperties *playerPP = player->getPhysicalProperties();

		if (player->getCurrentState().compare(L"IDLE_FRONT") == 0 || player->getCurrentState().compare(L"WALK_FRONT") == 0)
			player->setFacing(1);
		if (player->getCurrentState().compare(L"IDLE_BACK") == 0 || player->getCurrentState().compare(L"WALK_BACK") == 0)
			player->setFacing(2);
		if (player->getCurrentState().compare(L"IDLE_LEFT") == 0 || player->getCurrentState().compare(L"WALK_LEFT") == 0)
			player->setFacing(3);
		if (player->getCurrentState().compare(L"IDLE_RIGHT") == 0 || player->getCurrentState().compare(L"WALK_RIGHT") == 0)
			player->setFacing(4);

		
		if (input->isKeyDown(VK_UP) && !gsm->getMoveviewport())
		{
			wstring wStrState;

			if (player->isStrafing())
			{
				if (player->getFacing() == 1)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_FRONT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_FRONT.end());
				else if (player->getFacing() == 2)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_BACK.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_BACK.end());
				else if (player->getFacing() == 3)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_LEFT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_LEFT.end());
				else if (player->getFacing() == 4)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_RIGHT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_RIGHT.end());

			}
			else
				wStrState.assign(MG_PLAYER_ANIMATION_STATE_WALK_FRONT.begin(), MG_PLAYER_ANIMATION_STATE_WALK_FRONT.end());
			if (player->getCurrentState().compare(L"PUNCH_FRONT") != 0 && player->getCurrentState().compare(L"SHOOT_FRONT") != 0
				&& player->getCurrentState().compare(L"SHOOT_LEFT") != 0
				&& player->getCurrentState().compare(L"SHOOT_RIGHT") != 0
				&& player->getCurrentState().compare(L"SHOOT_DOWN") != 0)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(wStrState);
			}
			player->setPlayerState(ENUM_PLAYER_MOVING);
			player->setPlayerDirection(ENUM_PLAYER_DIRECTION_UP);
			player->setPlayerInputStorage(VK_UP);

			if (playerPP->getY() >= viewport->getViewportY() + viewport->getViewportHeight() / 2 - 50 && playerPP->getY() <= viewport->getViewportY() + viewport->getViewportHeight() / 2 + 5)
			{
				viewportVy -= playerPP->getVelocityY();
				viewportMoved = true;
			}
			//playerPP->setY(playerPP->getY() - playerPP->getVelocityY());
				

		}
			// down key
		if (input->isKeyDown(VK_DOWN) && !gsm->getMoveviewport())
		{
			wstring wStrState;

			if (player->isStrafing())
			{
				if (player->getFacing() == 1)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_FRONT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_FRONT.end());
				else if (player->getFacing() == 2)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_BACK.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_BACK.end());
				else if (player->getFacing() == 3)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_LEFT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_LEFT.end());
				else if (player->getFacing() == 4)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_RIGHT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_RIGHT.end());

			}
			else
				wStrState.assign(MG_PLAYER_ANIMATION_STATE_WALK_BACK.begin(), MG_PLAYER_ANIMATION_STATE_WALK_BACK.end());
			if (player->getCurrentState().compare(L"PUNCH_BACK") != 0 && player->getCurrentState().compare(L"SHOOT_BACK") != 0
				&& player->getCurrentState().compare(L"SHOOT_LEFT") != 0
				&& player->getCurrentState().compare(L"SHOOT_FRONT") != 0
				&& player->getCurrentState().compare(L"SHOOT_RIGHT") != 0)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(wStrState);

			}
			player->setPlayerState(ENUM_PLAYER_MOVING);
			player->setPlayerDirection(ENUM_PLAYER_DIRECTION_DOWN);
			player->setPlayerInputStorage(VK_DOWN);

			if (playerPP->getY() >= viewport->getViewportY() + viewport->getViewportHeight() / 2 - 50 && playerPP->getY() <= viewport->getViewportY() + viewport->getViewportHeight() / 2 + 5)
			{
				
				viewportVy += playerPP->getVelocityY();
				viewportMoved = true;
			}
				
			//playerPP->setY(playerPP->getY() + playerPP->getVelocityY());
				
		}
		// left key
		if (input->isKeyDown(VK_LEFT) && !gsm->getMoveviewport())
		{
			wstring wStrState;

			if (player->isStrafing())
			{
				if (player->getFacing() == 1)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_FRONT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_FRONT.end());
				else if (player->getFacing() == 2)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_BACK.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_BACK.end());
				else if (player->getFacing() == 3)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_LEFT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_LEFT.end());
				else if (player->getFacing() == 4)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_RIGHT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_RIGHT.end());

			}
			else
				wStrState.assign(MG_PLAYER_ANIMATION_STATE_WALK_LEFT.begin(), MG_PLAYER_ANIMATION_STATE_WALK_LEFT.end());
			if (player->getCurrentState().compare(L"PUNCH_LEFT") != 0 && player->getCurrentState().compare(L"SHOOT_LEFT") != 0
				&& player->getCurrentState().compare(L"SHOOT_RIGHT") != 0
				&& player->getCurrentState().compare(L"SHOOT_FRONT") != 0
				&& player->getCurrentState().compare(L"SHOOT_DOWN") != 0)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(wStrState);
			}
			
			player->setPlayerState(ENUM_PLAYER_MOVING);
			player->setPlayerDirection(ENUM_PLAYER_DIRECTION_LEFT);
			player->setPlayerInputStorage(VK_LEFT);

			if (playerPP->getX() >= viewport->getViewportX() + viewport->getViewportWidth() / 2 - 5 && playerPP->getX() <= viewport->getViewportX() + viewport->getViewportWidth() / 2 + 5)
			{
				viewportVx -= playerPP->getVelocityX();
				viewportMoved = true;
				
			}
			//playerPP->setX(playerPP->getX() - playerPP->getVelocityX());
		}
		// right key
		if (input->isKeyDown(VK_RIGHT) && !gsm->getMoveviewport())
		{
			wstring wStrState;

			if (player->isStrafing())
			{
				if (player->getFacing() == 1)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_FRONT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_FRONT.end());
				else if (player->getFacing() == 2)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_BACK.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_BACK.end());
				else if (player->getFacing() == 3)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_LEFT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_LEFT.end());
				else if (player->getFacing() == 4)
					wStrState.assign(MG_PLAYER_ANIMATION_STATE_STRAFE_RIGHT.begin(), MG_PLAYER_ANIMATION_STATE_STRAFE_RIGHT.end());

			}
			else
				wStrState.assign(MG_PLAYER_ANIMATION_STATE_WALK_RIGHT.begin(), MG_PLAYER_ANIMATION_STATE_WALK_RIGHT.end());
			if (player->getCurrentState().compare(L"PUNCH_RIGHT") != 0 && player->getCurrentState().compare(L"SHOOT_RIGHT") != 0 
				&& player->getCurrentState().compare(L"SHOOT_LEFT") != 0
				&& player->getCurrentState().compare(L"SHOOT_FRONT") != 0
				&& player->getCurrentState().compare(L"SHOOT_BACK") != 0)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(wStrState);
			}
			player->setPlayerState(ENUM_PLAYER_MOVING);
			player->setPlayerDirection(ENUM_PLAYER_DIRECTION_RIGHT);
			player->setPlayerInputStorage(VK_RIGHT);

			if (playerPP->getX() >= viewport->getViewportX() + viewport->getViewportWidth() / 2 - 5 && playerPP->getX() <= viewport->getViewportX() + viewport->getViewportWidth() / 2 + 5)
			{
				viewportVx += playerPP->getVelocityX();
				viewportMoved = true;
				
			}
			//playerPP->setX(playerPP->getX() + playerPP->getVelocityX());
		}
			//if (viewportMoved)
			//	viewport->moveViewport((int)floor(viewportVx + 0.5f), (int)floor(viewportVy + 0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());

		
		
			
				//playerPP->setX(playerPP->getX() + playerPP->getVelocityX());
			
			//if (viewportMoved)
			//	viewport->moveViewport((int)floor(viewportVx + 0.5f), (int)floor(viewportVy + 0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());

		
		//// --- end ---

		if (input->isKeyDownForFirstTime(P_KEY))
		{
			gsm->getPhysics()->togglePhysics();
		}
		if (input->isKeyDownForFirstTime(T_KEY))
		{
			gsm->getPhysics()->activateForSingleUpdate();
		}
		
		if (gsm->getMoveviewport())
		{
			//// I'm changing this code because I want that the viewport location is
			//// decided depending on the player sprite's location
			alterview = true;
			
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
			
			
			//// ----the problem of this implementation is that the viewport only moves 
			//// when there is keyboard input. => solution is that makes a key input storage in the player sprite class.
			
			
		}
		else
		{



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
			gsm->toggleMoveviewport();
		}
		if (input->isKeyDownForFirstTime(V_KEY) && !gsm->getMoveviewport())
		{
			//Strafe
			//player->setCurrentState(player->getCurrentState());
			player->togglestrafe();
			
		}


		if (input->isKeyDown(F_KEY) && !gsm->getMoveviewport())
		{
			//Shoot
			if (player->getFacing() == 1 && player->getCurrentState().compare(L"SHOOT_FRONT") != 0)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(L"SHOOT_FRONT");
			}
			else if (player->getFacing() == 2 && player->getCurrentState().compare(L"SHOOT_BACK") != 0)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(L"SHOOT_BACK");
			}
			else if (player->getFacing() == 3 && player->getCurrentState().compare(L"SHOOT_LEFT") != 0)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(L"SHOOT_LEFT");
			}
			else if (player->getFacing() == 4 && player->getCurrentState().compare(L"SHOOT_RIGHT") != 0)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(L"SHOOT_RIGHT");
			}

			/*if (input->isKeyDown(game->getGSM()->getIntKey()))
			{
				//generator->setdebug(L"sdfsfdssd");
				game->getGSM()->SafetyOn();
			}
			else 
			{
				generator->setdebug(L"");
				game->getGSM()->SafetyOff();
			}*/
		}
		if (input->isKeyDown(G_KEY) && !gsm->getMoveviewport())
		{
			if (player->getFacing() == 1 && player->getCurrentState().compare(L"PUNCH_FRONT") != 0 && player->getCanheal() == false)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(L"PUNCH_FRONT");
			}
			else if (player->getFacing() == 2 && player->getCurrentState().compare(L"PUNCH_BACK") != 0 && player->getCanheal() == false)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(L"PUNCH_BACK");
			}
			else if (player->getFacing() == 3 && player->getCurrentState().compare(L"PUNCH_LEFT") != 0 && player->getCanheal() == false)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(L"PUNCH_LEFT");
			}
			else if (player->getFacing() == 4 && player->getCurrentState().compare(L"PUNCH_RIGHT") != 0 && player->getCanheal() == false)
			{
				player->setPreviousState(player->getCurrentState());
				player->setCurrentState(L"PUNCH_RIGHT");
			}

			/*if (input->isKeyDown(game->getGSM()->getIntKey()))
			{
				generator->setdebug(L"sdfsfdssd");
				game->getGSM()->SafetyOn();
			}
			else
			{
				generator->setdebug(L"");
				game->getGSM()->SafetyOff();
			}*/
		}
		if (input->isKeyDown(H_KEY))
		{
			if (player->getCanheal() == true)
			{
				player->setIshealing(true);
			}
		}

		if (input->isKeyDownForFirstTime(I_KEY) && input->isKeyDown(VK_CONTROL))
		{
			player->toggleinvincible();
		}

		//viewport->toggleDebugView();
		//game->getGraphics()->toggleDebugTextShouldBeRendered();
		if (game->getGSM()->getSafety() != NULL)
		{
			if (input->isKeyDown(game->getGSM()->getIntKey()))
			{
				generator->setdebug(L"Safety On");
				game->getGSM()->SafetyOn();
			}
			else
			{
				generator->setdebug(L"");
				game->getGSM()->SafetyOff();
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

	if (gsm->isGameInProgress() && input->isKeyDownForFirstTime(ESCAPE_KEY))
		gsm->goToIngamePauseMenu();
	else if (gsm->isGameInPauseMenu() && input->isKeyDownForFirstTime(ESCAPE_KEY))
		gsm->goToGame();
	else if (gsm->isGameInProgress() && input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(W_KEY))
		gsm->addUpgrade(L"ATTACK");
	else if (gsm->isGameInProgress() && input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(A_KEY))
		gsm->addUpgrade(L"DEFENSE");
	else if (gsm->isGameInProgress() && input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(S_KEY))
		gsm->addUpgrade(L"SPEED");
	else if (gsm->isGameInProgress() && input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(D_KEY))
		gsm->useUpgrade(L"ATTACK");
	else if (gsm->isGameInProgress() && input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(P_KEY))
		gsm->useUpgrade(L"DEFENSE");
	else if (gsm->isGameInProgress() && input->isKeyDown(VK_CONTROL) && input->isKeyDownForFirstTime(T_KEY))
		gsm->useUpgrade(L"SPEED");

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