#include "knuthStrategy.h"
#include <cstdlib>
#include "code.h"
#include "Game.h"
#include<graphics.h>
#include <thread>
#include <map>
#include <utility>
#include<vector>
#include <algorithm>
using namespace std;
knuthStrategy::knuthStrategy() : strategy()  {

}

knuthStrategy::~knuthStrategy() {
	
}

void knuthStrategy::play(Game &g){
	
	initwindow(1000, 1000);

	int bulls, cows, row = 0;

	char str1[5];
	char str2[5];

	moves++;

	code start(0,0,1,1); // starting move

	for (int i = 0; i < 4; i++) {  // play the code
		std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));
		g.strategyPlay(start.getCode()[i], row, i, start, &bulls, &cows, 3);
		settextstyle(10, 0, 3);
		setcolor (YELLOW);
		outtextxy(796, 602, itoa(moves, str2, 10));
	}

	if (bulls == 4)
		return;

	strategy::filter(g, bulls, cows, start);

	setcolor (LIGHTRED);
	settextstyle(10, 0, 1);
	outtextxy(360, 7 + row * 40, "options left: ");
	outtextxy(510, 7 + row * 40, itoa(strategy::getCombSize(), str1, 10));

	if (strategy::getCombSize() == 1) {
		row++;
		moves++;
		settextstyle(10, 0, 3);
		setcolor (YELLOW);
		outtextxy(796, 602, itoa(moves, str2, 10));

		for (int i = 0; i < 4; i++) {  // play the code
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));
			g.strategyPlay(getWinnerCode().getCode()[i], row, i, getWinnerCode(), &bulls, &cows, 3);
		}
		return;
	}
	row++;

	while (1) {

		const int* co = nextMove(g);
		code c(co[0],co[1],co[2],co[3]); //build the next code

		moves++;
		settextstyle(10, 0, 3);
		setcolor (YELLOW);
		outtextxy(796, 602, itoa(moves, str2, 10));

		for (int i = 0; i < 4; i++) {  // play the code
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // delay for visual simulation
			g.strategyPlay(c.getCode()[i], row, i, c, &bulls, &cows, 3);
		}

		if (bulls == 4)
			break;

		strategy::filter(g, bulls, cows, c);

		setcolor(LIGHTRED);
		settextstyle(10, 0, 1);
		outtextxy(360, 7 + row * 40, "options left: ");
		outtextxy(510, 7 + row * 40, itoa(strategy::getCombSize(), str1, 10));

		if (strategy::getCombSize() == 1) {
			moves++;
			row++;
			settextstyle(10, 0, 3);
			setcolor(YELLOW);
			outtextxy(796, 602, itoa(moves, str2, 10));
			for (int i = 0; i < 4; i++) {  // play the code
				std::this_thread::sleep_for(
						std::chrono::nanoseconds(100000000)); // delay for visual simulation
				g.strategyPlay(getWinnerCode().getCode()[i], row, i,
						getWinnerCode(), &bulls, &cows, 2);
			}
		}
		row++;

		if (bulls == 4)
			break;
	}
}

const code& knuthStrategy::getWinnerCode() const{

	for(int i = 0; i < comb.size(); i++)
		if(comb[i].getCode()[4] != -1)
			return comb[i];
}

const int* knuthStrategy::nextMove(Game &g){
	
	int cows_ = 0, bulls_ = 0, row = 0;
	map<vector<int>, int> scoreCount;
	map<const int*, int> score;
	vector<const int*> nextGuesses;
	int max, min;

	for (int i = 0; i < comb.size(); i++) { // check for each the result in compre to all candidates code
		for (int j = 0; j < comb.size(); j++) {
			if (comb[j].getCode()[4] != -1) {  // candidate code
				checkResult(g, comb[i].getCode(), row, &bulls_, &cows_, -1, comb[j]);
				vector<int> result; //the result
				result.push_back(bulls_);
				result.push_back(cows_);

				if (scoreCount.count(result) == 1) // if this result in the map
					scoreCount.at(result)++;
				else
					scoreCount.emplace(result, 1);
			}
		}

		max = getMaxScore(scoreCount); // get the number of codes of the most common result that obtained
		score.emplace(comb[i].getCode(), max); // save the maximum result of this code
		scoreCount.clear();
	}

	min = getMinScore(score); 

	for (auto elem : score) { // collect all the codes with minimum
		if (elem.second == min) {
			nextGuesses.push_back(elem.first);
		}
	}

	const int* nextGuess = getNextGuess(nextGuesses);

	return nextGuess;
		
}

int knuthStrategy::getMaxScore(map<vector<int>, int> inputMap)const {

    int max = 0;
    
    for (auto elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}

int knuthStrategy::getMinScore(map<const int*, int> inputMap)const {

    int min = numeric_limits<int>::max();
    
    for (auto elem : inputMap) {
        if (elem.second < min) {
            min = elem.second;
        }
    }

    return min;
}


const int* knuthStrategy::getNextGuess(vector<const int*> nextGuesses) {

    const int* nextGuess;

    for (int i = 0; i < nextGuesses.size(); ++i) {
    	for (int j = 0; j < comb.size(); ++j)
        	if (comb[j].getCode()[4] != -1 && comb[j].getCode() == nextGuesses[i])       	
            	return nextGuesses[i];
        
    }
    for (int i = 0; i < nextGuesses.size(); ++i) {
    	for (int j = 0; j < comb.size(); ++j)
        	if (comb[j].getCode() == nextGuesses[i])       	
            	return nextGuesses[i];
        
    }

    return nextGuess;
}
