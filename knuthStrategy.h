#ifndef KNUTHSTRATEGY_H_
#define KNUTHSTRATEGY_H_
#include "strategy.h"
#include <map>
#include <utility>
#include<vector>
using namespace std;

class knuthStrategy : public strategy {
	
public:
	knuthStrategy();
	virtual ~knuthStrategy();
	void play(Game &g);
private:
	const code& getWinnerCode() const; // in case there is one code left, return it	
	const int* nextMove(Game &g);
	int getMaxScore(map<vector<int>, int> inputMap)const;  // return the maximu, int val in the map
	int getMinScore(map<const int*, int> inputMap)const; // return the minimum int val on the map
	const int* getNextGuess(vector<const int*> nextGuesses); // return the next guess from all options nextGuesses
};

#endif /* RANDOMSTRATEGY_H_ */
