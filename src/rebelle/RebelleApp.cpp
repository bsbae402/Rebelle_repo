/////// branch branch



/*
	RebelleApp.cpp
	edit: team Lawless 

	> Based on: BugsApp.cpp
	> Author: Richard McKenna
	>		Stony Brook University
	>		Computer Science Department
	

	This is a test game application, a game that demonstrates use of the 
	SideScrollerFramework to make a little scrolling, interactive demo. It
	demonstrates the rendering of images and text as well as responding to
	key presses and button cicks. Students should make their own named game
	applictions using a similar pattern, gradually adding other components,
	like additional gui controls, tiles, sprites, ai, and physics.
 */

#include "rebelle_VS\stdafx.h"

// Bugs GAME INCLUDES
#include "rebelle\RebelleApp.h"
#include "rebelle\RebelleButtonEventHandler.h"
#include "rebelle\RebelleKeyEventHandler.h"
#include "rebelle\RebelleMouseEventHandler.h"
#include "rebelle\RebelleTextGenerator.h"
#include "rebelle\RebelleStateMachine.h"
/// ---- Bongsung
#include "rebelle\RebelleUpgradeScreenGUI.h"

// GAME OBJECT INCLUDES
#include "mg\game\Game.h"
#include "mg\graphics\GameGraphics.h"
#include "mg\gsm\state\GameState.h"
#include "mg\gsm\state\GameStateMachine.h"
#include "mg\gui\Cursor.h"
#include "mg\gui\GameGUI.h"
#include "mg\gui\ScreenGUI.h"
#include "mg\input\GameInput.h"
#include "mg\os\GameOS.h"
#include "mg\text\GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "mg\platforms\Windows\WindowsOS.h"
#include "mg\platforms\Windows\WindowsInput.h"

// DIRECTX INCLUDES
#include "mg\platforms\DirectX\DirectXGraphics.h"
#include "mg\platforms\DirectX\DirectXTextureManager.h"

#include "mg\platforms\DirectX\GameAudio.h"

// FORWARD DECLARATIONS
void initCursor();
void initInGameGUI();
void initMainMenu();
void initSplashScreen();
void initLoadingLevel();
void initViewport();

///// declaration of custom functions in this file
void initLevelCompleteScreen();
void initInGamePauseMenu();
void initUpgradeScreen();
void initDonateScreen();

/*
	WinMain - This is the application's starting point. In this method we will construct a Game object, 
	then initialize all the platform-dependent technologies, then construct all the custom data for our 
	game, and then initialize the Game with	our custom data. We'll then start the game loop.
*/
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	// CREATE AND START UP THE ENGINE
	Game *rebelleGame = Game::getSingleton();
	rebelleGame->startUp();

	// NOW LOAD THE GAME-SPECIFIC STUFF

	// LOAD OUR CUSTOM TEXT GENERATOR, WHICH DETERMINES WHAT TEXT IS DRAWN EACH FRAME
	RebelleTextGenerator *rebelleTextGenerator = new RebelleTextGenerator();
	rebelleTextGenerator->startUp();

	// NOW LET'S LOAD THE GUI STUFF
	initViewport();
	initCursor();
	initSplashScreen();
	initMainMenu();
	initInGameGUI();
	initLoadingLevel();

	////-- edit:bongsung --
	initInGamePauseMenu();
	initUpgradeScreen();
	initLevelCompleteScreen();
	initDonateScreen();
	///////-----

	// SPECIFY WHO WILL HANDLE BUTTON EVENTS
	RebelleButtonEventHandler *rebelleButtonHandler = new RebelleButtonEventHandler();
	GameGUI *gui = rebelleGame->getGUI();
	gui->registerButtonEventHandler((ButtonEventHandler*)rebelleButtonHandler);

	// SPECIFY WHO WILL HANDLE KEY EVENTS
	RebelleKeyEventHandler *rebelleKeyHandler = new RebelleKeyEventHandler();
	rebelleGame->getInput()->registerKeyHandler((KeyEventHandler*)rebelleKeyHandler);

	// SPECIFY WHO WILL HANDLE MOUSE EVENTS NOT RELATED TO THE GUI
	RebelleMouseEventHandler *rebelleMouseHandler = new RebelleMouseEventHandler();
	rebelleGame->getInput()->registerMouseHandler((MouseEventHandler*)rebelleMouseHandler);

	// MAKE THE GAME STATE MACHINE THAT WILL HELP 
	// IMPLEMENT SOME CUSTOM GAME RULES
	RebelleStateMachine *rsm = new RebelleStateMachine();
	GameStateManager *gsm = rebelleGame->getGSM();
	gsm->setGameStateMachine(rsm);

	//// here, we are going to set game audios
	GameAudio *audio = rebelleGame->getAudio();
	audio->registerSoundEffect(ENUM_SOUND_EFFECT_SHOOT, SHOOT_SOUND_EFFECT_PATH);
	audio->registerSoundEffect(ENUM_SOUND_EFFECT_MONEY, MONEY_SOUND_EFFECT_PATH);
	audio->registerSoundEffect(ENUM_SOUND_EFFECT_PUNCH, PUNCH_SOUND_EFFECT_PATH);
	audio->registerSoundEffect(ENUM_SOUND_EFFECT_HEAL, HEAL_SOUND_EFFECT_PATH);
	audio->registerMusic(ENUM_MUSIC_MAIN_THEME, MAIN_THEME_MUSIC_PATH);
	audio->registerMusic(ENUM_MUSIC_LEVEL_COMPLETE, LEVEL_COMPLETE_MUSIC_PATH);
	audio->registerMusic(ENUM_MUSIC_GAMEOVER, GAMEOVER_MUSIC_PATH);

	//// ------ MORE AUDIO AND MUSIC NEEDED

	// START THE GAME LOOP
	rebelleGame->runGameLoop();

	// AND RETURN
	return 0;
}

/*
	initCursor - initializes a simple little cursor for the gui.
*/
void initCursor()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// SETUP THE CURSOR
	vector<unsigned int> *imageIDs = new vector<unsigned int>();
	int imageID;

	// - LOAD THE RED ANT CURSOR IMAGE
	imageID = guiTextureManager->loadTexture(RED_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - LOAD THE BLACK ANT CURSOR IMAGE
	imageID = guiTextureManager->loadTexture(YELLOW_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - NOW BUILD AND LOAD THE CURSOR
	Cursor *cursor = new Cursor();
	cursor->initCursor(imageIDs,
		*(imageIDs->begin()),
		0,
		0,
		0,
		255,
		32,
		32);
	GameGUI *gui = game->getGUI();
	gui->setCursor(cursor);
}

/*
	initInGameGUI - initializes the game's in-game gui.
*/
void initInGameGUI()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// NOW ADD THE IN-GAME GUI
	ScreenGUI *inGameGUI = new ScreenGUI();
	
	//// in-game guis are all disabled currently
	//// unsigned int imageID = guiTextureManager->loadTexture(IN_GAME_TOOLBAR_PATH);
	////  we don't have in-game toolbar
	/*
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 255;
	imageToAdd->width = 1366;
	imageToAdd->height = 64;
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->imageID = imageID;
	inGameGUI->addOverlayImage(imageToAdd);

	unsigned int normalTextureID = guiTextureManager->loadTexture(QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(QUIT_IMAGE_MO_PATH);
	
	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		0,
		0,
		0,
		255,
		200,
		100,
		false,
		QUIT_COMMAND);
	inGameGUI->addButton(buttonToAdd);
	*/

	// AND LET'S ADD OUR SCREENS
	GameGUI *gui = game->getGUI();
	gui->addScreenGUI(GS_GAME_IN_PROGRESS, inGameGUI);
}

/*
	initMainMenu - initializes the game's main menu gui.
*/
void initMainMenu()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(MAIN_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 255;
	imageToAdd->width = 512;
	imageToAdd->height = 512;
	imageToAdd->x = (graphics->getScreenWidth()/2)-(imageToAdd->width/2);
	imageToAdd->y = (graphics->getScreenHeight()/2)-(imageToAdd->height/2);
	imageToAdd->z = 0;
	imageToAdd->imageID = imageID;
	mainMenuGUI->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN EXIT BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(EXIT_IMAGE_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(EXIT_IMAGE_MO_PATH);
	int buttonWidth = 200;
	int buttonHeight = 100;
	int buttonPadding = 15;

	int exitNstartButtonY = (graphics->getScreenHeight() * 70 / 100);
	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		(graphics->getScreenWidth() / 2) + buttonPadding,
		exitNstartButtonY,
		0,
		255,
		buttonWidth,
		buttonHeight,
		false,
		EXIT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD A START BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(START_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(START_IMAGE_MO_PATH);

	// - INIT THE START BUTTON
	int controlsButtonY = (graphics->getScreenHeight() * 50 / 100);
	//// third arg. is x, forth arg is y
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		(graphics->getScreenWidth()/2) - buttonWidth - buttonPadding,
		exitNstartButtonY,
		0,
		255,
		buttonWidth,
		buttonHeight,
		false,
		START_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	//// Now, add controls button
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	normalTextureID = guiTextureManager->loadTexture(CONTROLS_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(CONTROLS_IMAGE_MO_PATH);

	// - INIT THE Controls BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		(graphics->getScreenWidth() / 2) - (buttonWidth/2),
		controlsButtonY,
		0,
		255,
		buttonWidth,
		buttonHeight,
		false,
		CONTROLS_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI (controls)
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	GameGUI *gui = game->getGUI();
	gui->addScreenGUI(GS_MAIN_MENU, mainMenuGUI);
}

void initLoadingLevel()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// ADD A LOADING SCREEN GUI
	ScreenGUI *loadingLevelGUI = new ScreenGUI();

	// INIT THE QUIT BUTTON
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(LOADING_LEVEL_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 255;
	imageToAdd->width = 800;
	imageToAdd->height = 530;
	imageToAdd->x = (graphics->getScreenWidth() / 2) - (imageToAdd->width / 2);
	imageToAdd->y = (graphics->getScreenHeight() / 2) - (imageToAdd->height / 2);
	imageToAdd->z = 0;
	imageToAdd->imageID = imageID;
	loadingLevelGUI->addOverlayImage(imageToAdd);

	// AND REGISTER IT WITH THE GUI
	GameGUI *gui = game->getGUI();
	gui->addScreenGUI(GS_PRE_GAME, loadingLevelGUI);
	gui->addScreenGUI(GS_LOADING_LEVEL, loadingLevelGUI);
}

/*
	initSplashScreen - initializes the game's splash screen gui.
*/
void initSplashScreen()
{
	Game *game = Game::getSingleton();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// NOW, FIRST LET'S ADD A SPLASH SCREEN GUI
	ScreenGUI *splashScreenGUI = new ScreenGUI();

	// WE'LL ONLY HAVE ONE IMAGE FOR OUR GIANT BUTTON
	unsigned int normalTextureID = guiTextureManager->loadTexture(SPLASH_SCREEN_PATH);
	unsigned int mouseOverTextureID = normalTextureID;

	int imageWidth = 1024;
	int imageHeight = 768;

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		(game->getGraphics()->getScreenWidth()/2) - (imageWidth/2),
		(game->getGraphics()->getScreenHeight()/2) - (imageHeight/2),
		0,
		255,
		imageWidth,
		imageHeight,
		false,
		GO_TO_MM_COMMAND);
	splashScreenGUI->addButton(buttonToAdd);

	// AND REGISTER IT WITH THE GUI
	GameGUI *gui = game->getGUI();
	gui->addScreenGUI(GS_SPLASH_SCREEN, splashScreenGUI);
}

/*
	initViewport - initializes the game's viewport.
*/
void initViewport()
{
	Game *game = Game::getSingleton();
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();

	// AND NOW SPECIFY THE VIEWPORT SIZE AND LOCATION. NOTE THAT IN THIS EXAMPLE,
	// WE ARE PUTTING A TOOLBAR WITH A BUTTON ACCROSS THE NORTH OF THE APPLICATION.
	// THAT TOOLBAR HAS A HEIGHT OF 64 PIXELS, SO WE'LL MAKE THAT THE OFFSET FOR
	// THE VIEWPORT IN THE Y AXIS
	Viewport *viewport = gui->getViewport();
	viewport->setViewportOffsetY(140);
	int viewportWidth = graphics->getScreenWidth() - VIEWPORT_OFFSET_X;
	int viewportHeight = graphics->getScreenHeight() - VIEWPORT_OFFSET_Y;
	viewport->setViewportWidth(viewportWidth);
	viewport->setViewportHeight(viewportHeight);
	viewport->setToggleOffsetY(TOGGLE_OFFSET_Y);
	
}

void initLevelCompleteScreen()
{
	Game *game = Game::getSingleton();
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// In-game menu will be shown on another screen. 
	// The ongoing game will be paused
	ScreenGUI *levelCompleteScreenGUI = new ScreenGUI();

	unsigned int levelCompleteScreenImageTextureID = guiTextureManager->loadTexture(LEVEL_COMPLETE_SCREEN_PATH);
	int levelCompleteScreenX = 380;
	int levelCompleteScreenY = 250;

	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 230;
	imageToAdd->width = 512;
	imageToAdd->height = 192;
	imageToAdd->x = levelCompleteScreenX;
	imageToAdd->y = levelCompleteScreenY;
	imageToAdd->z = 0;
	imageToAdd->imageID = levelCompleteScreenImageTextureID;
	levelCompleteScreenGUI->addOverlayImage(imageToAdd);


	/// -- adding resume button OF level complete screen
	Button *resumeButton = new Button();
	unsigned int resumeButtonTID = guiTextureManager->loadTexture(LEVEL_COMPLETE_BUTTON_RESUME_PATH);
	unsigned int moResumeButtonTID = guiTextureManager->loadTexture(LEVEL_COMPLETE_BUTTON_RESUME_MO_PATH);
	int resumeButtonWidth = 200;
	int resumeButtonHeight = 100;
	int resumeButtonPadding = 10;
	int resumeButtonX = levelCompleteScreenX + 150;
	int resumeButtonY = levelCompleteScreenY + 90;

	resumeButton->initButton(resumeButtonTID, moResumeButtonTID,
		resumeButtonX, resumeButtonY, 0, 255,
		resumeButtonWidth, resumeButtonHeight, true, GO_TO_NEXT_LEVEL_COMMAND);

	levelCompleteScreenGUI->addButton(resumeButton);
	/// --- complete resuem button

	gui->addScreenGUI(GS_LEVEL_COMPLETE, levelCompleteScreenGUI);
}

/*
	Bongsung - gui setting function: in-game menu
*/
void initInGamePauseMenu()
{
	Game *game = Game::getSingleton();
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	// In-game menu will be shown on another screen. 
	// The ongoing game will be paused
	ScreenGUI *inGameMenuScreenGUI = new ScreenGUI();

	unsigned int ingameMenuScreenImageTextureID = guiTextureManager->loadTexture(INGAME_PAUSE_MENU_PATH);
	int pauseMenuX = 180;

	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 230;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->x = pauseMenuX;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->imageID = ingameMenuScreenImageTextureID;
	inGameMenuScreenGUI->addOverlayImage(imageToAdd);

	int resumeNstartButtonY = 600;

	/// --- adding resume button
	Button *resumeButton = new Button();
	unsigned int resumeButtonTID = guiTextureManager->loadTexture(PAUSE_MENU_RESUME_PATH);
	unsigned int moResumeButtonTID = guiTextureManager->loadTexture(PAUSE_MENU_RESUME_MO_PATH);
	int resumeButtonWidth = 200;
	int resumeButtonHeight = 100;
	int resumeButtonPadding = 10;
	int resumeButtonX = pauseMenuX + 100;

	resumeButton->initButton(resumeButtonTID, moResumeButtonTID,
		resumeButtonX, resumeNstartButtonY, 0, 255,
		resumeButtonWidth, resumeButtonHeight, true, RESUME_COMMAND);

	inGameMenuScreenGUI->addButton(resumeButton);
	/// --- complete resuem button

	/// --- adding exit button
	Button *exitButton = new Button();
	unsigned int exitButtonTID = guiTextureManager->loadTexture(PAUSE_MENU_EXIT_PATH);
	unsigned int moExitButtonTID = guiTextureManager->loadTexture(PAUSE_MENU_EXIT_MO_PATH);
	int exitButtonWidth = 200;
	int exitButtonHeight = 100;
	int exitButtonPadding = 10;
	int exitButtonX = pauseMenuX + 500;

	exitButton->initButton(exitButtonTID, moExitButtonTID,
		exitButtonX, resumeNstartButtonY, 0, 255,
		exitButtonWidth, exitButtonHeight, true, PAUSE_MENU_EXIT_COMMAND);

	inGameMenuScreenGUI->addButton(exitButton);
	/// --- complete exit button

	/// --- adding show upgrade button
	int showUpgradeButtonY = 300;

	Button *showUpgradeButton = new Button();
	unsigned int showUpgradeButtonTID = guiTextureManager->loadTexture(PAUSE_MENU_SHOW_UPGRADE_PATH);
	unsigned int moShowUpgradeButtonTID = guiTextureManager->loadTexture(PAUSE_MENU_SHOW_UPGRADE_MO_PATH);
	int showUpgradeButtonWidth = 500;
	int showUpgradeButtonHeight = 50;
	int showUpgradeButtonPadding = 10;
	int showUpgradeButtonX = pauseMenuX + 200;

	showUpgradeButton->initButton(showUpgradeButtonTID, moShowUpgradeButtonTID,
		showUpgradeButtonX, showUpgradeButtonY, 0, 255,
		showUpgradeButtonWidth, showUpgradeButtonHeight, true, SHOW_UPGRADE_COMMAND);

	inGameMenuScreenGUI->addButton(showUpgradeButton);
	/// --- complete show upgrade button

	//Add Donate button

	int donateButtonY = 380;

	Button *donateButton = new Button();
	unsigned int donateButtonTID = guiTextureManager->loadTexture(PAUSE_MENU_DONATE_MONEY_PATH);
	unsigned int moDonateButtonTID = guiTextureManager->loadTexture(PAUSE_MENU_DONATE_MONEY_MO_PATH);
	int donateButtonWidth = 500;
	int donateButtonHeight = 50;
	int donateButtonPadding = 10;
	int donateButtonX = pauseMenuX + 200;

	donateButton->initButton(donateButtonTID, moDonateButtonTID,
		donateButtonX, donateButtonY, 0, 255,
		donateButtonWidth, donateButtonHeight, true, DONATE_MONEY_COMMAND);

	inGameMenuScreenGUI->addButton(donateButton);


	gui->addScreenGUI(GS_PAUSED, inGameMenuScreenGUI);

	//// To Be Editted ...
}

void initDonateScreen()
{
	Game *game = Game::getSingleton();
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	unsigned int moneyUpgradeTitleTID = guiTextureManager->loadTexture(MONEY_UPGRADE_TITLE_PATH);
	unsigned int moneytextTID = guiTextureManager->loadTexture(MONEY_TEXT_PATH);
	unsigned int moneylabelTID = guiTextureManager->loadTexture(MONEY_LABEL_PATH);
	unsigned int upTID = guiTextureManager->loadTexture(INCREASE_MONEY_PATH);
	unsigned int moupTID = guiTextureManager->loadTexture(INCREASE_MONEY_MO_PATH);
	unsigned int downTID = guiTextureManager->loadTexture(DECREASE_MONEY_PATH);
	unsigned int modownTID = guiTextureManager->loadTexture(DECREASE_MONEY_MO_PATH);
	unsigned int scorelabelTID = guiTextureManager->loadTexture(SCORE_LABEL_PATH);
	unsigned int donateTID = guiTextureManager->loadTexture(DONATE_BUTTON_PATH);
	unsigned int modonateTID = guiTextureManager->loadTexture(DONATE_BUTTON_MO_PATH);

	// In-game menu will be shown on another screen. 
	// The ongoing game will be paused
	RebelleUpgradeScreenGUI *donateScreenGUI = new RebelleUpgradeScreenGUI();

	unsigned int donateScreenImageTextureID = guiTextureManager->loadTexture(DONATE_SCREEN_LAYOUT_PATH);
	int pauseMenuX = 180;

	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 230;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->x = pauseMenuX;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->imageID = donateScreenImageTextureID;
	donateScreenGUI->addOverlayImage(imageToAdd);


	Button *backToPauseMenuButton = new Button();
	unsigned int backToPauseMenuButtonTID = guiTextureManager->loadTexture(BACK_TO_MENU_PATH);
	unsigned int moBackToPauseMenuButtonTID = guiTextureManager->loadTexture(BACK_TO_MENU_MO_PATH);
	int backTPMButtonWidth = 300;
	int backTPMButtonHeight = 60;
	int backTPMButtonX = 200;
	int backTPMButtonY = 700;

	backToPauseMenuButton->initButton(backToPauseMenuButtonTID, moBackToPauseMenuButtonTID,
		backTPMButtonX, backTPMButtonY, 0, 255,
		backTPMButtonWidth, backTPMButtonHeight, true, BACK_TO_PAUSE_MENU_COMMAND);

	donateScreenGUI->addButton(backToPauseMenuButton);


	OverlayImage *moneylabel = new OverlayImage();
	moneylabel->alpha = 255;
	moneylabel->width = donateScreenGUI->getStatTitleWidth();
	moneylabel->height = donateScreenGUI->getStatLineHeight();
	moneylabel->x = 300;
	moneylabel->y = 170;
	moneylabel->z = 0;
	moneylabel->imageID = moneylabelTID;
	donateScreenGUI->addOverlayImage(moneylabel);

	OverlayImage *scorelabel = new OverlayImage();
	scorelabel->alpha = 255;
	scorelabel->width = donateScreenGUI->getStatTitleWidth();
	scorelabel->height = donateScreenGUI->getStatLineHeight();
	scorelabel->x = 300;
	scorelabel->y = 370;
	scorelabel->z = 0;
	scorelabel->imageID = scorelabelTID;
	donateScreenGUI->addOverlayImage(scorelabel);

	Button *money = new Button();
	int moneyButtonX = 480;
	int moneyButtonY = 170;
	money->initButton(moneytextTID, moneytextTID,
		moneyButtonX, moneyButtonY, 0, 255,
		100, 60, true, L"no command");
	donateScreenGUI->addButton(money);


	Button *donateButton = new Button();
	int donateWidth = 300;
	int donateHeight = 60;
	int donateX = 800;
	int donateY = 150;

	donateButton->initButton(donateTID, modonateTID,
		donateX, donateY, 0, 255,
		donateWidth, donateHeight, true, L"donate");

	donateScreenGUI->addButton(donateButton);



	Button *score = new Button();
	int scoreButtonX = 450;
	int scoreButtonY = 370;
	score->initButton(moneytextTID, moneytextTID,
		scoreButtonX, scoreButtonY, 0, 255,
		100, 60, true, L"no command");
	donateScreenGUI->addButton(score);

	Button *up = new Button();
	int upX = 730;
	int upY = 130;
	up->initButton(upTID, moupTID,
		upX, upY, 0, 255,
		50, 50, true, L"increase donate");
	donateScreenGUI->addButton(up);

	Button *down = new Button();
	int downX = 730;
	int downY = 190;
	down->initButton(downTID, modownTID,
		downX, downY, 0, 255,
		50, 50, true, L"decrease donate");
	donateScreenGUI->addButton(down);


	gui->addScreenGUI(GS_DONATE_SCREEN, donateScreenGUI);

}

void initUpgradeScreen() {
	Game *game = Game::getSingleton();
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	TextureManager *guiTextureManager = graphics->getGUITextureManager();

	RebelleUpgradeScreenGUI *upgradeScreenGUI = new RebelleUpgradeScreenGUI();

	unsigned int upgradeScreenLayoutTID = guiTextureManager->loadTexture(UPGRADE_SCREEN_LAYOUT_PATH);

	unsigned int speedUpgradeTitleTID = guiTextureManager->loadTexture(SPEED_UPGRADE_TITLE_PATH);
	unsigned int attackUpgradeTitleTID = guiTextureManager->loadTexture(ATTACK_UPGRADE_TITLE_PATH);
	unsigned int defenseUpgradeTitleTID = guiTextureManager->loadTexture(DEFENSE_UPGRADE_TITLE_PATH);
	unsigned int upgradeUpgradeTitleTID = guiTextureManager->loadTexture(UPGRADE_UPGRADE_TITLE_PATH);
	unsigned int priceUpgradeTitleTID = guiTextureManager->loadTexture(PRICE_UPGRADE_TITLE_PATH);
	unsigned int purchaseUpgradeTitleTID = guiTextureManager->loadTexture(PURCHASE_UPGRADE_TITLE_PATH);
	unsigned int moneyUpgradeTitleTID = guiTextureManager->loadTexture(MONEY_UPGRADE_TITLE_PATH);
	unsigned int moneytextTID = guiTextureManager->loadTexture(MONEY_TEXT_PATH);
	unsigned int moneylabelTID = guiTextureManager->loadTexture(MONEY_LABEL_PATH);


	unsigned int upgradeButtonTID = guiTextureManager->loadTexture(UPGRADE_BUTTON_PATH);
	unsigned int moUpgradeButtonTID = guiTextureManager->loadTexture(UPGRADE_BUTTON_MO_PATH);

	int upgradeButtonWidth = 40;
	int upgradeButtonHeight = 40;

	/*
	void initialize(unsigned int initScreenX, unsigned int initScreenY,
	unsigned int initStatListX, unsigned int initStatListY,
	unsigned int initYdistBetweenStats,
	unsigned int initStatLineHeight,
	unsigned int initStatTitleWidth,
	unsigned int initUpgradeButtonWidth);
	*/
	upgradeScreenGUI->initialize(100, 0, 200, 200, 30, 40, 250, upgradeButtonWidth);

	/// --- the screen image for upgrade screen
	///// the order of adding OverlayImage in the ScreenGUI object is important.
	///// If I add this screen image later than other images, 
	///// the other images will be rendered below this screen image.
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->alpha = 230;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->x = upgradeScreenGUI->getScreenX();
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->imageID = upgradeScreenLayoutTID;
	upgradeScreenGUI->addOverlayImage(imageToAdd);



	//first add the title for the upgrade table

	//upgrade
	OverlayImage *upgradeUpgradeTitleImage = new OverlayImage();
	upgradeUpgradeTitleImage->alpha = 255;
	upgradeUpgradeTitleImage->width = upgradeScreenGUI->getStatTitleWidth();
	upgradeUpgradeTitleImage->height = upgradeScreenGUI->getStatLineHeight();
	upgradeUpgradeTitleImage->x = upgradeScreenGUI->getStatListX();
	upgradeUpgradeTitleImage->y = upgradeScreenGUI->getStatListY();
	upgradeUpgradeTitleImage->z = 0;
	upgradeUpgradeTitleImage->imageID = upgradeUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(upgradeUpgradeTitleImage);

	//price
	OverlayImage *priceUpgradeTitleImage = new OverlayImage();
	priceUpgradeTitleImage->alpha = 255;
	priceUpgradeTitleImage->width = upgradeScreenGUI->getStatTitleWidth();
	priceUpgradeTitleImage->height = upgradeScreenGUI->getStatLineHeight();
	priceUpgradeTitleImage->x = upgradeScreenGUI->getStatListX() + upgradeScreenGUI->getStatTitleWidth();
	priceUpgradeTitleImage->y = upgradeScreenGUI->getStatListY();
	priceUpgradeTitleImage->z = 0;
	priceUpgradeTitleImage->imageID = priceUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(priceUpgradeTitleImage);

	//purchase
	OverlayImage *purchaseUpgradeTitleImage = new OverlayImage();
	purchaseUpgradeTitleImage->alpha = 255;
	purchaseUpgradeTitleImage->width = upgradeScreenGUI->getStatTitleWidth();
	purchaseUpgradeTitleImage->height = upgradeScreenGUI->getStatLineHeight();
	purchaseUpgradeTitleImage->x = upgradeScreenGUI->getStatListX() + (2 * upgradeScreenGUI->getStatTitleWidth());
	purchaseUpgradeTitleImage->y = upgradeScreenGUI->getStatListY();
	purchaseUpgradeTitleImage->z = 0;
	purchaseUpgradeTitleImage->imageID = purchaseUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(purchaseUpgradeTitleImage);


	/// --- followings are other small images that are drawn upon the screen image
	// -- 1st component on list: speed
	/// text
	int speedStatY = upgradeScreenGUI->getStatListY()
		+ upgradeScreenGUI->getStatLineHeight() + upgradeScreenGUI->getYDistBetweenStats();

	OverlayImage *speedUpgradeTitleImage = new OverlayImage();
	speedUpgradeTitleImage->alpha = 255;
	speedUpgradeTitleImage->width = upgradeScreenGUI->getStatTitleWidth();
	speedUpgradeTitleImage->height = upgradeScreenGUI->getStatLineHeight();
	speedUpgradeTitleImage->x = upgradeScreenGUI->getStatListX();
	speedUpgradeTitleImage->y = speedStatY;
	speedUpgradeTitleImage->z = 0;
	speedUpgradeTitleImage->imageID = speedUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(speedUpgradeTitleImage);

	/// text money
	OverlayImage *moneyUpgradeTitleImage = new OverlayImage();
	moneyUpgradeTitleImage->alpha = 255;
	moneyUpgradeTitleImage->width = upgradeScreenGUI->getStatTitleWidth();
	moneyUpgradeTitleImage->height = upgradeScreenGUI->getStatLineHeight();
	moneyUpgradeTitleImage->x = upgradeScreenGUI->getStatListX() + upgradeScreenGUI->getStatTitleWidth();
	moneyUpgradeTitleImage->y = speedStatY;
	moneyUpgradeTitleImage->z = 0;
	moneyUpgradeTitleImage->imageID = moneyUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(moneyUpgradeTitleImage);

	/// upgrade button
	Button *speedUpButton = new Button();
	int speedUpButtonX = upgradeScreenGUI->getStatListX() + (2 * upgradeScreenGUI->getStatTitleWidth());
	int speedUpButtonY = speedStatY;
	speedUpButton->initButton(upgradeButtonTID, moUpgradeButtonTID,
		speedUpButtonX, speedUpButtonY, 0, 255,
		upgradeButtonWidth, upgradeButtonHeight, true, SPEED_UPGRADE_COMMAND);
	upgradeScreenGUI->addButton(speedUpButton);
	// -- speed component complete

	// 2nd component on list: attack
	int attackStatY = speedStatY
		+ upgradeScreenGUI->getStatLineHeight() + upgradeScreenGUI->getYDistBetweenStats();

	OverlayImage *attackUpgradeTitleImage = new OverlayImage();
	attackUpgradeTitleImage->alpha = 255;
	attackUpgradeTitleImage->width = upgradeScreenGUI->getStatTitleWidth();
	attackUpgradeTitleImage->height = upgradeScreenGUI->getStatLineHeight();
	attackUpgradeTitleImage->x = upgradeScreenGUI->getStatListX();
	attackUpgradeTitleImage->y = attackStatY;
	attackUpgradeTitleImage->z = 0;
	attackUpgradeTitleImage->imageID = attackUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(attackUpgradeTitleImage);

	/// text money
	OverlayImage *moneyUpgradeTitleImage2 = new OverlayImage();
	moneyUpgradeTitleImage2->alpha = 255;
	moneyUpgradeTitleImage2->width = upgradeScreenGUI->getStatTitleWidth();
	moneyUpgradeTitleImage2->height = upgradeScreenGUI->getStatLineHeight();
	moneyUpgradeTitleImage2->x = upgradeScreenGUI->getStatListX() + upgradeScreenGUI->getStatTitleWidth();
	moneyUpgradeTitleImage2->y = attackStatY;
	moneyUpgradeTitleImage2->z = 0;
	moneyUpgradeTitleImage2->imageID = moneyUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(moneyUpgradeTitleImage2);

	/// upgrade button
	Button *attackUpButton = new Button();
	int attackUpButtonX = speedUpButtonX;
	int attackUpButtonY = attackStatY;
	attackUpButton->initButton(upgradeButtonTID, moUpgradeButtonTID,
		attackUpButtonX, attackUpButtonY, 0, 255,
		upgradeButtonWidth, upgradeButtonHeight, true, ATTACK_UPGRADE_COMMAND);
	upgradeScreenGUI->addButton(attackUpButton);
	// -- attack component complete

	// 3rd component on list: defense
	int defenseStatY = attackStatY + upgradeScreenGUI->getStatLineHeight() + upgradeScreenGUI->getYDistBetweenStats();

	OverlayImage *defenseUpgradeTitleImage = new OverlayImage();
	defenseUpgradeTitleImage->alpha = 255;
	defenseUpgradeTitleImage->width = upgradeScreenGUI->getStatTitleWidth();
	defenseUpgradeTitleImage->height = upgradeScreenGUI->getStatLineHeight();
	defenseUpgradeTitleImage->x = upgradeScreenGUI->getStatListX();
	defenseUpgradeTitleImage->y = defenseStatY;
	defenseUpgradeTitleImage->z = 0;
	defenseUpgradeTitleImage->imageID = defenseUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(defenseUpgradeTitleImage);

	/*int defenseStatY = attackStatY + upgradeScreenGUI->getStatLineHeight() + upgradeScreenGUI->getYDistBetweenStats();

	Button *moneylabel = new Button();
	moneylabel->alpha = 255;
	moneylabel->width = upgradeScreenGUI->getStatTitleWidth();
	defenseUpgradeTitleImage->height = upgradeScreenGUI->getStatLineHeight();
	defenseUpgradeTitleImage->x = upgradeScreenGUI->getStatListX();
	defenseUpgradeTitleImage->y = defenseStatY;
	defenseUpgradeTitleImage->z = 0;
	defenseUpgradeTitleImage->imageID = defenseUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(defenseUpgradeTitleImage);*/
	OverlayImage *moneylabel = new OverlayImage();
	moneylabel->alpha = 255;
	moneylabel->width = upgradeScreenGUI->getStatTitleWidth();
	moneylabel->height = upgradeScreenGUI->getStatLineHeight();
	moneylabel->x = upgradeScreenGUI->getStatListX();
	moneylabel->y = defenseStatY + 170;
	moneylabel->z = 0;
	moneylabel->imageID = moneylabelTID;
	upgradeScreenGUI->addOverlayImage(moneylabel);

	Button *money = new Button();
	int moneyButtonX = upgradeScreenGUI->getStatListX() + 160;
	int moneyButtonY = defenseStatY + 170;
	money->initButton(moneytextTID, moneytextTID,
		moneyButtonX, moneyButtonY, 0, 255,
		100, 60, true, L"no command");
	upgradeScreenGUI->addButton(money);

	/// text money
	OverlayImage *moneyUpgradeTitleImage3 = new OverlayImage();
	moneyUpgradeTitleImage3->alpha = 255;
	moneyUpgradeTitleImage3->width = upgradeScreenGUI->getStatTitleWidth();
	moneyUpgradeTitleImage3->height = upgradeScreenGUI->getStatLineHeight();
	moneyUpgradeTitleImage3->x = upgradeScreenGUI->getStatListX() + upgradeScreenGUI->getStatTitleWidth();
	moneyUpgradeTitleImage3->y = defenseStatY;
	moneyUpgradeTitleImage3->z = 0;
	moneyUpgradeTitleImage3->imageID = moneyUpgradeTitleTID;
	upgradeScreenGUI->addOverlayImage(moneyUpgradeTitleImage3);

	/// upgrade button
	Button *defenseUpButton = new Button();
	int defenseUpButtonX = attackUpButtonX;
	int defenseUpButtonY = defenseStatY;
	defenseUpButton->initButton(upgradeButtonTID, moUpgradeButtonTID,
		defenseUpButtonX, defenseUpButtonY, 0, 255,
		upgradeButtonWidth, upgradeButtonHeight, true, DEFENSE_UPGRADE_COMMAND);
	upgradeScreenGUI->addButton(defenseUpButton);
	// -- defense component complete

	//// let's start adding control buttons
	int allButtonsPadding = 10;

	/// --- adding back_to_pause_menu button
	Button *backToPauseMenuButton = new Button();
	unsigned int backToPauseMenuButtonTID = guiTextureManager->loadTexture(BACK_TO_MENU_PATH);
	unsigned int moBackToPauseMenuButtonTID = guiTextureManager->loadTexture(BACK_TO_MENU_MO_PATH);
	int backTPMButtonWidth = 300;
	int backTPMButtonHeight = 60;
	int backTPMButtonX = upgradeScreenGUI->getScreenX() + 50;
	int backTPMButtonY = 700;

	backToPauseMenuButton->initButton(backToPauseMenuButtonTID, moBackToPauseMenuButtonTID,
		backTPMButtonX, backTPMButtonY, 0, 255,
		backTPMButtonWidth, backTPMButtonHeight, true, BACK_TO_PAUSE_MENU_COMMAND);

	upgradeScreenGUI->addButton(backToPauseMenuButton);
	/// --- back_to_pause_menu button complete

	//// game state: GS_UPGRADE_SCREEN
	//// when game reached GS_UPGRADE_SCREEN state, upgradeScreenGUI should be shown up 
	gui->addScreenGUI(GS_UPGRADE_SCREEN, upgradeScreenGUI);
}