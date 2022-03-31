#ifndef MPSTRATEGY_H_
#define MPSTRATEGY_H_
#include "strategy.h"
#include <map>
#include <utility>
#include<vector>
using namespace std;

class MPStrategy : public strategy {
	
public:
	MPStrategy();
	virtual ~MPStrategy();
	void play(Game &g); // play the game
private:
	const code& getWinnerCode() const; // in case there is one code left, return it	
	const int* nextMove(Game &g); // return the next move

};

#endif /* MPSTRATEGY_H_ */
