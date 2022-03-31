/*
 * lexicStrategy.h
 *
 *  Created on: Dec 19, 2020
 *      Author: cs313311797
 */

#ifndef LEXICSTRATEGY_H_
#define LEXICSTRATEGY_H_
#include "strategy.h"

class lexicStrategy : public strategy {
	
public:
	lexicStrategy();
	virtual ~lexicStrategy();
	void play(Game &g);

};

#endif /* LEXICSTRATEGY_H_ */

