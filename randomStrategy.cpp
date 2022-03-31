#include "randomStrategy.h"
#include <cstdlib>
#include "code.h"
#include "Game.h"
#include<graphics.h>
#include <thread>
#include <random>
#include <sstream>
randomStrategy::randomStrategy(int seed_) : strategy(), seed(seed_)  {
	// TODO Auto-generated constructor stub

}

randomStrategy::~randomStrategy() {
	// TODO Auto-generated destructor stub
}

void randomStrategy::play(Game &g){
	
	initwindow(1000, 1000);

	srand (seed);
	int bulls, cows, row = 0;
	stringstream s;
	
	s << seed;
	std::random_device rd(s.str()); // use the string of seed to create random device
	std::seed_seq seed_ { rd() };
	std::default_random_engine generator(seed_);  
	
	while (1) {

		char str1[5];
		char str2[5];

		moves++;
		settextstyle(10, 0, 3);
		setcolor (YELLOW);
		outtextxy(796, 602, itoa(moves, str2, 10));

		std::uniform_int_distribution<int> distribution(0, comb.size() - 1);
		int r = distribution(generator);

		for (int i = 0; i < 4; i++) {  // play the code
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // delay for visual simulation
			g.strategyPlay(comb[r].getCode()[i], row, i, comb[r], &bulls, &cows,
					2, &seed);
		}

		filter(g, bulls, cows, comb[r]);

		setcolor (LIGHTRED);
		settextstyle(10, 0, 1);
		outtextxy(360, 7 + row * 40, "options left: ");
		outtextxy(510, 7 + row * 40, itoa(comb.size(), str1, 10));

		row++;

		if (bulls == 4)
			break;
	}
}

void randomStrategy::filter(Game &g, int bulls, int cows, code c){
	
	int cows_ = 0,	bulls_ = 0, row = 0;

	for(int j = 0; j < comb.size(); j++){
		checkResult(g, comb[j].getCode(),row,&bulls_,&cows_,-1,c);
			if(bulls_ != bulls || cows_ != cows){   // if any same color it is not the code
				comb[j] = comb[comb.size()-1]; // remove code
				comb.pop_back();
				j--;
				if(j == comb.size())  // if the removed code was rhe last int the vector
					return;
					
			}
	}

}






