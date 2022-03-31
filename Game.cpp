
#include<graphics.h>
#include "Game.h"
#include<cstdlib>
#include <thread>

Game::Game() {
	
}

Game::Game(const code& c) : cd(c){
	
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::buildBoard(int mode, int *seed) const {

	for (int j = 0; j < 18; j++)      // colors cells
		for (int i = 0; i < 4; i++) {
			setcolor (BLACK);
			setfillstyle(SOLID_FILL, BLACK);
			circle(25 + i * 40, 25 + j * 40, 18);
			floodfill(25 + i * 40, 25 + j * 40, BLACK);
			setcolor (WHITE);
			circle(25 + i * 40, 25 + j * 40, 18);
		}

	settextstyle(10, 0, 3);
	setcolor (YELLOW);
	if (mode != 0) // strategy mode, different position on board for moves field
		outtextxy(700, 600, "moves:");

	if (mode == 0) {  // user mode
		outtextxy(400, 600, "moves:");
		settextstyle(10, 0, 1);
		for (int i = 0; i < 6; i++) {  // draw colors possibilities on board
			switch (i) {

			case 0:
				setcolor (WHITE);
				outtextxy(395, 110, "w");
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				circle(400 + i * 40, 165, 18);
				floodfill(400 + i * 40, 165, WHITE);
				break;
			case 1:
				setcolor(WHITE);
				outtextxy(395 + 40 * i, 110, "m");
				setcolor (MAGENTA);
				setfillstyle(SOLID_FILL, MAGENTA);
				circle(400 + i * 40, 165, 18);
				floodfill(400 + i * 40, 165, MAGENTA);
				break;
			case 2:
				setcolor(WHITE);
				outtextxy(395 + 40 * i, 110, "r");
				setcolor (LIGHTRED);
				setfillstyle(SOLID_FILL, LIGHTRED);
				circle(400 + i * 40, 165, 18);
				floodfill(400 + i * 40, 165, LIGHTRED);
				break;

			case 3:
				setcolor(WHITE);
				outtextxy(395 + 40 * i, 110, "b");
				setcolor (BLUE);
				setfillstyle(SOLID_FILL, BLUE);
				circle(400 + i * 40, 165, 18);
				floodfill(400 + i * 40, 165, BLUE);
				break;
			case 4:
				setcolor(WHITE);
				outtextxy(395 + 40 * i, 110, "g");
				setcolor (GREEN);
				setfillstyle(SOLID_FILL, GREEN);
				circle(400 + i * 40, 165, 18);
				floodfill(400 + i * 40, 165, GREEN);
				break;
			case 5:
				setcolor(WHITE);
				outtextxy(395 + 40 * i, 110, "y");
				setcolor(YELLOW);
				setfillstyle(SOLID_FILL, YELLOW);
				circle(400 + i * 40, 165, 18);
				floodfill(400 + i * 40, 165, YELLOW);
				break;
			}
		}

		setcolor (WHITE);
		outtextxy(400, 200, "press 'c' for undo");
	} else if (mode == 1) {
		settextstyle(10, 0, 2);
		setcolor (LIGHTRED);
		outtextxy(595, 200, "Lexicographic strategy play");
	} else if (mode == 2) {
		char seed_str[5];
		settextstyle(10, 0, 2);
		setcolor (LIGHTRED);
		outtextxy(565, 200, "Random strategy play with seed ");
		outtextxy(933, 200, itoa(*seed, seed_str, 10));
	} else if (mode == 3) {
		settextstyle(10, 0, 2);
		setcolor (LIGHTRED);
		outtextxy(600, 200, "Knuth strategy play");
	} else if (mode == 4) {
		settextstyle(10, 0, 2);
		setcolor (LIGHTRED);
		outtextxy(600, 200, "Entropy strategy play");
	} else {
		settextstyle(10, 0, 2);
		setcolor (LIGHTRED);
		outtextxy(600, 200, "Most parts strategy play");
	}
				
}

void Game::strategyPlay(int choice, int row, int col, const code& code_, int *bulls, int *cows, int mode,int *seed){
	
	if (row == 0 && col == 0) { // build board at the beginnig and in case the board is full
		cleardevice();
		buildBoard(mode, seed);
	}

	switch (choice) {  // paint the chosen color

	case 0:
		setcolor (WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		circle(25 + col * 40, 25 + row * 40, 18);
		floodfill(25 + col * 40, 25 + row * 40, WHITE);
		break;
	case 1:
		setcolor (MAGENTA);
		setfillstyle(SOLID_FILL, MAGENTA);
		circle(25 + col * 40, 25 + row * 40, 18);
		floodfill(25 + col * 40, 25 + row * 40, MAGENTA);
		break;
	case 2:
		setcolor (LIGHTRED);
		setfillstyle(SOLID_FILL, LIGHTRED);
		circle(25 + col * 40, 25 + row * 40, 18);
		floodfill(25 + col * 40, 25 + row * 40, LIGHTRED);
		break;

	case 3:
		setcolor (BLUE);
		setfillstyle(SOLID_FILL, BLUE);
		circle(25 + col * 40, 25 + row * 40, 18);
		floodfill(25 + col * 40, 25 + row * 40, BLUE);
		break;
	case 4:
		setcolor (GREEN);
		setfillstyle(SOLID_FILL, GREEN);
		circle(25 + col * 40, 25 + row * 40, 18);
		floodfill(25 + col * 40, 25 + row * 40, GREEN);
		break;
	case 5:
		setcolor (YELLOW);
		setfillstyle(SOLID_FILL, YELLOW);
		circle(25 + col * 40, 25 + row * 40, 18);
		floodfill(25 + col * 40, 25 + row * 40, YELLOW);
		break;
	default:
		;
		break;
	}

	if (col == 3 && checkResult(*this, code_.getCode(), row, bulls, cows, 1) == true) { // check result after the fourth choice of color
		settextstyle(10, 0, 7);
		setcolor (LIGHTRED);
		outtextxy(595, 300, "STRATEGY");
		outtextxy(680, 360, "WON");
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 4; i++) {
				std::this_thread::sleep_for(std::chrono::nanoseconds(50000000));
				setcolor (BLACK);
				setfillstyle(SOLID_FILL, BLACK);
				circle(460 + i * 40, 400, 18);
				floodfill(460 + i * 40, 400, BLACK);
				setcolor(BLACK);
				circle(460 + i * 40, 400, 18);
			}
			for (int i = 0; i < 4; i++) {  // display to user the winning code
				std::this_thread::sleep_for(std::chrono::nanoseconds(50000000));
				switch (cd.getCode()[i]) {

				case 0:
					setcolor (WHITE);
					setfillstyle(SOLID_FILL, WHITE);
					circle(680 + i * 40, 460, 18);
					floodfill(680 + i * 40, 460, WHITE);
					break;
				case 1:
					setcolor (MAGENTA);
					setfillstyle(SOLID_FILL, MAGENTA);
					circle(680 + i * 40, 460, 18);
					floodfill(680 + i * 40, 460, MAGENTA);
					break;
				case 2:
					setcolor(LIGHTRED);
					setfillstyle(SOLID_FILL, LIGHTRED);
					circle(680 + i * 40, 460, 18);
					floodfill(680 + i * 40, 460, LIGHTRED);
					break;

				case 3:
					setcolor (BLUE);
					setfillstyle(SOLID_FILL, BLUE);
					circle(680 + i * 40, 460, 18);
					floodfill(680 + i * 40, 460, BLUE);
					break;
				case 4:
					setcolor (GREEN);
					setfillstyle(SOLID_FILL, GREEN);
					circle(680 + i * 40, 460, 18);
					floodfill(680 + i * 40, 460, GREEN);
					break;
				case 5:
					setcolor (YELLOW);
					setfillstyle(SOLID_FILL, YELLOW);
					circle(680 + i * 40, 460, 18);
					floodfill(680 + i * 40, 460, YELLOW);
					break;
				}
			}
		}
		getch();
		closegraph();
	}
	
}

void Game::userPlay() {
	
	char c; // user input
	int moves = 0;
	int choice[4];
	char str2[5];
	bool win = false;
	
	initwindow(700, 1000);
	
	do {
		cleardevice();
		buildBoard();
		settextstyle(10, 0, 3);
		setcolor (YELLOW);
		outtextxy(496, 602, itoa(moves, str2, 10)); // display the moves counter

		for (int j = 0; j < 18; j++) {
			moves++;
			for (int i = 0; i < 4; i++) { // fill a row in the board
				c = getch();

				switch (c) {

				case 'w':
					setcolor (WHITE);
					setfillstyle(SOLID_FILL, WHITE);
					circle(25 + i * 40, 25 + j * 40, 18);
					floodfill(25 + i * 40, 25 + j * 40, WHITE);
					choice[i] = 0;
					break;
				case 'm':
					setcolor (MAGENTA);
					setfillstyle(SOLID_FILL, MAGENTA);
					circle(25 + i * 40, 25 + j * 40, 18);
					floodfill(25 + i * 40, 25 + j * 40, MAGENTA);
					choice[i] = 1;
					break;
				case 'r':
					setcolor (LIGHTRED);
					setfillstyle(SOLID_FILL, LIGHTRED);
					circle(25 + i * 40, 25 + j * 40, 18);
					floodfill(25 + i * 40, 25 + j * 40, LIGHTRED);
					choice[i] = 2;
					break;

				case 'b':
					setcolor (BLUE);
					setfillstyle(SOLID_FILL, BLUE);
					circle(25 + i * 40, 25 + j * 40, 18);
					floodfill(25 + i * 40, 25 + j * 40, BLUE);
					choice[i] = 3;
					break;
				case 'g':
					setcolor (GREEN);
					setfillstyle(SOLID_FILL, GREEN);
					circle(25 + i * 40, 25 + j * 40, 18);
					floodfill(25 + i * 40, 25 + j * 40, GREEN);
					choice[i] = 4;
					break;
				case 'y':
					setcolor(YELLOW);
					setfillstyle(SOLID_FILL, YELLOW);
					circle(25 + i * 40, 25 + j * 40, 18);
					floodfill(25 + i * 40, 25 + j * 40, YELLOW);
					choice[i] = 5;
					break;
				case 'c': // undo
					settextstyle(10, 0, 7);
					if (i <= 3 && i > 0) {
						i--;
						setcolor (BLACK);
						setfillstyle(SOLID_FILL, BLACK);
						circle(25 + i * 40, 25 + j * 40, 18);
						floodfill(25 + i * 40, 25 + j * 40, BLACK);
						setcolor(WHITE);
						circle(25 + i * 40, 25 + j * 40, 18);
						i--;
					} else if (i == 0)
						i = -1;
					break;
				default:
					i--;
					break;
				}
			}
			win = checkResult(*this, choice, j); // check winning

			settextstyle(10, 0, 3);
			setcolor(YELLOW);
			outtextxy(496, 602, itoa(moves, str2, 10));
			if (win == true)
				break;  // break the for loop
		}
	} while (!win);

	settextstyle(10, 0, 7);
	setcolor (LIGHTRED);
	outtextxy(380, 300, "YOU WON");

	for (int j = 0; j < 3; j++) { 
		for (int i = 0; i < 4; i++) {  // display the winning code
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));
			setcolor (BLACK);
			setfillstyle(SOLID_FILL, BLACK);
			circle(460 + i * 40, 400, 18);
			floodfill(460 + i * 40, 400, BLACK);
			setcolor(BLACK);
			circle(460 + i * 40, 400, 18);
		}
		for (int i = 0; i < 4; i++) {
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));
			switch (cd.getCode()[i]) {

			case 0:
				setcolor (WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				circle(460 + i * 40, 400, 18);
				floodfill(460 + i * 40, 400, WHITE);
				break;
			case 1:
				setcolor (MAGENTA);
				setfillstyle(SOLID_FILL, MAGENTA);
				circle(460 + i * 40, 400, 18);
				floodfill(460 + i * 40, 400, MAGENTA);
				break;
			case 2:
				setcolor(LIGHTRED);
				setfillstyle(SOLID_FILL, LIGHTRED);
				circle(460 + i * 40, 400, 18);
				floodfill(460 + i * 40, 400, LIGHTRED);
				break;

			case 3:
				setcolor (BLUE);
				setfillstyle(SOLID_FILL, BLUE);
				circle(460 + i * 40, 400, 18);
				floodfill(460 + i * 40, 400, BLUE);
				break;
			case 4:
				setcolor (GREEN);
				setfillstyle(SOLID_FILL, GREEN);
				circle(460 + i * 40, 400, 18);
				floodfill(460 + i * 40, 400, GREEN);
				break;
			case 5:
				setcolor(YELLOW);
				setfillstyle(SOLID_FILL, YELLOW);
				circle(460 + i * 40, 400, 18);
				floodfill(460 + i * 40, 400, YELLOW);
				break;
			}
		}
	}
	getch();
	closegraph();
}

const code& Game::getCode() const{
	return cd;
}

bool checkResult(Game &g, const int *choice, int row,int *bulls_, int* cows_, int mode,code comp){
	
	int cows = 0, bulls = 0;
	int pos_bulls[4] = { 0 };
	int pos_cows[4] = { 0 };

	if (mode != -1) { // compare to the game code and display the result on the board

		for (int i = 0; i < 4; i++)
			if (choice[i] == g.cd.getCode()[i]) {
				pos_bulls[i] = 1;  // mark position bull
				bulls++;

			}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (choice[i] == g.cd.getCode()[j] && pos_bulls[j] != 1
						&& pos_bulls[i] != 1 && pos_cows[j] != 1) { // if equal but was not counted already as bull or cow, it is a cow
					cows++;
					pos_cows[j] = 1;
					break;
				}
			}
		}

		settextstyle(10, 0, 1);  // display the result on board
		setcolor (LIGHTRED);
		outtextxy(262, 7 + row * 40, ":BULLS");
		if (bulls != 0) {
			for (int i = 0; i < bulls; i++) {
				setcolor(LIGHTRED);
				setfillstyle(SOLID_FILL, LIGHTRED);
				circle(250 - i * 20, 18 + row * 40, 4);
				floodfill(250 - i * 20, 18 + row * 40, LIGHTRED);
				setcolor (WHITE);
				circle(250 - i * 20, 18 + row * 40, 4);
			}
		} else { // bo bulls
			settextstyle(10, 0, 1);
			outtextxy(250, 7 + row * 40, "X");
		}

		settextstyle(10, 0, 1);
		setcolor (WHITE);
		outtextxy(262, 24 + row * 40, ":COWS");
		if (cows != 0) {
			for (int i = 0; i < cows; i++) {
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				circle(250 - i * 20, 36 + row * 40, 4);
				floodfill(250 - i * 20, 36 + row * 40, WHITE);
				setcolor(WHITE);
				circle(250 - i * 20, 36 + row * 40, 4);
			}
		} else { // no cows
			outtextxy(250, 24 + row * 40, "X");
			settextstyle(10, 0, 1);
		}
	} else { // filter mode, compare to comp without output

		for (int i = 0; i < 4; i++)
			if (choice[i] == comp.getCode()[i]) {
				pos_bulls[i] = 1;  // mark position bull
				bulls++;

			}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (choice[i] == comp.getCode()[j] && pos_bulls[j] != 1
						&& pos_bulls[i] != 1 && pos_cows[j] != 1) { // if equal but not counted already as bull or cow
					cows++;
					pos_cows[j] = 1;
					break;
				}
			}
		}
	}
	if (mode == 1 || mode == -1) {
		*bulls_ = bulls;  // return the result 
		*cows_ = cows;
	}

	return bulls == 4;
}

