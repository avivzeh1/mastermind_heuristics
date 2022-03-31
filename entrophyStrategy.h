#ifndef ENROPHYSTRATEGY_H_
#define ENROPHYSTRATEGY_H_
#include "strategy.h"
#include <map>
#include <utility>
#include<vector>
using namespace std;

class entrophyStrategy : public strategy {
	
public:
	entrophyStrategy();
	virtual ~entrophyStrategy();
	void play(Game &g);
private:
	const code& getWinnerCode() const; // in case there is one code left, return it	
	const int* nextMove(Game &g);
	float getMaxEnt(map<const int*, float> inputMap) const; // return the maximum float value in inpur map
	const int* getNextGuess(vector<const int*> nextGuesses); // return one guess from the nextGuesses vector
};

#endif /* ENTROPHSTRATEGY_H_ */
