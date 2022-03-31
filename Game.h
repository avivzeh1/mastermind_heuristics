#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include "code.h"

using namespace std;

class Game {
	
	code cd;
	//bulid the game board, mode for strategy mode or user mode, seed for random strategy, called by userPlay and strategyPlay
	void buildBoard(int mode = 0,int *seed = nullptr) const; 

public:
	Game();
	Game(const code& c);
	virtual ~Game();
	// play the game as user
	void userPlay();
	// strategyPlay - play the strategy move on board and return the result
	// choice - the number that presents the choisen color, row,col - the nposition on the board, code_ the full choisen code, bulls, cows- will contain the result of the move
	// mode - for knowing which stratgy, seed - for random strategy	
	void strategyPlay(int choice, int row, int col, const code& code_, int *bulls, int *cows, int mode,int *seed = nullptr);
	const code& getCode() const;
	// check the result of choice in game g at row row on the board, 
	// return true if the result is 4 bulls and has a winning
	// bulls and cows will contain the result
	// if mode is not 0 then the function compare choise with compcode and return the result
	friend bool checkResult(Game &g,const int *choice,int row, int *bulls, int* cows, int mode,code comp);

};
bool checkResult(Game &g,const int *choice,int row, int *bulls = nullptr, int* cows = nullptr, int mode = 0,code comp = code());
#endif /* GAME_H_ */

