// Xsi0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>

class Game {
private:
	bool exit;
	std::string tab;
	std::string message;
	struct gameBoard {
		char table[3][3];
		int nivel, scoreBoard1, scoreBoard2, lastWinner;
		bool stop;
		bool turn1, turn2, turn, facut;
		bool active;
	}board;
	struct MainMenu {
		int newGame, credential, exit;
		bool active;
	} mainMenu;
	struct selectLevel {
		int easy, normal, hard, multiplayer, back;
		bool active;
	} menuSelectLevel;
	struct credentials {
		bool active;
	} cred;
	struct fiz {
		int status, adancime;
	};
private:
	//Initialize game parameters.
	void initializeGameParameters() {
		this->exit = false;
		this->tab = "Main Menu";
		this->message = "Player1 is first!";
		//Initialize Credentials tab
		this->cred.active = false;
		//Initialize main menu.
		this->mainMenu.newGame = 1;
		this->mainMenu.credential = 0;
		this->mainMenu.exit = 0;
		this->mainMenu.active = true;
		//End of initialization main menu.
		//Start initilize select level menu.
		this->menuSelectLevel.easy = 1;
		this->menuSelectLevel.normal = 0;
		this->menuSelectLevel.hard = 0;
		this->menuSelectLevel.multiplayer = 0;
		this->menuSelectLevel.back = 0;
		this->menuSelectLevel.active = false;
		//End of initialization select level menu.
		//Start initilize table of game.
		this->board.active = false;
		this->board.stop = false;
		this->board.lastWinner = 0;
		this->board.turn = false;
		this->board.facut = true;
		this->board.scoreBoard1 = 0;
		this->board.scoreBoard2 = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				this->board.table[i][j] = ' ';
		//Legend: 0->Uncomplete, 1->Complete with 'x', 2->Complete with '0'
	}
	//Reseteaza jocul dar incrementeaza actualizeaza score board.
	void restartGame() {
		if (this->board.turn1) this->message = "Player1 is first!";
		else if (this->board.turn2) this->message = "Player2 is first!";
		this->board.active = false;
		this->board.stop = false;
		this->board.facut = true;
		if (this->board.lastWinner == 1) this->board.scoreBoard1++;
		else if (this->board.lastWinner == 2) this->board.scoreBoard2++;
		this->board.lastWinner = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				this->board.table[i][j] = ' ';
	}
	//Seteaza dificultatea jocului.
	void setDifficulty(int level) {
		this->board.turn1 = true;
		this->board.turn2 = false;
		switch (level) {
		case 1: this->board.nivel = 1; break;
		case 2: this->board.nivel = 2; break;
		case 3: this->board.nivel = 3; break;
		case 4: this->board.nivel = 4; break;
		default: break;
		}
	}
	//Listen when a key is pressed.
	int listenKeyPress() {
		int c;
		c = _getch();
		switch (c) {
		case 13: return 13; break; //Enter Key;
		case 72: return 11; break; //Up Key;
		case 80: return 12; break; //Down Key;
		case 49: return 1; break; //Left Down Corner;
		case 50: return 2; break; //Down middle;
		case 51: return 3; break; //Right Down corner;
		case 52: return 4; break; //Middle left;
		case 53: return 5; break; //Middle;
		case 54: return 6; break; //Middle right;
		case 55: return 7; break; //Top Left corner;
		case 56: return 8; break; // Top Middle;
		case 57: return 9; break; //Top Right corner;
		default: return 0; break;
		}
		return 0;
	}
	//Show interface in console.
	void render() {
		system("cls");
		std::cout << " _  _    ___  ____     ___  " << '\n';
		std::cout << "( \\/ )  / __)(_  _)   / _ \\ " << '\n';
		std::cout << " )  (   \\__ \\ _)(_   ( (_) )" << '\n';
		std::cout << "(_/\\_)  (___/(____)   \\___/ " << '\n';
		std::cout << "--------------" << this->tab << "-------------" << '\n';
		if (this->mainMenu.active) {
			if (this->mainMenu.newGame == 1) std::cout << "> "; else std::cout << "- "; std::cout << "New Game" << '\n';
			if (this->mainMenu.credential == 1) std::cout << "> "; else std::cout << "- "; std::cout << "Credentials" << '\n';
			if (this->mainMenu.exit == 1) std::cout << "> "; else std::cout << "- "; std::cout << "Exit" << '\n' << '\n';
			std::cout << "Note: Press 'Enter' to select menu.";
		}
		else if(this->menuSelectLevel.active) {
			if (this->menuSelectLevel.easy == 1) std::cout << "> "; else std::cout << "- "; std::cout << "Easy" << '\n';
			if (this->menuSelectLevel.normal == 1) std::cout << "> "; else std::cout << "- "; std::cout << "Normal" << '\n';
			if (this->menuSelectLevel.hard == 1) std::cout << "> "; else std::cout << "- "; std::cout << "Hard" << '\n' << '\n';
			if (this->menuSelectLevel.multiplayer == 1) std::cout << "> "; else std::cout << "- "; std::cout << "Multiplayer" << '\n' << '\n';
			if (this->menuSelectLevel.back == 1) std::cout << "> "; else std::cout << "- "; std::cout << "Back" << '\n' << '\n';
			std::cout << "Note: Press 'Enter' to select difficuly.";
		}
		else if (this->cred.active) {
			std::cout << "   _____ _        _               _____                         _____      _        _ _       " << '\n';
			std::cout << "  / ____| |      (_)             |_   _|                       / ____|    | |      | (_)      " << '\n';
			std::cout << " | (___ | |_ ___  _  __ _ _ __     | |  ___   __ _ _ __ ______| |     __ _| |_ __ _| |_ _ __  " << '\n';
			std::cout << "  \\___ \\| __/ _ \\| |/ _` | '_ \\    | | / _ \\ / _` | '_ \\______| |    / _` | __/ _` | | | '_ \\ " << '\n';
			std::cout << "  ____) | || (_) | | (_| | | | |  _| || (_) | (_| | | | |     | |___| (_| | || (_| | | | | | |" << '\n';
			std::cout << " |_____/ \\__\\___/|_|\\__,_|_| |_| |_____\\___/_\\__,_|_| |_|      \\_____\\__,_|\\__\\__,_|_|_|_| |_|" << '\n';
			std::cout << "  / ____|                       _  |  _ \\  / /                                                " << '\n';
			std::cout << " | |  __ _ __ _   _ _ __   __ _(_) | |_) |/ /_                                                " << '\n';
			std::cout << " | | |_ | '__| | | | '_ \\ / _` |   |  _ <| '_ \\                                               " << '\n';
			std::cout << " | |__| | |  | |_| | |_) | (_| |_  | |_) | (_) |                                              " << '\n';
			std::cout << "  \\_____|_|   \\__,_| .__/ \\__,_(_) |____/ \\___/                                               " << '\n';
			std::cout << "                   | |                                                                        " << '\n';
			std::cout << "                   |_|                                                                        " << '\n' << '\n';
			std::cout << "Note: Please press 'Enter' to go back.";
		}
		else if (this->board.active) {
			std::cout << '\n';
			std::cout << "Score board ---- Player1: " << this->board.scoreBoard1 << " ---- Player2: " << this->board.scoreBoard2;
			std::cout << '\n' << '\n';
			std::cout << "       You can       -------------" << '\n';
			std::cout << "   use NumLock area  | " << this->board.table[0][0] << " |" << " " << this->board.table[0][1] << " |" << " " << this->board.table[0][2] << " |" << '\n';
			std::cout << "   for choose where  -------------" << '\n';
			std::cout << "   you want to make  | " << this->board.table[1][0] << " |" << " " << this->board.table[1][1] << " |" << " " << this->board.table[1][2] << " |" << '\n';
			std::cout << "      your move.     -------------" << '\n';
			std::cout << "                     | " << this->board.table[2][0] << " |" << " " << this->board.table[2][1] << " |" << " " << this->board.table[2][2] << " |" << '\n';
			std::cout << "                     -------------" << '\n'<< '\n';
			std::cout << "!!! " << this->message << " !!!"<< '\n' << '\n';
			std::cout << "Note: Press 'Enter' to go back in main menu.";
		}
	}
	void switchTurn() {
		if (this->board.turn1) {
			this->board.turn1 = false;
			this->board.turn2 = true;
		}
		else {
			this->board.turn1 = true;
			this->board.turn2 = false;
		}
	}
	//Decide ce actiune trebuie facuta in functie de tasta apasata.
	void readAndDo(int keyPressed) { //This function read keypressed and change parameters.
		if (keyPressed == 13) {
			if (this->cred.active) {
				this->initializeGameParameters();
				this->changeToMainMenu();
			}
			else if (this->board.active) {
				this->initializeGameParameters();
				this->changeToMainMenu();
			}
			else this->enterPressed();
	 	}
        else if (this->mainMenu.active) {
			//We are in main menu.
			switch (keyPressed) {
			case 11: this->mainMenuMoveUp(); break;
			case 12: this->mainMenuMoveDown(); break;
			default: break;
			}
		}
		else if (this->menuSelectLevel.active) {
			//We are in select level menu.
			switch (keyPressed) {
			case 11: this->selectMenuMoveUp(); break;
			case 12: this->selectMenuMoveDown(); break;
			default: break;
			}
		}
		else if (this->board.active) {
			//We are in select level menu.
			if (this->board.stop) {
				this->restartGame();
				this->board.turn = !this->board.turn;
				this->changeToBoardGame();
				if (this->board.turn==true && this->board.facut==true) {
					int win = checkForWin();
					if (this->checkForGame(win));
					this->board.turn = true;
					this->board.facut = false;
					this->aiEasyMove();
					win = checkForWin();
					if (this->checkForGame(win));
					this->message = " It's your turn! ";
				}
			}
			else switch (this->board.nivel) {
			case 1: this->aiMode(keyPressed); break;
			case 2: this->aiMode(keyPressed); break;
			case 3: this->aiMode(keyPressed); break;
			case 4: this->multiplayerMode(keyPressed);
			default: break;
			}
		}
	}
	//Misca in sus cursorul in meniul principal.
	void mainMenuMoveUp() {
		if (this->mainMenu.newGame) {
			this->mainMenu.newGame = 0; this->mainMenu.credential = 0; this->mainMenu.exit = 1;
		}
		else if (this->mainMenu.credential) {
			this->mainMenu.newGame = 1; this->mainMenu.credential = 0; this->mainMenu.exit = 0;
		}
		else if (this->mainMenu.exit) {
			this->mainMenu.newGame = 0; this->mainMenu.credential = 1; this->mainMenu.exit = 0;
		}
	}
	//Misca in jos cursorul in meniul principal.
	void mainMenuMoveDown() {
		if (this->mainMenu.newGame) {
			this->mainMenu.newGame = 0; this->mainMenu.credential = 1; this->mainMenu.exit = 0;
		}
		else if (this->mainMenu.credential) {
			this->mainMenu.newGame = 0; this->mainMenu.credential = 0; this->mainMenu.exit = 1;
		}
		else if (this->mainMenu.exit) {
			this->mainMenu.newGame = 1; this->mainMenu.credential = 0; this->mainMenu.exit = 0;
		}
	}
	//Misca in sus cursorul in meniul de selectare a nivelelor.
	void selectMenuMoveUp() {
		if (this->menuSelectLevel.easy) {
			this->menuSelectLevel.easy = 0;
			this->menuSelectLevel.normal = 0;
			this->menuSelectLevel.hard = 0;
			this->menuSelectLevel.multiplayer = 0;
			this->menuSelectLevel.back = 1;
		}
		else if (this->menuSelectLevel.normal) {
			this->menuSelectLevel.easy = 1; 
			this->menuSelectLevel.normal = 0;
			this->menuSelectLevel.hard = 0;
			this->menuSelectLevel.multiplayer = 0;
			this->menuSelectLevel.back = 0;
		}
		else if (this->menuSelectLevel.hard) {
			this->menuSelectLevel.easy = 0; 
			this->menuSelectLevel.normal = 1;
			this->menuSelectLevel.hard = 0;
			this->menuSelectLevel.multiplayer = 0;
			this->menuSelectLevel.back = 0;
		}
		else if (this->menuSelectLevel.multiplayer) {
			this->menuSelectLevel.easy = 0;
			this->menuSelectLevel.normal = 0;
			this->menuSelectLevel.hard = 1;
			this->menuSelectLevel.multiplayer = 0;
			this->menuSelectLevel.back = 0;
		}
		else if (this->menuSelectLevel.back) {
			this->menuSelectLevel.easy = 0;
			this->menuSelectLevel.normal = 0;
			this->menuSelectLevel.hard = 0;
			this->menuSelectLevel.multiplayer = 1;
			this->menuSelectLevel.back = 0;
		}
	}
	//Misca in jos cursorul in meniul de selectare a nivelelor.
	void selectMenuMoveDown() {
		if (this->menuSelectLevel.easy) {
			this->menuSelectLevel.easy = 0;
			this->menuSelectLevel.normal = 1;
			this->menuSelectLevel.hard = 0;
			this->menuSelectLevel.multiplayer = 0;
			this->menuSelectLevel.back = 0;
		}
		else if (this->menuSelectLevel.normal) {
			this->menuSelectLevel.easy = 0;
			this->menuSelectLevel.normal = 0; 
			this->menuSelectLevel.hard = 1;
			this->menuSelectLevel.multiplayer = 0;
			this->menuSelectLevel.back = 0;
		}
		else if (this->menuSelectLevel.hard) {
			this->menuSelectLevel.easy = 0;
			this->menuSelectLevel.normal = 0;
			this->menuSelectLevel.hard = 0;
			this->menuSelectLevel.multiplayer = 1;
			this->menuSelectLevel.back = 0;
		}
		else if (this->menuSelectLevel.multiplayer) {
			this->menuSelectLevel.easy = 0;
			this->menuSelectLevel.normal = 0;
			this->menuSelectLevel.hard = 0;
			this->menuSelectLevel.multiplayer = 0;
			this->menuSelectLevel.back = 1;
		}
		else if (this->menuSelectLevel.back) {
			this->menuSelectLevel.easy = 1;
			this->menuSelectLevel.normal = 0; 
			this->menuSelectLevel.hard = 0;
			this->menuSelectLevel.multiplayer = 0;
			this->menuSelectLevel.back = 0;
		}
	}
	//Seteaza ca si activ meniul de selectare a nivelelor.
	void changeToSelectMenu() {
		this->tab = "Select difficulty of game";
		this->menuSelectLevel.active = true;
		this->mainMenu.active = false;
		this->cred.active = false;
		this->board.active = false;
	}
	//Seteaza ca si activ meniul principal.
	void changeToMainMenu() {
		this->tab = "Main Menu";
		this->menuSelectLevel.active = false;
		this->mainMenu.active = true;
		this->cred.active = false;
		this->board.active = false;
	}
	//Seteaza ca si activ tab-ul credentials.
	void changeToCredentials() {
		this->tab = "Credentials";
		this->menuSelectLevel.active = false;
		this->mainMenu.active = false;
		this->cred.active = true;
		this->board.active = false;
	}
	//Seteaza ca si activ jocul. Incepe jocul.
	void changeToBoardGame() {
		this->tab = "";
		this->menuSelectLevel.active = false;
		this->mainMenu.active = false;
		this->cred.active = false;
		this->board.active = true;
	}
	//Trateaza cazul in care tasta "enter" a fost apasata.
	void enterPressed() {
		if (this->mainMenu.active) {
			if (this->mainMenu.newGame) this->changeToSelectMenu();
			if (this->mainMenu.credential) this->changeToCredentials();
			if (this->mainMenu.exit) this->exit = true;
		}
		else if (this->menuSelectLevel.active) {
			//Do stuff for start game.
			if (this->menuSelectLevel.back) this->changeToMainMenu();
			else if (this->menuSelectLevel.easy) {
				this->setDifficulty(1);
				this->changeToBoardGame();
			}
			else if (this->menuSelectLevel.normal) {
				this->setDifficulty(2);
				this->changeToBoardGame();
			}
			else if (this->menuSelectLevel.hard) {
				this->setDifficulty(3);
				this->changeToBoardGame();
			}
			else if (this->menuSelectLevel.multiplayer) {
				this->setDifficulty(4);
				this->changeToBoardGame();
			}
		}
	}
	//Easy Mode
	void aiMode(int keyPressed) {
		switch (keyPressed) {
		case 1:
			if (this->board.table[2][0] == ' ') {
				this->board.table[2][0] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel==1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->aiEasyMove() : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " It's your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 2:
			if (this->board.table[2][1] == ' ') {
				this->board.table[2][1] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel == 1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->aiEasyMove() : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " It's your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 3:
			if (this->board.table[2][2] == ' ') {
				this->board.table[2][2] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel == 1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->aiEasyMove() : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " It's your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 4:
			if (this->board.table[1][0] == ' ') {
				this->board.table[1][0] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel == 1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->aiEasyMove() : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " It's your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 5:
			if (this->board.table[1][1] == ' ') {
				this->board.table[1][1] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel == 1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->aiEasyMove() : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " It's your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 6:
			if (this->board.table[1][2] == ' ') {
				this->board.table[1][2] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel == 1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->aiEasyMove() : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " It's your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 7:
			if (this->board.table[0][0] == ' ') {
				this->board.table[0][0] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel == 1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->aiEasyMove() : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " Is your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 8:
			if (this->board.table[0][1] == ' ') {
				this->board.table[0][1] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel == 1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->board.table[1][1] = '0' : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " It's your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 9:
			if (this->board.table[0][2] == ' ') {
				this->board.table[0][2] = 'X';
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.nivel == 1) this->aiEasyMove();
				else if (this->board.nivel == 2) this->board.facut ? this->aiEasyMove() : this->aiNormalMove();
				else if (this->board.nivel == 3) this->board.facut ? this->aiEasyMove() : this->aiHardMove();
				this->board.facut = false;
				win = checkForWin();
				if (this->checkForGame(win)) break;
				this->message = " It's your turn! ";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		default: break;
		}
	}
	//A.I. Easy move.
	void aiEasyMove() {
		this->message = "Computer loading...";
		int move = 1 + (rand() % (int)(9 - 1 + 1));
		switch (move) {
		case 1:
			if (this->board.table[2][0] == ' ') {
				this->board.table[2][0] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		case 2:
			if (this->board.table[2][1] == ' ') {
				this->board.table[2][1] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		case 3:
			if (this->board.table[2][2] == ' ') {
				this->board.table[2][2] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		case 4:
			if (this->board.table[1][0] == ' ') {
				this->board.table[1][0] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		case 5:
			if (this->board.table[1][1] == ' ') {
				this->board.table[1][1] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		case 6:
			if (this->board.table[1][2] == ' ') {
				this->board.table[1][2] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		case 7:
			if (this->board.table[0][0] == ' ') {
				this->board.table[0][0] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		case 8:
			if (this->board.table[0][1] == ' ') {
				this->board.table[0][1] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		case 9:
			if (this->board.table[0][2] == ' ') {
				this->board.table[0][2] = 'O';
			}
			else {
				this->aiEasyMove();
			}
			break;
		default: break;
		}
	}
	//AiLastMove
	int CheckForLastMoveFor(char mark) {
		if (this->board.table[0][0] == ' ') {
			if (this->board.table[0][1] == this->board.table[0][2] && this->board.table[0][1] == mark) return 7;
			if (this->board.table[1][0] == this->board.table[2][0] && this->board.table[1][0] == mark) return 7;
			if (this->board.table[1][1] == this->board.table[2][2] && this->board.table[1][1] == mark) return 7;
		}
		if (this->board.table[0][1] == ' ') {
			if (this->board.table[0][0] == this->board.table[0][2] && this->board.table[0][0] == mark) return 8;
			if (this->board.table[1][1] == this->board.table[2][1] && this->board.table[1][1] == mark) return 8;
		}
		if (this->board.table[0][2] == ' ') {
			if (this->board.table[0][0] == this->board.table[0][1] && this->board.table[0][1] == mark) return 9;
			if (this->board.table[1][2] == this->board.table[2][2] && this->board.table[1][0] == mark) return 9;
			if (this->board.table[1][1] == this->board.table[2][0] && this->board.table[1][1] == mark) return 9;
		}
		if (this->board.table[1][0] == ' ') {
			if (this->board.table[1][1] == this->board.table[1][2] && this->board.table[0][1] == mark) return 4;
			if (this->board.table[0][0] == this->board.table[2][0] && this->board.table[0][0] == mark) return 4;
		}
		if (this->board.table[1][1] == ' ') {
			if (this->board.table[0][1] == this->board.table[2][1] && this->board.table[0][1] == mark) return 5;
			if (this->board.table[1][0] == this->board.table[1][2] && this->board.table[1][0] == mark) return 5;
			if (this->board.table[0][0] == this->board.table[2][2] && this->board.table[0][0] == mark) return 5;
			if (this->board.table[0][2] == this->board.table[2][0] && this->board.table[0][2] == mark) return 5;
		}
		if (this->board.table[1][2] == ' ') {
			if (this->board.table[0][2] == this->board.table[2][2] && this->board.table[0][2] == mark) return 6;
			if (this->board.table[1][0] == this->board.table[1][1] && this->board.table[1][0] == mark) return 6;
		}
		if (this->board.table[2][0] == ' ') {
			if (this->board.table[0][0] == this->board.table[1][0] && this->board.table[0][0] == mark) return 1;
			if (this->board.table[2][1] == this->board.table[2][2] && this->board.table[2][1] == mark) return 1;
			if (this->board.table[1][1] == this->board.table[0][2] && this->board.table[1][1] == mark) return 1;
		}
		if (this->board.table[2][1] == ' ') {
			if (this->board.table[2][0] == this->board.table[2][2] && this->board.table[2][0] == mark) return 2;
			if (this->board.table[1][1] == this->board.table[0][1] && this->board.table[1][1] == mark) return 2;
		}
		if (this->board.table[2][2] == ' ') {
			if (this->board.table[0][0] == this->board.table[1][1] && this->board.table[0][0] == mark) return 3;
			if (this->board.table[2][1] == this->board.table[2][0] && this->board.table[2][1] == mark) return 3;
			if (this->board.table[1][2] == this->board.table[0][2] && this->board.table[1][2] == mark) return 3;
		}
		return 0;
	}
	//AI hard move
	void aiHardMove() {
		int pos = 0, goodMove, castig = 0, adancime, maxAdancime = 1000;
		fiz move;
		this->message = "Computer loading...";
		goodMove = this->CheckForLastMoveFor('O');
		if (goodMove == 0) goodMove = this->CheckForLastMoveFor('X');
		if (goodMove == 0)
			for (int i = 2; i >= 0; i--)
				for (int j = 0; j < 3; j++) {
					pos++;
					if (this->board.table[i][j] == ' ') {
						char tableNew[3][3];
						for (int y = 0; y < 3; y++)
							for (int t = 0; t < 3; t++)
								tableNew[y][t] = this->board.table[y][t];
						adancime = 1;
						move = minMaxRecursiv(tableNew, false, pos, adancime, i, j, 3);
						if (move.status == 1 || move.status == 0) {
							if (move.adancime < maxAdancime) {
								goodMove = pos;
								maxAdancime = move.adancime;
							}
						}
					}
				}
		if (goodMove == 0) {
			int k = 0;
			for (int i = 2; i >= 0; i--) {
				for (int j = 0; j < 3; j++) {
					k++;
					if (this->board.table[i][j] == ' ') goodMove = k;
				}
			}
		}
		switch (goodMove) {
		case 1:
			if (this->board.table[2][0] == ' ') {
				this->board.table[2][0] = 'O';
			}
			break;
		case 2:
			if (this->board.table[2][1] == ' ') {
				this->board.table[2][1] = 'O';
			}
			break;
		case 3:
			if (this->board.table[2][2] == ' ') {
				this->board.table[2][2] = 'O';
			}
			break;
		case 4:
			if (this->board.table[1][0] == ' ') {
				this->board.table[1][0] = 'O';
			}
			break;
		case 5:
			if (this->board.table[1][1] == ' ') {
				this->board.table[1][1] = 'O';
			}
			break;
		case 6:
			if (this->board.table[1][2] == ' ') {
				this->board.table[1][2] = 'O';
			}
			break;
		case 7:
			if (this->board.table[0][0] == ' ') {
				this->board.table[0][0] = 'O';
			}
			break;
		case 8:
			if (this->board.table[0][1] == ' ') {
				this->board.table[0][1] = 'O';
			}
			break;
		case 9:
			if (this->board.table[0][2] == ' ') {
				this->board.table[0][2] = 'O';
			}
			break;
		default: break;
		}
	}
	//AI normal move
	fiz minMaxRecursiv(char table[3][3], bool turn, int pos, int adancime, int x, int y, int status) {
		if (status == 3) {
			if (turn == true) {
				table[x][y] = 'X';
				int win = checkForWinMinMax(table), k;
				fiz status;
				status.status = this->checkForGameMinMax(win);
				if (status.status != 3) {
					return status;
				}
			}
			else if (turn == false) {
				table[x][y] = 'O';
				int win = checkForWinMinMax(table), k;
				fiz status;
				status.status = this->checkForGameMinMax(win);
				if (status.status != 3) {
					return status;
				}
			}
			fiz rez;
			if (turn) rez.status = 1;
			else rez.status = -1;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++) {
					if (table[i][j] == ' ') {
						char tableNew[3][3];
						for (int y = 0; y < 3; y++)
							for (int t = 0; t < 3; t++)
								tableNew[y][t] = table[y][t];
					    adancime++;
						fiz k = minMaxRecursiv(tableNew, !turn, pos, adancime, i, j, 3);
						if (turn) {
							if (k.status < rez.status) rez = k;
						}
						else {
							if (k.status > rez.status) rez = k;
						}
					}
				}
			rez.adancime = adancime;
			return rez;
		}
	}
	void aiNormalMove() {
		int pos = 0, goodMove, castig = 0, adancime, maxAdancime = 1000;
		fiz move;
		this->message = "Computer loading...";
		goodMove = this->CheckForLastMoveFor('O');
		if (goodMove == 0) goodMove = this->CheckForLastMoveFor('X');
		if (goodMove == 0) {
			this->aiEasyMove();
		}
		else {
			switch (goodMove) {
			case 1:
				if (this->board.table[2][0] == ' ') {
					this->board.table[2][0] = 'O';
				}
				break;
			case 2:
				if (this->board.table[2][1] == ' ') {
					this->board.table[2][1] = 'O';
				}
				break;
			case 3:
				if (this->board.table[2][2] == ' ') {
					this->board.table[2][2] = 'O';
				}
				break;
			case 4:
				if (this->board.table[1][0] == ' ') {
					this->board.table[1][0] = 'O';
				}
				break;
			case 5:
				if (this->board.table[1][1] == ' ') {
					this->board.table[1][1] = 'O';
				}
				break;
			case 6:
				if (this->board.table[1][2] == ' ') {
					this->board.table[1][2] = 'O';
				}
				break;
			case 7:
				if (this->board.table[0][0] == ' ') {
					this->board.table[0][0] = 'O';
				}
				break;
			case 8:
				if (this->board.table[0][1] == ' ') {
					this->board.table[0][1] = 'O';
				}
				break;
			case 9:
				if (this->board.table[0][2] == ' ') {
					this->board.table[0][2] = 'O';
				}
				break;
			default: break;
			}
		}
	}
	//Mode Multiplayer
	void multiplayerMode(int keyPressed) {
		switch (keyPressed) {
		case 1: 
			if (this->board.table[2][0] == ' ') {
				if (this->board.turn1) this->board.table[2][0] = 'X'; else this->board.table[2][0] = 'O';
				this->switchTurn(); //Left Down Corner;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 2: 
			if (this->board.table[2][1] == ' ') {
				if (this->board.turn1) this->board.table[2][1] = 'X'; else this->board.table[2][1] = 'O';
				this->switchTurn(); //Down middle;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 3:
			if (this->board.table[2][2] == ' ') {
				if (this->board.turn1) this->board.table[2][2] = 'X'; else this->board.table[2][2] = 'O';
				this->switchTurn(); //Right Down corner;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 4:
			if (this->board.table[1][0] == ' ') {
				if (this->board.turn1) this->board.table[1][0] = 'X'; else this->board.table[1][0] = 'O';
				this->switchTurn();  break; //Middle left;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 5:
			if (this->board.table[1][1] == ' ') {
				if (this->board.turn1) this->board.table[1][1] = 'X'; else this->board.table[1][1] = 'O';
				this->switchTurn(); //Middle;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 6:
			if (this->board.table[1][2] == ' ') {
				if (this->board.turn1) this->board.table[1][2] = 'X'; else this->board.table[1][2] = 'O';
				this->switchTurn(); //Middle right;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 7: 
			if (this->board.table[0][0] == ' ') {
				if (this->board.turn1) this->board.table[0][0] = 'X'; else this->board.table[0][0] = 'O';
				this->switchTurn(); //Top Left corner;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 8: 
			if (this->board.table[0][1] == ' ') {
				if (this->board.turn1) this->board.table[0][1] = 'X'; else this->board.table[0][1] = 'O';
				this->switchTurn(); // Top Middle;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		case 9: 
			if (this->board.table[0][2] == ' ') {
				if (this->board.turn1) this->board.table[0][2] = 'X'; else this->board.table[0][2] = 'O';
				this->switchTurn(); //Top Right corner;
				int win = checkForWin();
				if (this->checkForGame(win)) break;
				if (this->board.turn1) this->message = "1 player 's turn.";
				else this->message = "2 player 's turn.";
			}
			else {
				this->message = "You can't put your mark there.";
			}
			break;
		default: break;
		}
	}
	int checkForWin() {
		if (this->board.table[1][1] != ' ' && this->board.table[0][0] == this->board.table[1][1] && this->board.table[2][2] == this->board.table[1][1])
			if (this->board.table[1][1] == 'X') return 1;
			else return 2;
		else if (this->board.table[1][1] != ' ' && this->board.table[0][2] == this->board.table[1][1] && this->board.table[2][0] == this->board.table[1][1])
			if (this->board.table[1][1] == 'X') return 1;
			else return 2;
		else if (this->board.table[0][1] != ' ' && this->board.table[0][0] == this->board.table[0][1] && this->board.table[0][2] == this->board.table[0][1])
			if (this->board.table[0][1] == 'X') return 1;
			else return 2;
		else if (this->board.table[1][1] != ' ' && this->board.table[1][0] == this->board.table[1][1] && this->board.table[1][2] == this->board.table[1][1])
			if (this->board.table[1][1] == 'X') return 1;
			else return 2;
		else if (this->board.table[2][1] != ' ' && this->board.table[2][0] == this->board.table[2][1] && this->board.table[2][2] == this->board.table[2][1])
			if (this->board.table[2][1] == 'X') return 1;
			else return 2;
		else if (this->board.table[1][0] != ' ' && this->board.table[0][0] == this->board.table[1][0] && this->board.table[2][0] == this->board.table[1][0])
			if (this->board.table[1][0] == 'X') return 1;
			else return 2;
		else if (this->board.table[1][1] != ' ' && this->board.table[0][1] == this->board.table[1][1] && this->board.table[2][1] == this->board.table[1][1])
			if (this->board.table[1][1] == 'X') return 1;
			else return 2;
		else if (this->board.table[1][2] != ' ' && this->board.table[0][2] == this->board.table[1][2] && this->board.table[2][2] == this->board.table[1][2])
			if (this->board.table[1][2] == 'X') return 1;
			else return 2;
			int remize = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (this->board.table[i][j] == ' ') remize = 1;
			if (remize) return 0;
			return 3;
	}
	bool checkForGame(int win) {
		if (win) {
			if (win == 1) { this->message = "Player 1 is the winner! Press 'enter' for back to menu. Any key for continue the game."; this->board.lastWinner = 1; }
			else if (win == 2) { this->message = "Player 2 is the winner! Press 'enter' for back to menu. Any key for continue the game."; this->board.lastWinner = 2; }
			else if (win == 3) { this->message = "Nobody win! Press 'enter' for back to menu. Any key for continue the game."; this->board.lastWinner = 0; }
			this->board.stop = true;
		}
		return this->board.stop;
	}
	//Check MINMAX WIN
	int checkForWinMinMax(char table[3][3]) {
		if (table[1][1] != ' ' && table[0][0] == table[1][1] && table[2][2] == table[1][1])
			if (table[1][1] == 'X') return 1;
			else return 2;
		else if (table[1][1] != ' ' && table[0][2] == table[1][1] && table[2][0] == table[1][1])
			if (table[1][1] == 'X') return 1;
			else return 2;
		else if (table[0][1] != ' ' && table[0][0] == table[0][1] && table[0][2] == table[0][1])
			if (table[0][1] == 'X') return 1;
			else return 2;
		else if (table[1][1] != ' ' && table[1][0] == table[1][1] && table[1][2] == table[1][1])
			if (table[1][1] == 'X') return 1;
			else return 2;
		else if (table[2][1] != ' ' && table[2][0] == table[2][1] && table[2][2] == table[2][1])
			if (table[2][1] == 'X') return 1;
			else return 2;
		else if (table[1][0] != ' ' && table[0][0] == table[1][0] && table[2][0] == table[1][0])
			if (table[1][0] == 'X') return 1;
			else return 2;
		else if (table[1][1] != ' ' && table[0][1] == table[1][1] && table[2][1] == table[1][1])
			if (table[1][1] == 'X') return 1;
			else return 2;
		else if (table[1][2] != ' ' && table[0][2] == table[1][2] && table[2][2] == table[1][2])
			if (table[1][2] == 'X') return 1;
			else return 2;
			int remize = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (table[i][j] == ' ') remize = 1;
			if (remize) return 0;
			return 3;
	}
	int checkForGameMinMax(int win) {
		if (win) {
			if (win == 1) { return -1; }
			else if (win == 2) { return 1; }
			else if (win == 0) { return 0; }
		}
		return 3;
	}
public:
	//Porneste aplicatia.
	void run() {
		this->initializeGameParameters();
		this->render();
		while (true) {
			this->readAndDo(
				this->listenKeyPress()
				);
			if (this->exit) break;
			this->render();
		}
	}
};

int main()
{
	Game xSi0;
	xSi0.run();
    return 0;
}

