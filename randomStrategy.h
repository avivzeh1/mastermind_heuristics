

#ifndef RANDOMSTRATEGY_H_
#define RANDOMSTRATEGY_H_
#include "strategy.h"
class randomStrategy : public strategy {
	
	int seed;
public:
	randomStrategy(int seed);
	virtual ~randomStrategy();
	void play(Game &g); // start playing
private:
	void filter(Game &g, int bulls, int cows, code c); //override filter for remove the codes who was fltered for saving run time
};

#endif /* RANDOMSTRATEGY_H_ */
