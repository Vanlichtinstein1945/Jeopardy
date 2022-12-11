/*
--------------------------------------------------------------
-	This is a recreation of Jeopardy in C. This is meant as a-
-	programming project for CSE 130-50.                      -
----Authors:--------------------------------------------------
-	Brenan Patrick                                           -
-	Madison Russel                                           -
-	Terence Nacario                                          -
-	Jalyn Perry-Bell                                         -
----Dates Modified--------------------------------------------
-   June 13th, 2021                                          -
-   June 21st, 2021                                          -
-   July 19th, 2021                                          -
--------------------------------------------------------------	
*/

//------------------------------------------------------------
// Inclusions, Definitions, and Declarations
//------------------------------------------------------------
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

// Defining window size
#define APP_HEIGHT 500
#define APP_WIDTH 500

// Defining question file locations
#define anime ".\\questions\\anime\\questions.file"
#define plants ".\\questions\\plants\\questions.file"
#define lotr ".\\questions\\lotr\\questions.file"
#define star_wars ".\\questions\\star_wars\\questions.file"
#define nba ".\\questions\\nba\\questions.file"
#define ufc ".\\questions\\ufc\\questions.file"
#define animals ".\\questions\\animals\\questions.file"
#define music ".\\questions\\music\\questions.file"
#define shoes ".\\questions\\shoes\\questions.file"
#define geography ".\\questions\\geography\\questions.file"

// Defining the ID corresponders to buttons and cases for the
// main message queue to interpret
#define StartGame 0
#define QUIT 1

#define TwoPlayers 2
#define ThreePlayers 3
#define FourPlayers 4

#define savePlayers 5

#define cat1Quest1 6
#define cat2Quest1 7
#define cat3Quest1 8
#define cat4Quest1 9
#define cat5Quest1 34
#define cat1Quest2 11
#define cat2Quest2 12
#define cat3Quest2 13
#define cat4Quest2 14
#define cat5Quest2 15
#define cat1Quest3 16
#define cat2Quest3 17
#define cat3Quest3 18
#define cat4Quest3 19
#define cat5Quest3 20
#define cat1Quest4 21
#define cat2Quest4 22
#define cat3Quest4 23
#define cat4Quest4 24
#define cat5Quest4 25
#define cat1Quest5 26
#define cat2Quest5 27
#define cat3Quest5 28
#define cat4Quest5 29
#define cat5Quest5 30

#define backToMain 31

#define wrongAnswer 32
#define rightAnswer 33

#define ansButtonLeftX 10
#define ansButtonUpY 250
#define ansButtonRightX 260
#define ansButtonDownY 370
#define ansButtonWidth 230
#define ansButtonHeight 110

// Declaring the functions used and their parameters
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void LoadImages();
void ChooseCategories();
void playerMenu(HWND);
void PlayerSelect(HWND);
void removePlayerSelect();
void mainGame(HWND);
void questionBase(HWND, int);
void destroyMainGame();
void destroyQuestion(int);
void pullQuestions();
void randomPlayer();
void randomDailyDouble();
void endGame(HWND);

// Creating the 'questCat' variable type to save all of the properties for our different categories to
typedef struct questCat
{
	char catName[256];
	
	int quest1Disabled;
	int quest2Disabled;
	int quest3Disabled;
	int quest4Disabled;
	int quest5Disabled;
	
	HWND categoryHandler;
	
	HWND quest1Handler;
	HWND quest1TextHandler;
	HWND quest1Ans1Handler;
	HWND quest1Ans2Handler;
	HWND quest1Ans3Handler;
	HWND quest1Ans4Handler;
	
	HWND quest2Handler;
	HWND quest2TextHandler;
	HWND quest2Ans1Handler;
	HWND quest2Ans2Handler;
	HWND quest2Ans3Handler;
	HWND quest2Ans4Handler;
	
	HWND quest3Handler;
	HWND quest3TextHandler;
	HWND quest3Ans1Handler;
	HWND quest3Ans2Handler;
	HWND quest3Ans3Handler;
	HWND quest3Ans4Handler;
	
	HWND quest4Handler;
	HWND quest4TextHandler;
	HWND quest4Ans1Handler;
	HWND quest4Ans2Handler;
	HWND quest4Ans3Handler;
	HWND quest4Ans4Handler;
	
	HWND quest5Handler;
	HWND quest5TextHandler;
	HWND quest5Ans1Handler;
	HWND quest5Ans2Handler;
	HWND quest5Ans3Handler;
	HWND quest5Ans4Handler;
	
	char quest1Text[256];
	char quest1Ans1Text[256];
	char quest1Ans2Text[256];
	char quest1Ans3Text[256];
	char quest1Ans4Text[256];
	
	char quest2Text[256];
	char quest2Ans1Text[256];
	char quest2Ans2Text[256];
	char quest2Ans3Text[256];
	char quest2Ans4Text[256];
	
	char quest3Text[256];
	char quest3Ans1Text[256];
	char quest3Ans2Text[256];
	char quest3Ans3Text[256];
	char quest3Ans4Text[256];
	
	char quest4Text[256];
	char quest4Ans1Text[256];
	char quest4Ans2Text[256];
	char quest4Ans3Text[256];
	char quest4Ans4Text[256];
	
	char quest5Text[256];
	char quest5Ans1Text[256];
	char quest5Ans2Text[256];
	char quest5Ans3Text[256];
	char quest5Ans4Text[256];
	
} questCat;

// Declaring the category variables to save our questions and answers to
questCat category1 = { 0 };
questCat category2 = { 0 };
questCat category3 = { 0 };
questCat category4 = { 0 };
questCat category5 = { 0 };

// Declaring the handlers used throughout the program
// Handlers were grouped based on use in the program
HWND titleScreenHandler, startButtonHandler, quitButtonHandler;
HWND playerCountText, selectPlayers2Handler, selectPlayers3Handler, selectPlayers4Handler;
HWND playerNameStatic1, playerNameEdit1, playerNameStatic2, playerNameEdit2, playerNameStatic3, playerNameEdit3, playerNameStatic4, playerNameEdit4, savePlayersHandler;

HWND player1Turn, player2Turn, player3Turn, player4Turn;
HWND playersTurnTextHandler;
HWND player1ScoreTextHandler, player2ScoreTextHandler, player3ScoreTextHandler, player4ScoreTextHandler;
HWND winnerTextHandler, randomQuestHandler;

HWND questTextHandler, questAns1Handler, questAns2Handler, questAns3Handler, questAns4Handler;

// Declaring the variable used to import the Jeopardy image on
HBITMAP titleScreen;

// Declaring the variables for choosing a random 'Daily Double' and defining the list of
// categories to be randomly chosen from for the 5 used in game
char categories[10][10] = {"NBA", "Plants", "LOTR", "Star Wars", "Anime", "UFC", "Animals", "Music", "Shoes", "Geography"};
int randomQuest;
int randomQuestActive = 0;

// Declaring the variables used to save player count, names, and scores
int playersTurn = 1, playerCount, questID, currentCategories[5];
wchar_t player1Name[100], player2Name[100], player3Name[100], player4Name[100];
CHAR player1TurnText[100], player2TurnText[100], player3TurnText[100], player4TurnText[100];
int player1Score = 0, player2Score = 0, player3Score = 0, player4Score = 0;
int currentQuestScore = 0;

//------------------------------------------------------------
// Function definitions
//------------------------------------------------------------

// The main function that handles window creation and message handling
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	// Creating a 'WNDCLASSW' struct named 'wc'
	WNDCLASSW wc = {0};
	
	// Declaring the 'wc' struct's properties
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"windowClass";
	wc.lpfnWndProc = WindowProcedure;
	
	// Exiting the program if we were unable to register our new window class
	if(!RegisterClassW(&wc))
		return -1;
	
	// Grabbing the computer's current center location based on resolution
	int resolutionHeight = (GetSystemMetrics(SM_CYSCREEN)/2) - (APP_HEIGHT/2);
	int resolutionWidth = (GetSystemMetrics(SM_CXSCREEN)/2) - (APP_WIDTH/2);

	// Disabling the console from appearing when using the .exe version of this program
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	
/*
	CreateWindowW(LPCTSTR lpClassName,	- Name of the window class. Of type long string I.E. button, windowClass, static, etc.
				  LPCTSTR lpWindowName,	- Name of the window being created. Of type long string I.E. test window name
				  DWORD dwStyle,		- Styles the window should inherit. Of type 32-bit unsigned long I.E. WS_VISIBLE, WS_CHILD, SS_CENTER, etc.
				  int x,				- The x position in pixels of the left side of the window. Of type integer I.E. 0, 100, 300, etc.
				  int y,				- The y position in pixels of the top side of the window. Of type integer I.E. 0, 100, 300, etc.
				  int nWidth,			- The width of the window in pixels. Of type integer I.E. 0, 100, 300, etc.
				  int nHeight,			- The height of the window in pixels. Of type integer I.E. 0, 100, 300, etc.
				  HWND hWndParent,		- The parent handler to set this window in. Of type HWND
				  HMENU hMenu,			- The menu or ID that this window uses to interact with the message queue. Of type HMENU
				  HINSTANCE hInstance,	- The window's instance used to help lookup its DLL alongside the 'lpClassName'. Of type HINSTANCE I.E. USER32.DLL, A.DLL, B.DLL, etc.
				  WPARAM wpParam,		- The argument used to pass extra WORD paramters through. Of type WPARAM
				  LPARAM lpParam		- The argument used to pass extra long parameters through. Of type LPARAM
				  )
	This function returns its handler in the form of HWND I.E. windowHandler = CreateWindowW();
*/
	
	// Creating the base window that our game will be ran from
	CreateWindowW(L"windowClass", L"Jeopardy Game", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_VISIBLE, resolutionWidth, resolutionHeight, APP_WIDTH, APP_HEIGHT, NULL, NULL, NULL, NULL);
	
	// Creating the message struct to control the message queue
	MSG msg = {0};

	// Creating the while loop that interprets and operates on messages passed from the window
	while(GetMessage(&msg, NULL, 0, 4294967295))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	// Returning '0' if the function completed successfully
	return 0;
}

// The function that acts as our message queue decision maker based on what ID and WPARAM the message is passing
LRESULT CALLBACK WindowProcedure(HWND windowHandler, UINT msg, WPARAM wp, LPARAM lp)
{
	// Creating a variable for storing responses to secondary windows
	int val;
	
	// Switching through different cases. Performing certain actions if the message is equal to a case we've defined,
	// and sending the message through the default message queue if we aren't performing an action from it
	switch(msg)
	{
		// The case for a message stating that the window has been created for the first time
		case WM_CREATE:
			LoadImages();
			AddControls(windowHandler);
			ChooseCategories();
			break;
		// The case for when a button or menu returns a command as a message
		case WM_COMMAND:
			switch(wp)
			{
				// The case for when a command's WPARAM is equal to the ID 'StartGame'
				case StartGame:
					playerMenu(windowHandler);
					break;
				// The case for when a command's WPARAM is equal to the ID 'QUIT'
				case QUIT:
					// Creating a second window asking if the user really wants to quit and returning its value to 'val'
					val = MessageBoxW(windowHandler, L"Are you sure?", L"Quit?", MB_YESNO);
					if(val==IDYES)
					{
						DestroyWindow(windowHandler);
					}
					break;
				// The case for when a command's WPARAM is equal to the ID 'TwoPlayers'
				case TwoPlayers:
					playerCount = 2;
					PlayerSelect(windowHandler);
					break;
				// The case for when a command's WPARAM is equal to the ID 'ThreePlayers'
				case ThreePlayers:
					playerCount = 3;
					PlayerSelect(windowHandler);
					break;
				// The case for when a command's WPARAM is equal to the ID 'FourPlayers'
				case FourPlayers:
					playerCount = 4;
					PlayerSelect(windowHandler);
					break;
				// The case for when a command's WPARAM is equal to the ID 'savePlayers'
				case savePlayers:
					// Grabbing the text currently inside the handlers (I.E. 'playerNameEdit1') and setting the first
					// 100 characters to a variable (I.E. 'player1Name')
					GetWindowTextW(playerNameEdit1, player1Name, 100);
					GetWindowTextW(playerNameEdit2, player2Name, 100);
					GetWindowTextW(playerNameEdit3, player3Name, 100);
					GetWindowTextW(playerNameEdit4, player4Name, 100);
					removePlayerSelect();
					pullQuestions();
					randomDailyDouble();
					mainGame(windowHandler);
					break;
				// Rolling through the multiple cases testing if the button/menu's ID is calling a category/question
				// Selecting a random player, disabling the question from being chosen again, setting the score equal
				// to the question, and testing if the question is the 'Daily Double'
				case cat1Quest1:
					randomPlayer();
					questID = cat1Quest1;
					category1.quest1Disabled = 1;
					currentQuestScore = 100;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat1Quest1);
					break;
				case cat2Quest1:
					randomPlayer();
					questID = cat2Quest1;
					category2.quest1Disabled = 1;
					currentQuestScore = 100;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat2Quest1);
					break;
				case cat3Quest1:
					randomPlayer();
					questID = cat3Quest1;
					category3.quest1Disabled = 1;
					currentQuestScore = 100;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat3Quest1);
					break;
				case cat4Quest1:
					randomPlayer();
					questID = cat4Quest1;
					category4.quest1Disabled = 1;
					currentQuestScore = 100;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat4Quest1);
					break;
				case cat5Quest1:
					randomPlayer();
					questID = cat5Quest1;
					category5.quest1Disabled = 1;
					currentQuestScore = 100;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat5Quest1);
					break;
				case cat1Quest2:
					randomPlayer();
					questID = cat1Quest2;
					category1.quest2Disabled = 1;
					currentQuestScore = 200;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat1Quest2);
					break;
				case cat2Quest2:
					randomPlayer();
					questID = cat2Quest2;
					category2.quest2Disabled = 1;
					currentQuestScore = 200;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat2Quest2);
					break;
				case cat3Quest2:
					randomPlayer();
					questID = cat3Quest2;
					category3.quest2Disabled = 1;
					currentQuestScore = 200;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat3Quest2);
					break;
				case cat4Quest2:
					randomPlayer();
					questID = cat4Quest2;
					category4.quest2Disabled = 1;
					currentQuestScore = 200;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat4Quest2);
					break;
				case cat5Quest2:
					randomPlayer();
					questID = cat5Quest2;
					category5.quest2Disabled = 1;
					currentQuestScore = 200;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat5Quest2);
					break;
				case cat1Quest3:
					randomPlayer();
					questID = cat1Quest3;
					category1.quest3Disabled = 1;
					currentQuestScore = 300;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat1Quest3);
					break;
				case cat2Quest3:
					randomPlayer();
					questID = cat2Quest3;
					category2.quest3Disabled = 1;
					currentQuestScore = 300;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat2Quest3);
					break;
				case cat3Quest3:
					randomPlayer();
					questID = cat3Quest3;
					category3.quest3Disabled = 1;
					currentQuestScore = 300;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat3Quest3);
					break;
				case cat4Quest3:
					randomPlayer();
					questID = cat4Quest3;
					category4.quest3Disabled = 1;
					currentQuestScore = 300;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat4Quest3);
					break;
				case cat5Quest3:
					randomPlayer();
					questID = cat5Quest3;
					category5.quest3Disabled = 1;
					currentQuestScore = 300;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat5Quest3);
					break;
				case cat1Quest4:
					randomPlayer();
					questID = cat1Quest4;
					category1.quest4Disabled = 1;
					currentQuestScore = 400;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat1Quest4);
					break;
				case cat2Quest4:
					randomPlayer();
					questID = cat2Quest4;
					category2.quest4Disabled = 1;
					currentQuestScore = 400;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat2Quest4);
					break;
				case cat3Quest4:
					randomPlayer();
					questID = cat3Quest4;
					category3.quest4Disabled = 1;
					currentQuestScore = 400;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat3Quest4);
					break;
				case cat4Quest4:
					randomPlayer();
					questID = cat4Quest4;
					category4.quest4Disabled = 1;
					currentQuestScore = 400;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat4Quest4);
					break;
				case cat5Quest4:
					randomPlayer();
					questID = cat5Quest4;
					category5.quest4Disabled = 1;
					currentQuestScore = 400;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat5Quest4);
					break;
				case cat1Quest5:
					randomPlayer();
					questID = cat1Quest5;
					category1.quest5Disabled = 1;
					currentQuestScore = 500;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat1Quest5);
					break;
				case cat2Quest5:
					randomPlayer();
					questID = cat2Quest5;
					category2.quest5Disabled = 1;
					currentQuestScore = 500;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat2Quest5);
					break;
				case cat3Quest5:
					randomPlayer();
					questID = cat3Quest5;
					category3.quest5Disabled = 1;
					currentQuestScore = 500;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat3Quest5);
					break;
				case cat4Quest5:
					randomPlayer();
					questID = cat4Quest5;
					category4.quest5Disabled = 1;
					currentQuestScore = 500;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat4Quest5);
					break;
				case cat5Quest5:
					randomPlayer();
					questID = cat5Quest5;
					category5.quest5Disabled = 1;
					currentQuestScore = 500;
					if (questID==randomQuest)
					{
						currentQuestScore *= 2;
						randomQuestActive = 1;
					}
					questionBase(windowHandler, cat5Quest5);
					break;
				// The case for when a command's WPARAM is equal to the ID 'wrongAnswer'
				case wrongAnswer:
					// Upticking the player by one position and resetting it to the first player if it reaches the max
					if(playerCount==2)
					{
						if(playersTurn<2)
						{
							playersTurn++;
						} else {
							playersTurn = 1;
						}
					} else if(playerCount==3) {
						if(playersTurn<3)
						{
							playersTurn++;
						} else {
							playersTurn = 1;
						}
					} else if(playerCount==4) {
						if(playersTurn<4)
						{
							playersTurn++;
						} else {
							playersTurn = 1;
						}
					}
					destroyQuestion(questID);
					questionBase(windowHandler, questID);
					break;
				// The case for when a command's WPARAM is equal to the ID 'rightAnswer'
				case rightAnswer:
					// Adding the question's score to the active player's score
					if(playersTurn==1)
					{
						player1Score+=currentQuestScore;
					} else if(playersTurn==2) {
						player2Score+=currentQuestScore;
					} else if(playersTurn==3) {
						player3Score+=currentQuestScore;
					} else if(playersTurn==4) {
						player4Score+=currentQuestScore;
					}
					destroyQuestion(questID);
					// Resetting the 'Daily Double' if this question was it
					randomQuestActive = 0;
					mainGame(windowHandler);
					break;
			} break;
		// The case for when the window is being destroyed I.E. Pressing the 'X' button
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		// Setting any non-specified messages to the standard queue to be automatically handled
		default:
			return DefWindowProcW(windowHandler, msg, wp, lp);
	}
}

// The function for creating the opening title screen
void AddControls(HWND windowHandler)
{
	// Placing the 'Jeopardy' image in the window
	titleScreenHandler = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 500, 300, windowHandler, NULL, NULL, NULL);
	SendMessageW(titleScreenHandler, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)titleScreen);

	// Placing the 'Start' and 'Quit' buttons on the window
	startButtonHandler = CreateWindowW(L"button", L"Start Game", WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-50, 338, 100, 25, windowHandler, (HMENU)StartGame, NULL, NULL);
	quitButtonHandler = CreateWindowW(L"button", L"Quit", WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-50, 388, 100, 25, windowHandler, (HMENU)QUIT, NULL, NULL);
}

// The function for loading the 'Jeopardy' image from the directory
void LoadImages()
{
	titleScreen = (HBITMAP)LoadImageW(NULL, L".\\images\\title.bmp", IMAGE_BITMAP, 500, 300, LR_LOADFROMFILE);
}

// The function for randomly choosing 5 categories from our list of 10
void ChooseCategories()
{
	// Selecting a random seed so it isn't predictable
	srand(time(NULL));
	int choosing, currentChoice, choice1, choice2, choice3, choice4, choice5;
	
	// Looping 5 times to pull 5 random categories
	for(int i=0; i<5; i++)
	{
		choosing=0;
		
		// Creating a while loop to ensure we don't choose the same category twice
		while(choosing==0)
		{
			// Choosing a random category from 0 to 9
			currentChoice = rand() % 10;
			
			// Testing if this category has already been chosen this run
			if(currentChoice!=choice1 && currentChoice!=choice2 && currentChoice!=choice3 && currentChoice!=choice4 && currentChoice!=choice5)
				choosing=1;
		}
		
		// Setting the random choice into the earlier specified variables to test against for duplicates
		if(i==0)
			choice1 = currentChoice;
		else if(i==1)
			choice2 = currentChoice;
		else if(i==2)
			choice3 = currentChoice;
		else if(i==3)
			choice4 = currentChoice;
		else if(i==4)
			choice5 = currentChoice;
		
		// Setting the chosen category into the list 'currentCategories' in the i'nth place
		currentCategories[i] = currentChoice;
	}
}

// The function for selecting the player amount
void playerMenu(HWND windowHandler)
{
	// Destroying the items currently on the window, so we can place our new items on an empty surface
	DestroyWindow(titleScreenHandler);
	DestroyWindow(startButtonHandler);
	DestroyWindow(quitButtonHandler);
	
	// Creating the text and buttons for the player to select the player count from
	// The button selected will return a message to our 'WindowProcedure' to test the case against the ID I.E. 'TwoPlayers'
	playerCountText = CreateWindowW(L"static", L"How many players?", WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-50, 150, 100, 50, windowHandler, NULL, NULL, NULL);
	selectPlayers2Handler = CreateWindowW(L"button", L"2 Players", WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-50, 190, 100, 25, windowHandler, (HMENU)TwoPlayers, NULL, NULL);
	selectPlayers3Handler = CreateWindowW(L"button", L"3 Players", WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-50, 215, 100, 25, windowHandler, (HMENU)ThreePlayers, NULL, NULL);
	selectPlayers4Handler = CreateWindowW(L"button", L"4 Players", WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-50, 240, 100, 25, windowHandler, (HMENU)FourPlayers, NULL, NULL);
}

// The function for entering the players names based on the player count previously chosen
void PlayerSelect(HWND windowHandler)
{
	// Destroying the items currently on the window, so we can place our new items on an empty surface
	DestroyWindow(playerCountText);
	DestroyWindow(selectPlayers2Handler);
	DestroyWindow(selectPlayers3Handler);
	DestroyWindow(selectPlayers4Handler);
	
	// Allowing the input of 2 names
	playerNameStatic1 = CreateWindowW(L"static", L"Enter Player 1 name:", WS_VISIBLE | WS_CHILD, 75, 50, 100, 50, windowHandler, NULL, NULL, NULL);
	playerNameEdit1 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 75, 110, 100, 50, windowHandler, NULL, NULL, NULL);
	playerNameStatic2 = CreateWindowW(L"static", L"Enter Player 2 name:", WS_VISIBLE | WS_CHILD, 325, 50, 100, 50, windowHandler, NULL, NULL, NULL);
	playerNameEdit2 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 325, 110, 100, 50, windowHandler, NULL, NULL, NULL);
	// Allowing the input of 3 names if 3 player mode was selected
	if(playerCount > 2) {
		playerNameStatic3 = CreateWindowW(L"static", L"Enter Player 3 name:", WS_VISIBLE | WS_CHILD, 75, 250, 100, 50, windowHandler, NULL, NULL, NULL);
		playerNameEdit3 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 75, 310, 100, 50, windowHandler, NULL, NULL, NULL);
	// Allowing the input of 4 names if 4 player mode was selected
	}
	if(playerCount > 3) {
		playerNameStatic4 = CreateWindowW(L"static", L"Enter Player 4 name:", WS_VISIBLE | WS_CHILD, 325, 250, 100, 50, windowHandler, NULL, NULL, NULL);
		playerNameEdit4 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 325, 310, 100, 50, windowHandler, NULL, NULL, NULL);
	}

	// Creating the button to be clicked when the players have finished entering names
	savePlayersHandler = CreateWindowW(L"button", L"Continue", WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-50, 400, 100, 25, windowHandler, (HMENU)savePlayers, NULL, NULL);
}

// The function for removing the 'PlayerSelect' items (I.E. 'playernameStatic1') and creating the strings to be used
// by the labels in the next section of the window
void removePlayerSelect()
{
	// Destroying the items currently on the window, so we can place our new items on an empty surface
	DestroyWindow(playerNameStatic1);
	DestroyWindow(playerNameEdit1);
	DestroyWindow(playerNameStatic2);
	DestroyWindow(playerNameEdit2);
	DestroyWindow(savePlayersHandler);
	if(playerCount > 2)
	{
		DestroyWindow(playerNameStatic3);
		DestroyWindow(playerNameEdit3);
	}
	if(playerCount > 3)
	{
		DestroyWindow(playerNameStatic4);
		DestroyWindow(playerNameEdit4);
	}

	// Saving a formatted string to a variable to be used in the labels later. In this case, we're saving the formatted
	// text to the 'player1TurnText' variable
	sprintf(player1TurnText, "%ls, choose the category and question.", player1Name);
	sprintf(player2TurnText, "%ls, choose the category and question.", player2Name);
	sprintf(player3TurnText, "%ls, choose the category and question.", player3Name);
	sprintf(player4TurnText, "%ls, choose the category and question.", player4Name);
}

// The function for handling the main portion of the game: showing player score and choosing category and question
void mainGame(HWND windowHandler)
{	
	// Crating the labels at the top of each category. We're calling the lists 'categories' and 'currentCategories' to
	// modulate the label and not have to test which categories were chosen. We can just call them from the lists
	category1.categoryHandler = CreateWindow("static", categories[currentCategories[0]], WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 100, 25, windowHandler, NULL, NULL, NULL);
	category2.categoryHandler = CreateWindow("static", categories[currentCategories[1]], WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 0, 100, 25, windowHandler, NULL, NULL, NULL);
	category3.categoryHandler = CreateWindow("static", categories[currentCategories[2]], WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 0, 100, 25, windowHandler, NULL, NULL, NULL);
	category4.categoryHandler = CreateWindow("static", categories[currentCategories[3]], WS_VISIBLE | WS_CHILD | SS_CENTER, 300, 0, 100, 25, windowHandler, NULL, NULL, NULL);
	category5.categoryHandler = CreateWindow("static", categories[currentCategories[4]], WS_VISIBLE | WS_CHILD | SS_CENTER, 400, 0, 100, 25, windowHandler, NULL, NULL, NULL);

	// Creating the buttons for the 1st question in each category. The question will not be displayed if 'Disabled==1',
	// because this means that we've already called this question before
	if(category1.quest1Disabled==0)
	{
		category1.quest1Handler = CreateWindowW(L"button", L"100", WS_VISIBLE | WS_CHILD, 0, 25, 100, 25, windowHandler, (HMENU)cat1Quest1, NULL, NULL);
	}
	if(category2.quest1Disabled==0)
	{
		category2.quest1Handler = CreateWindowW(L"button", L"100", WS_VISIBLE | WS_CHILD, 100, 25, 100, 25, windowHandler, (HMENU)cat2Quest1, NULL, NULL);
	}
	if(category3.quest1Disabled==0)
	{
		category3.quest1Handler = CreateWindowW(L"button", L"100", WS_VISIBLE | WS_CHILD, 200, 25, 100, 25, windowHandler, (HMENU)cat3Quest1, NULL, NULL);
	}
	if(category4.quest1Disabled==0)
	{
		category4.quest1Handler = CreateWindowW(L"button", L"100", WS_VISIBLE | WS_CHILD, 300, 25, 100, 25, windowHandler, (HMENU)cat4Quest1, NULL, NULL);
	}
	if(category5.quest1Disabled==0)
	{
		category5.quest1Handler = CreateWindowW(L"button", L"100", WS_VISIBLE | WS_CHILD, 400, 25, 100, 25, windowHandler, (HMENU)cat5Quest1, NULL, NULL);
	}
	
	// Creating the buttons for the 2nd question in each category. The question will not be displayed if 'Disabled==1',
	// because this means that we've already called this question before
	if(category1.quest2Disabled==0)
	{
		category1.quest2Handler = CreateWindowW(L"button", L"200", WS_VISIBLE | WS_CHILD, 0, 50, 100, 25, windowHandler, (HMENU)cat1Quest2, NULL, NULL);
	}
	if(category2.quest2Disabled==0)
	{
		category2.quest2Handler = CreateWindowW(L"button", L"200", WS_VISIBLE | WS_CHILD, 100, 50, 100, 25, windowHandler, (HMENU)cat2Quest2, NULL, NULL);
	}
	if(category3.quest2Disabled==0)
	{
		category3.quest2Handler = CreateWindowW(L"button", L"200", WS_VISIBLE | WS_CHILD, 200, 50, 100, 25, windowHandler, (HMENU)cat3Quest2, NULL, NULL);
	}
	if(category4.quest2Disabled==0)
	{
		category4.quest2Handler = CreateWindowW(L"button", L"200", WS_VISIBLE | WS_CHILD, 300, 50, 100, 25, windowHandler, (HMENU)cat4Quest2, NULL, NULL);
	}
	if(category5.quest2Disabled==0)
	{
		category5.quest2Handler = CreateWindowW(L"button", L"200", WS_VISIBLE | WS_CHILD, 400, 50, 100, 25, windowHandler, (HMENU)cat5Quest2, NULL, NULL);
	}
	
	// Creating the buttons for the 3rd question in each category. The question will not be displayed if 'Disabled==1',
	// because this means that we've already called this question before
	if(category1.quest3Disabled==0)
	{
		category1.quest3Handler = CreateWindowW(L"button", L"300", WS_VISIBLE | WS_CHILD, 0, 75, 100, 25, windowHandler, (HMENU)cat1Quest3, NULL, NULL);
	}
	if(category2.quest3Disabled==0)
	{
		category2.quest3Handler = CreateWindowW(L"button", L"300", WS_VISIBLE | WS_CHILD, 100, 75, 100, 25, windowHandler, (HMENU)cat2Quest3, NULL, NULL);
	}
	if(category3.quest3Disabled==0)
	{
		category3.quest3Handler = CreateWindowW(L"button", L"300", WS_VISIBLE | WS_CHILD, 200, 75, 100, 25, windowHandler, (HMENU)cat3Quest3, NULL, NULL);
	}
	if(category4.quest3Disabled==0)
	{
		category4.quest3Handler = CreateWindowW(L"button", L"300", WS_VISIBLE | WS_CHILD, 300, 75, 100, 25, windowHandler, (HMENU)cat4Quest3, NULL, NULL);
	}
	if(category5.quest3Disabled==0)
	{
		category5.quest3Handler = CreateWindowW(L"button", L"300", WS_VISIBLE | WS_CHILD, 400, 75, 100, 25, windowHandler, (HMENU)cat5Quest3, NULL, NULL);
	}

	// Creating the buttons for the 4th question in each category. The question will not be displayed if 'Disabled==1',
	// because this means that we've already called this question before
	if(category1.quest4Disabled==0)
	{
		category1.quest4Handler = CreateWindowW(L"button", L"400", WS_VISIBLE | WS_CHILD, 0, 100, 100, 25, windowHandler, (HMENU)cat1Quest4, NULL, NULL);
	}
	if(category2.quest4Disabled==0)
	{
		category2.quest4Handler = CreateWindowW(L"button", L"400", WS_VISIBLE | WS_CHILD, 100, 100, 100, 25, windowHandler, (HMENU)cat2Quest4, NULL, NULL);
	}
	if(category3.quest4Disabled==0)
	{
		category3.quest4Handler = CreateWindowW(L"button", L"400", WS_VISIBLE | WS_CHILD, 200, 100, 100, 25, windowHandler, (HMENU)cat3Quest4, NULL, NULL);
	}
	if(category4.quest4Disabled==0)
	{
		category4.quest4Handler = CreateWindowW(L"button", L"400", WS_VISIBLE | WS_CHILD, 300, 100, 100, 25, windowHandler, (HMENU)cat4Quest4, NULL, NULL);
	}
	if(category5.quest4Disabled==0)
	{
		category5.quest4Handler = CreateWindowW(L"button", L"400", WS_VISIBLE | WS_CHILD, 400, 100, 100, 25, windowHandler, (HMENU)cat5Quest4, NULL, NULL);
	}
	
	// Creating the buttons for the 5th question in each category. The question will not be displayed if 'Disabled==1',
	// because this means that we've already called this question before
	if(category1.quest5Disabled==0)
	{
		category1.quest5Handler = CreateWindowW(L"button", L"500", WS_VISIBLE | WS_CHILD, 0, 125, 100, 25, windowHandler, (HMENU)cat1Quest5, NULL, NULL);
	}
	if(category2.quest5Disabled==0)
	{
		category2.quest5Handler = CreateWindowW(L"button", L"500", WS_VISIBLE | WS_CHILD, 100, 125, 100, 25, windowHandler, (HMENU)cat2Quest5, NULL, NULL);
	}
	if(category3.quest5Disabled==0)
	{
		category3.quest5Handler = CreateWindowW(L"button", L"500", WS_VISIBLE | WS_CHILD, 200, 125, 100, 25, windowHandler, (HMENU)cat3Quest5, NULL, NULL);
	}
	if(category4.quest5Disabled==0)
	{
		category4.quest5Handler = CreateWindowW(L"button", L"500", WS_VISIBLE | WS_CHILD, 300, 125, 100, 25, windowHandler, (HMENU)cat4Quest5, NULL, NULL);
	}
	if(category5.quest5Disabled==0)
	{
		category5.quest5Handler = CreateWindowW(L"button", L"500", WS_VISIBLE | WS_CHILD, 400, 125, 100, 25, windowHandler, (HMENU)cat5Quest5, NULL, NULL);
	}

	// Creating the label for displaying whose turn it is and changing the text based on 'playersTurn'
	if(playersTurn==1)
	{
		player1Turn = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-100, (APP_HEIGHT/2)-25, 200, 50, windowHandler, NULL, NULL, NULL);
		SendMessage(player1Turn, WM_SETTEXT, 0, (LPARAM)player1TurnText);
	} else if(playersTurn==2) {
		player2Turn = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-100, (APP_HEIGHT/2)-25, 200, 50, windowHandler, NULL, NULL, NULL);
		SendMessage(player2Turn, WM_SETTEXT, 0, (LPARAM)player2TurnText);
	} else if(playersTurn==3) {
		player3Turn = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-100, (APP_HEIGHT/2)-25, 200, 50, windowHandler, NULL, NULL, NULL);
		SendMessage(player3Turn, WM_SETTEXT, 0, (LPARAM)player3TurnText);
	} else if(playersTurn==4) {
		player4Turn = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD, (APP_WIDTH/2)-100, (APP_HEIGHT/2)-25, 200, 50, windowHandler, NULL, NULL, NULL);
		SendMessage(player4Turn, WM_SETTEXT, 0, (LPARAM)player4TurnText);
	}
	
	// Creating the variables for setting player's formatted scores into
	CHAR player1ScoreText[256], player2ScoreText[256], player3ScoreText[256], player4ScoreText[256];
	sprintf(player1ScoreText, "%ls's score: %d", player1Name, player1Score);
	sprintf(player2ScoreText, "%ls's score: %d", player2Name, player2Score);
	sprintf(player3ScoreText, "%ls's score: %d", player3Name, player3Score);
	sprintf(player4ScoreText, "%ls's score: %d", player4Name, player4Score);
	
	// Displaying player scores based on how many players were selected previously
	player1ScoreTextHandler = CreateWindow("static", player1ScoreText, WS_VISIBLE | WS_CHILD | SS_CENTER, 45, 350, 75, 50, windowHandler, NULL, NULL, NULL);
	player2ScoreTextHandler = CreateWindow("static", player2ScoreText, WS_VISIBLE | WS_CHILD | SS_CENTER, 145, 350, 75, 50, windowHandler, NULL, NULL, NULL);
	if(playerCount>2)
	{
		player3ScoreTextHandler = CreateWindow("static", player3ScoreText, WS_VISIBLE | WS_CHILD | SS_CENTER, 245, 350, 75, 50, windowHandler, NULL, NULL, NULL);
	}
	if(playerCount>3)
	{
		player4ScoreTextHandler = CreateWindow("static", player4ScoreText, WS_VISIBLE | WS_CHILD | SS_CENTER, 345, 350, 75, 50, windowHandler, NULL, NULL, NULL);
	}
	
	// Checking if all questions have been used, if so, go to the endGame screen
	if(category1.quest1Disabled==1 && category1.quest2Disabled==1 && category1.quest3Disabled==1 && category1.quest4Disabled==1 && category1.quest5Disabled==1 &&
	   category2.quest1Disabled==1 && category2.quest2Disabled==1 && category2.quest3Disabled==1 && category2.quest4Disabled==1 && category2.quest5Disabled==1 &&
	   category3.quest1Disabled==1 && category3.quest2Disabled==1 && category3.quest3Disabled==1 && category3.quest4Disabled==1 && category3.quest5Disabled==1 &&
	   category4.quest1Disabled==1 && category4.quest2Disabled==1 && category4.quest3Disabled==1 && category4.quest4Disabled==1 && category4.quest5Disabled==1 &&
	   category5.quest1Disabled==1 && category5.quest2Disabled==1 && category5.quest3Disabled==1 && category5.quest4Disabled==1 && category5.quest5Disabled==1)
	{
		endGame(windowHandler);
	}
}

// The function that acts as the base for each question to work off of. Creates the question and answer buttons based
// on which question was chosen by the player
void questionBase(HWND windowHandler, int buttonID)
{
	// Calling the function to destroy the items still on screen from the mainGame window
	destroyMainGame();
	
	// Creating the variable to save the current player's turn formatted text into
	CHAR playersTurnText[100];
	
	// Creating the buffers to save our questions and answers to
	CHAR questBuff[256];
	CHAR questAns1Buff[256];
	CHAR questAns2Buff[256];
	CHAR questAns3Buff[256];
	CHAR questAns4Buff[256];
	
	// Updating the 'playersTurnText' variable based on whose turn it is
	if(playersTurn==1)
	{
		sprintf(playersTurnText, "It is %ls's turn!", player1Name);
	} else if(playersTurn==2) {
		sprintf(playersTurnText, "It is %ls's turn!", player2Name);
	} else if(playersTurn==3) {
		sprintf(playersTurnText, "It is %ls's turn!", player3Name);
	} else if(playersTurn==4) {
		sprintf(playersTurnText, "It is %ls's turn!", player4Name);
	}
	
	// Displaying the current players turn to the window
	playersTurnTextHandler = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 20, 500, 100, windowHandler, NULL, NULL, NULL);
	SendMessage(playersTurnTextHandler, WM_SETTEXT, 0, (LPARAM)playersTurnText);
	
	// Displaying 'Daily Double!' if the 'randomQuestActive==1' meaning that this question was
	// the randomly chose 'Daily Double'
	if(randomQuestActive==1)
	{
		randomQuestHandler = CreateWindowW(L"static", L"Daily Double!", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 120, 500, 30, windowHandler, NULL, NULL, NULL);
	}
	
	// Changing the text of the buttons and labels based on which question was passed
	if(buttonID==cat1Quest1)
	{
		sprintf(questBuff, "%s", category1.quest1Text);
		sprintf(questAns1Buff, "%s", category1.quest1Ans1Text);
		sprintf(questAns2Buff, "%s", category1.quest1Ans2Text);
		sprintf(questAns3Buff, "%s", category1.quest1Ans3Text);
		sprintf(questAns4Buff, "%s", category1.quest1Ans4Text);
	} else if(buttonID==cat2Quest1) {
		sprintf(questBuff, "%s", category2.quest1Text);
		sprintf(questAns1Buff, "%s", category2.quest1Ans1Text);
		sprintf(questAns2Buff, "%s", category2.quest1Ans2Text);
		sprintf(questAns3Buff, "%s", category2.quest1Ans3Text);
		sprintf(questAns4Buff, "%s", category2.quest1Ans4Text);
	} else if(buttonID==cat3Quest1) {
		sprintf(questBuff, "%s", category3.quest1Text);
		sprintf(questAns1Buff, "%s", category3.quest1Ans1Text);
		sprintf(questAns2Buff, "%s", category3.quest1Ans2Text);
		sprintf(questAns3Buff, "%s", category3.quest1Ans3Text);
		sprintf(questAns4Buff, "%s", category3.quest1Ans4Text);
	} else if(buttonID==cat4Quest1) {
		sprintf(questBuff, "%s", category4.quest1Text);
		sprintf(questAns1Buff, "%s", category4.quest1Ans1Text);
		sprintf(questAns2Buff, "%s", category4.quest1Ans2Text);
		sprintf(questAns3Buff, "%s", category4.quest1Ans3Text);
		sprintf(questAns4Buff, "%s", category4.quest1Ans4Text);
	} else if(buttonID==cat5Quest1) {
		sprintf(questBuff, "%s", category5.quest1Text);
		sprintf(questAns1Buff, "%s", category5.quest1Ans1Text);
		sprintf(questAns2Buff, "%s", category5.quest1Ans2Text);
		sprintf(questAns3Buff, "%s", category5.quest1Ans3Text);
		sprintf(questAns4Buff, "%s", category5.quest1Ans4Text);
	} else if(buttonID==cat1Quest2) {
		sprintf(questBuff, "%s", category1.quest2Text);
		sprintf(questAns1Buff, "%s", category1.quest2Ans1Text);
		sprintf(questAns2Buff, "%s", category1.quest2Ans2Text);
		sprintf(questAns3Buff, "%s", category1.quest2Ans3Text);
		sprintf(questAns4Buff, "%s", category1.quest2Ans4Text);
	} else if(buttonID==cat2Quest2) {
		sprintf(questBuff, "%s", category2.quest2Text);
		sprintf(questAns1Buff, "%s", category2.quest2Ans1Text);
		sprintf(questAns2Buff, "%s", category2.quest2Ans2Text);
		sprintf(questAns3Buff, "%s", category2.quest2Ans3Text);
		sprintf(questAns4Buff, "%s", category2.quest2Ans4Text);
	} else if(buttonID==cat3Quest2) {
		sprintf(questBuff, "%s", category3.quest2Text);
		sprintf(questAns1Buff, "%s", category3.quest2Ans1Text);
		sprintf(questAns2Buff, "%s", category3.quest2Ans2Text);
		sprintf(questAns3Buff, "%s", category3.quest2Ans3Text);
		sprintf(questAns4Buff, "%s", category3.quest2Ans4Text);
	} else if(buttonID==cat4Quest2) {
		sprintf(questBuff, "%s", category4.quest2Text);
		sprintf(questAns1Buff, "%s", category4.quest2Ans1Text);
		sprintf(questAns2Buff, "%s", category4.quest2Ans2Text);
		sprintf(questAns3Buff, "%s", category4.quest2Ans3Text);
		sprintf(questAns4Buff, "%s", category4.quest2Ans4Text);
	} else if(buttonID==cat5Quest2) {
		sprintf(questBuff, "%s", category5.quest2Text);
		sprintf(questAns1Buff, "%s", category5.quest2Ans1Text);
		sprintf(questAns2Buff, "%s", category5.quest2Ans2Text);
		sprintf(questAns3Buff, "%s", category5.quest2Ans3Text);
		sprintf(questAns4Buff, "%s", category5.quest2Ans4Text);
	} else if(buttonID==cat1Quest3) {
		sprintf(questBuff, "%s", category1.quest3Text);
		sprintf(questAns1Buff, "%s", category1.quest3Ans1Text);
		sprintf(questAns2Buff, "%s", category1.quest3Ans2Text);
		sprintf(questAns3Buff, "%s", category1.quest3Ans3Text);
		sprintf(questAns4Buff, "%s", category1.quest3Ans4Text);
	} else if(buttonID==cat2Quest3) {
		sprintf(questBuff, "%s", category2.quest3Text);
		sprintf(questAns1Buff, "%s", category2.quest3Ans1Text);
		sprintf(questAns2Buff, "%s", category2.quest3Ans2Text);
		sprintf(questAns3Buff, "%s", category2.quest3Ans3Text);
		sprintf(questAns4Buff, "%s", category2.quest3Ans4Text);
	} else if(buttonID==cat3Quest3) {
		sprintf(questBuff, "%s", category3.quest3Text);
		sprintf(questAns1Buff, "%s", category3.quest3Ans1Text);
		sprintf(questAns2Buff, "%s", category3.quest3Ans2Text);
		sprintf(questAns3Buff, "%s", category3.quest3Ans3Text);
		sprintf(questAns4Buff, "%s", category3.quest3Ans4Text);
	} else if(buttonID==cat4Quest3) {
		sprintf(questBuff, "%s", category4.quest3Text);
		sprintf(questAns1Buff, "%s", category4.quest3Ans1Text);
		sprintf(questAns2Buff, "%s", category4.quest3Ans2Text);
		sprintf(questAns3Buff, "%s", category4.quest3Ans3Text);
		sprintf(questAns4Buff, "%s", category4.quest3Ans4Text);
	} else if(buttonID==cat5Quest3) {
		sprintf(questBuff, "%s", category5.quest3Text);
		sprintf(questAns1Buff, "%s", category5.quest3Ans1Text);
		sprintf(questAns2Buff, "%s", category5.quest3Ans2Text);
		sprintf(questAns3Buff, "%s", category5.quest3Ans3Text);
		sprintf(questAns4Buff, "%s", category5.quest3Ans4Text);
	} else if(buttonID==cat1Quest4) {
		sprintf(questBuff, "%s", category1.quest4Text);
		sprintf(questAns1Buff, "%s", category1.quest4Ans1Text);
		sprintf(questAns2Buff, "%s", category1.quest4Ans2Text);
		sprintf(questAns3Buff, "%s", category1.quest4Ans3Text);
		sprintf(questAns4Buff, "%s", category1.quest4Ans4Text);
	} else if(buttonID==cat2Quest4) {
		sprintf(questBuff, "%s", category2.quest4Text);
		sprintf(questAns1Buff, "%s", category2.quest4Ans1Text);
		sprintf(questAns2Buff, "%s", category2.quest4Ans2Text);
		sprintf(questAns3Buff, "%s", category2.quest4Ans3Text);
		sprintf(questAns4Buff, "%s", category2.quest4Ans4Text);
	} else if(buttonID==cat3Quest4) {
		sprintf(questBuff, "%s", category3.quest4Text);
		sprintf(questAns1Buff, "%s", category3.quest4Ans1Text);
		sprintf(questAns2Buff, "%s", category3.quest4Ans2Text);
		sprintf(questAns3Buff, "%s", category3.quest4Ans3Text);
		sprintf(questAns4Buff, "%s", category3.quest4Ans4Text);
	} else if(buttonID==cat4Quest4) {
		sprintf(questBuff, "%s", category4.quest4Text);
		sprintf(questAns1Buff, "%s", category4.quest4Ans1Text);
		sprintf(questAns2Buff, "%s", category4.quest4Ans2Text);
		sprintf(questAns3Buff, "%s", category4.quest4Ans3Text);
		sprintf(questAns4Buff, "%s", category4.quest4Ans4Text);
	} else if(buttonID==cat5Quest4) {
		sprintf(questBuff, "%s", category5.quest4Text);
		sprintf(questAns1Buff, "%s", category5.quest4Ans1Text);
		sprintf(questAns2Buff, "%s", category5.quest4Ans2Text);
		sprintf(questAns3Buff, "%s", category5.quest4Ans3Text);
		sprintf(questAns4Buff, "%s", category5.quest4Ans4Text);
	} else if(buttonID==cat1Quest5) {
		sprintf(questBuff, "%s", category1.quest5Text);
		sprintf(questAns1Buff, "%s", category1.quest5Ans1Text);
		sprintf(questAns2Buff, "%s", category1.quest5Ans2Text);
		sprintf(questAns3Buff, "%s", category1.quest5Ans3Text);
		sprintf(questAns4Buff, "%s", category1.quest5Ans4Text);
	} else if(buttonID==cat2Quest5) {
		sprintf(questBuff, "%s", category2.quest5Text);
		sprintf(questAns1Buff, "%s", category2.quest5Ans1Text);
		sprintf(questAns2Buff, "%s", category2.quest5Ans2Text);
		sprintf(questAns3Buff, "%s", category2.quest5Ans3Text);
		sprintf(questAns4Buff, "%s", category2.quest5Ans4Text);
	} else if(buttonID==cat3Quest5) {
		sprintf(questBuff, "%s", category3.quest5Text);
		sprintf(questAns1Buff, "%s", category3.quest5Ans1Text);
		sprintf(questAns2Buff, "%s", category3.quest5Ans2Text);
		sprintf(questAns3Buff, "%s", category3.quest5Ans3Text);
		sprintf(questAns4Buff, "%s", category3.quest5Ans4Text);
	} else if(buttonID==cat4Quest5) {
		sprintf(questBuff, "%s", category4.quest5Text);
		sprintf(questAns1Buff, "%s", category4.quest5Ans1Text);
		sprintf(questAns2Buff, "%s", category4.quest5Ans2Text);
		sprintf(questAns3Buff, "%s", category4.quest5Ans3Text);
		sprintf(questAns4Buff, "%s", category4.quest5Ans4Text);
	} else if(buttonID==cat5Quest5) {
		sprintf(questBuff, "%s", category5.quest5Text);
		sprintf(questAns1Buff, "%s", category5.quest5Ans1Text);
		sprintf(questAns2Buff, "%s", category5.quest5Ans2Text);
		sprintf(questAns3Buff, "%s", category5.quest5Ans3Text);
		sprintf(questAns4Buff, "%s", category5.quest5Ans4Text);
	}
	
	// Creating the question and button answers
	questTextHandler = CreateWindow("static", questBuff, WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 200, 500, 100, windowHandler, NULL, NULL, NULL);
	
	int AnsNumBuff = rand() % 4;
	if (AnsNumBuff == 0) {
		int AnsNumBuff2 = rand() % 3;
		if (AnsNumBuff2 == 0) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		} else if (AnsNumBuff2 == 1) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		} else if (AnsNumBuff2 == 2) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		}
	} else if (AnsNumBuff == 1) {
		int AnsNumBuff2 = rand() % 3;
		if (AnsNumBuff2 == 0) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		} else if (AnsNumBuff2 == 1) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		} else if (AnsNumBuff2 == 2) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		}
	} else if (AnsNumBuff == 2) {
		int AnsNumBuff2 = rand() % 3;
		if (AnsNumBuff2 == 0) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		} else if (AnsNumBuff2 == 1) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		} else if (AnsNumBuff2 == 2) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
			}
		}
	} else if (AnsNumBuff == 3) {
		int AnsNumBuff2 = rand() % 3;
		if (AnsNumBuff2 == 0) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
			}
		} else if (AnsNumBuff2 == 1) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
			}
		} else if (AnsNumBuff2 == 2) {
			int AnsNumBuff3 = rand() % 2;
			if (AnsNumBuff3 == 0) {
				questAns1Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
			} else if (AnsNumBuff3 == 1) {
				questAns1Handler = CreateWindow("button", questAns4Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns2Handler = CreateWindow("button", questAns3Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonUpY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns3Handler = CreateWindow("button", questAns2Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonLeftX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)wrongAnswer, NULL, NULL);
				questAns4Handler = CreateWindow("button", questAns1Buff, WS_VISIBLE | WS_CHILD | BS_CENTER, ansButtonRightX, ansButtonDownY, ansButtonWidth, ansButtonHeight, windowHandler, (HMENU)rightAnswer, NULL, NULL);
			}
		}
	}
}

// The function for destroying the items from the questionBase window
void destroyQuestion(int questID)
{
	DestroyWindow(playersTurnTextHandler);
	DestroyWindow(randomQuestHandler);
	DestroyWindow(questTextHandler);
	DestroyWindow(questAns1Handler);
	DestroyWindow(questAns2Handler);
	DestroyWindow(questAns3Handler);
	DestroyWindow(questAns4Handler);
}

// The function for destroying the items from the 'mainGame' window
void destroyMainGame()
{
	DestroyWindow(category1.categoryHandler);
	DestroyWindow(category2.categoryHandler);
	DestroyWindow(category3.categoryHandler);
	DestroyWindow(category4.categoryHandler);
	DestroyWindow(category5.categoryHandler);
	DestroyWindow(category1.quest1Handler);
	DestroyWindow(category2.quest1Handler);
	DestroyWindow(category3.quest1Handler);
	DestroyWindow(category4.quest1Handler);
	DestroyWindow(category5.quest1Handler);
	DestroyWindow(category1.quest2Handler);
	DestroyWindow(category2.quest2Handler);
	DestroyWindow(category3.quest2Handler);
	DestroyWindow(category4.quest2Handler);
	DestroyWindow(category5.quest2Handler);
	DestroyWindow(category1.quest3Handler);
	DestroyWindow(category2.quest3Handler);
	DestroyWindow(category3.quest3Handler);
	DestroyWindow(category4.quest3Handler);
	DestroyWindow(category5.quest3Handler);
	DestroyWindow(category1.quest4Handler);
	DestroyWindow(category2.quest4Handler);
	DestroyWindow(category3.quest4Handler);
	DestroyWindow(category4.quest4Handler);
	DestroyWindow(category5.quest4Handler);
	DestroyWindow(category1.quest5Handler);
	DestroyWindow(category2.quest5Handler);
	DestroyWindow(category3.quest5Handler);
	DestroyWindow(category4.quest5Handler);
	DestroyWindow(category5.quest5Handler);
	DestroyWindow(player1Turn);
	DestroyWindow(player2Turn);
	DestroyWindow(player3Turn);
	DestroyWindow(player4Turn);
	DestroyWindow(player1ScoreTextHandler);
	DestroyWindow(player2ScoreTextHandler);
	DestroyWindow(player3ScoreTextHandler);
	DestroyWindow(player4ScoreTextHandler);
}

// The function for pulling the questions and answers from our directory files based on
// which categories were randomly chosen
void pullQuestions()
{
	// Looping 5 times to grab each question and answer for the 5 categories
	for(int catNum=0; catNum<5; catNum++)
	{
		// Creating variables
		int line_count = 0;
		FILE *file;
		char *tmpString = categories[currentCategories[catNum]];
		
		// Testing which category aligns with the categoryID and opening
		// that categories file for scraping
		if(strcmp("Plants",tmpString)==0)
		{
			file = fopen(plants, "r");
		} else if(strcmp("Anime",tmpString)==0) {
			file = fopen(anime, "r");
		} else if(strcmp("Animals",tmpString)==0) {
			file = fopen(animals, "r");
		} else if(strcmp("Geography",tmpString)==0) {
			file = fopen(geography, "r");
		} else if(strcmp("LOTR",tmpString)==0) {
			file = fopen(lotr, "r");
		} else if(strcmp("Music",tmpString)==0) {
			file = fopen(music, "r");
		} else if(strcmp("NBA",tmpString)==0) {
			file = fopen(nba, "r");
		} else if(strcmp("UFC",tmpString)==0) {
			file = fopen(ufc, "r");
		} else if(strcmp("Star Wars",tmpString)==0) {
			file = fopen(star_wars, "r");
		} else if(strcmp("Shoes",tmpString)==0) {
			file = fopen(shoes, "r");
		}
		
		// Looping through the file's 25 lines to pull all 5 questions and their 4 answers
		while(line_count<26)
		{
			line_count++;
			
			// Testing which line it is to know which question or answer we're pulling
			if(line_count==1)
			{
				// Testing which categoryID it is to know which variable to save our line to
				if(catNum==0)
				{
					// Getting the current file line and saving the first 256 characters to 'quest1Text'
					fgets(category1.quest1Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest1Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest1Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest1Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest1Text, 256, file);
				}
			} else if(line_count==2) {
				if(catNum==0)
				{
					fgets(category1.quest1Ans1Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest1Ans1Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest1Ans1Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest1Ans1Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest1Ans1Text, 256, file);
				}
			} else if(line_count==3) {
				if(catNum==0)
				{
					fgets(category1.quest1Ans2Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest1Ans2Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest1Ans2Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest1Ans2Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest1Ans2Text, 256, file);
				}
			} else if(line_count==4) {
				if(catNum==0)
				{
					fgets(category1.quest1Ans3Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest1Ans3Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest1Ans3Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest1Ans3Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest1Ans3Text, 256, file);
				}
			} else if(line_count==5) {
				if(catNum==0)
				{
					fgets(category1.quest1Ans4Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest1Ans4Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest1Ans4Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest1Ans4Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest1Ans4Text, 256, file);
				}
			} else if(line_count==6) {
				if(catNum==0)
				{
					fgets(category1.quest2Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest2Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest2Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest2Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest2Text, 256, file);
				}
			} else if(line_count==7) {
				if(catNum==0)
				{
					fgets(category1.quest2Ans1Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest2Ans1Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest2Ans1Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest2Ans1Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest2Ans1Text, 256, file);
				}
			} else if(line_count==8) {
				if(catNum==0)
				{
					fgets(category1.quest2Ans2Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest2Ans2Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest2Ans2Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest2Ans2Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest2Ans2Text, 256, file);
				}
			} else if(line_count==9) {
				if(catNum==0)
				{
					fgets(category1.quest2Ans3Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest2Ans3Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest2Ans3Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest2Ans3Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest2Ans3Text, 256, file);
				}
			} else if(line_count==10) {
				if(catNum==0)
				{
					fgets(category1.quest2Ans4Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest2Ans4Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest2Ans4Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest2Ans4Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest2Ans4Text, 256, file);
				}
			} else if(line_count==11) {
				if(catNum==0)
				{
					fgets(category1.quest3Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest3Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest3Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest3Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest3Text, 256, file);
				}
			} else if(line_count==12) {
				if(catNum==0)
				{
					fgets(category1.quest3Ans1Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest3Ans1Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest3Ans1Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest3Ans1Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest3Ans1Text, 256, file);
				}
			} else if(line_count==13) {
				if(catNum==0)
				{
					fgets(category1.quest3Ans2Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest3Ans2Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest3Ans2Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest3Ans2Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest3Ans2Text, 256, file);
				}
			} else if(line_count==14) {
				if(catNum==0)
				{
					fgets(category1.quest3Ans3Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest3Ans3Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest3Ans3Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest3Ans3Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest3Ans3Text, 256, file);
				}
			} else if(line_count==15) {
				if(catNum==0)
				{
					fgets(category1.quest3Ans4Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest3Ans4Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest3Ans4Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest3Ans4Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest3Ans4Text, 256, file);
				}
			} else if(line_count==16) {
				if(catNum==0)
				{
					fgets(category1.quest4Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest4Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest4Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest4Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest4Text, 256, file);
				}
			} else if(line_count==17) {
				if(catNum==0)
				{
					fgets(category1.quest4Ans1Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest4Ans1Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest4Ans1Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest4Ans1Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest4Ans1Text, 256, file);
				}
			} else if(line_count==18) {
				if(catNum==0)
				{
					fgets(category1.quest4Ans2Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest4Ans2Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest4Ans2Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest4Ans2Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest4Ans2Text, 256, file);
				}
			} else if(line_count==19) {
				if(catNum==0)
				{
					fgets(category1.quest4Ans3Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest4Ans3Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest4Ans3Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest4Ans3Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest4Ans3Text, 256, file);
				}
			} else if(line_count==20) {
				if(catNum==0)
				{
					fgets(category1.quest4Ans4Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest4Ans4Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest4Ans4Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest4Ans4Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest4Ans4Text, 256, file);
				}
			} else if(line_count==21) {
				if(catNum==0)
				{
					fgets(category1.quest5Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest5Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest5Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest5Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest5Text, 256, file);
				}
			} else if(line_count==22) {
				if(catNum==0)
				{
					fgets(category1.quest5Ans1Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest5Ans1Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest5Ans1Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest5Ans1Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest5Ans1Text, 256, file);
				}
			} else if(line_count==23) {
				if(catNum==0)
				{
					fgets(category1.quest5Ans2Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest5Ans2Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest5Ans2Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest5Ans2Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest5Ans2Text, 256, file);
				}
			} else if(line_count==24) {
				if(catNum==0)
				{
					fgets(category1.quest5Ans3Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest5Ans3Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest5Ans3Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest5Ans3Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest5Ans3Text, 256, file);
				}
			} else if(line_count==25) {
				if(catNum==0)
				{
					fgets(category1.quest5Ans4Text, 256, file);
				} else if(catNum==1) {
					fgets(category2.quest5Ans4Text, 256, file);
				} else if(catNum==2) {
					fgets(category3.quest5Ans4Text, 256, file);
				} else if(catNum==3) {
					fgets(category4.quest5Ans4Text, 256, file);
				} else if(catNum==4) {
					fgets(category5.quest5Ans4Text, 256, file);
				}
			}
		}
		// Closing the file once we're done to free memory, prevent corruption, and general tidyness
		fclose(file);
	}
}

// The function for selection a random player based on player count
void randomPlayer()
{
	// If there are 2 players, choose 1 or 2
	if(playerCount==2)
	{
		playersTurn = rand() % 2;
		
		if(playersTurn==0)
		{
			playersTurn = 2;
		}
	// If there are 3 players, choose 1, 2, or 3
	} else if(playerCount==3) {
		playersTurn = rand() % 3;
	
		if(playersTurn==0)
		{
			playersTurn = 3;
		}
	// If there are 4 players, choose 1, 2, 3, or 4
	} else if(playerCount==4) {
		playersTurn = rand() % 4;
		
		if(playersTurn==0)
		{
			playersTurn = 4;
		}
	}
}

// The function for choosing a random question to be the 'Daily Double'
void randomDailyDouble()
{
	// Choosing a random number from 6-30 based on questionIDs defined at the top of this program
	randomQuest = (rand() % 23)+6;
}

// The function for displaying the end of game window
void endGame(HWND windowHandler)
{
	// Destroying the items currently on the window, so we can place our new items on an empty surface
	destroyMainGame();
	
	// Creating the variable to save our winning player's formatted score to
	CHAR winnerText[256];
	
	// Setting winnerText based on whose score was the highest
	if(player1Score>player2Score && player1Score>player3Score && player1Score>player4Score)
	{
		sprintf(winnerText, "%ls wins with %d points!", player1Name, player1Score);
	} else if(player2Score>player3Score && player2Score>player4Score) {
		sprintf(winnerText, "%ls wins with %d points!", player2Name, player2Score);
	} else if(player3Score>player4Score) {
		sprintf(winnerText, "%ls wins with %d points!", player3Name, player3Score);
	} else {
		sprintf(winnerText, "%ls wins with %d points!", player4Name, player4Score);
	}
	
	// Displaying the winning player and their score and the 'Quit' button
	winnerTextHandler = CreateWindow("static", winnerText, WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 100, 500, 50, windowHandler, NULL, NULL, NULL);
	quitButtonHandler = CreateWindowW(L"button", L"Quit", WS_VISIBLE | WS_CHILD, 200, 350, 100, 50, windowHandler, (HMENU)QUIT, NULL, NULL);
}