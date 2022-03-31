#ifndef STRATEGY_H_
#define STRATEGY_H_
#include<vector>
#include "Game.h"
#include "code.h"
using namespace std;
class strategy {

public:
	strategy();
	virtual ~strategy();
	virtual void filter(Game &g, int bulls, int cows, code c); // filter comb after playing c and result of bulls and cows
	int getCombSize() const;  // return the candidates codes amount
	// getters
	const vector<code>& getComb() const;
	int getMoves() const;
protected:

	vector<code> comb; // 1296 combinations of codes of 4 digits
	int moves;
	
};

#endif /* STRATEGY_H_ */

