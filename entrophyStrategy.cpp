#include "entrophyStrategy.h"
#include <cstdlib>
#include "code.h"
#include "Game.h"
#include<graphics.h>
#include <thread>
#include <cmath>
#include <map>
#include <utility>
#include<vector>
#include <algorithm>
using namespace std;
entrophyStrategy::entrophyStrategy() : strategy()  {


}

entrophyStrategy::~entrophyStrategy() {

}

void entrophyStrategy::play(Game &g){
	
	initwindow(1000, 1000);

	int bulls, cows, row = 0;

	char str1[5];
	char str2[5];

	moves++;

	code start(0,1,2,3); // starting move

	for (int i = 0; i < 4; i++) {  // play the code
		std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // delay for visual simulation
		g.strategyPlay(start.getCode()[i], row, i, start, &bulls, &cows, 4);
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
			g.strategyPlay(getWinnerCode().getCode()[i], row, i,
					getWinnerCode(), &bulls, &cows, 4);
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
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));
			g.strategyPlay(c.getCode()[i], row, i, c, &bulls, &cows, 4);
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
						std::chrono::nanoseconds(100000000));
				g.strategyPlay(getWinnerCode().getCode()[i], row, i,
						getWinnerCode(), &bulls, &cows, 4);
			}
		}

		if (bulls == 4)
			break;

		row++;

	}
}

const int* entrophyStrategy::nextMove(Game &g){
	
	int cows_ = 0, bulls_ = 0, row = 0;
	map<vector<int>, int> scoreCount;
	map<const int*, float> entrophies;
	vector<const int*> nextGuesses;
	vector<float> propabilties;
	float max, min;

	for (int i = 0; i < comb.size(); i++) { // for all codes
		for (int j = 0; j < comb.size(); j++) {
			if (comb[j].getCode()[4] != -1) {  // candidate code
				checkResult(g, comb[i].getCode(), row, &bulls_, &cows_, -1, comb[j]);
				vector<int> result; //the result
				result.push_back(bulls_);
				result.push_back(cows_);

				if (scoreCount.count(result) == 1) // if this result in the map
					scoreCount.at(result)++;else
					scoreCount.emplace(result, 1);

			}
		}

		for (auto s : scoreCount) { // get for each result get probabilty tob get this result if we play the code comb[i]
			float p = ((float) s.second) / ((float) strategy::getCombSize());
			propabilties.push_back(p);
		}

		float ent = 0;

		for (auto pr : propabilties)  // calculate the entropy
			ent += pr * log2(1 / pr);

		entrophies.emplace(comb[i].getCode(), ent); // store the entropy of code comb[i]

		scoreCount.clear();
		propabilties.clear();

	}

	max = getMaxEnt(entrophies);

	for (auto elem : entrophies) { // put all the codes with max entrophy  in next guesses vector
		if (elem.second == max) {
			nextGuesses.push_back(elem.first);
		}
	}

	const int* nextGuess = getNextGuess(nextGuesses);  // max code entrophy

	return nextGuess;
		
}

float entrophyStrategy::getMaxEnt(map<const int*, float> inputMap)const {

    float max = 0;
    
    for (auto elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}


const code& entrophyStrategy::getWinnerCode() const{

	for(int i = 0; i < comb.size(); i++)
		if(comb[i].getCode()[4] != -1)
			return comb[i];
}


const int* entrophyStrategy::getNextGuess(vector<const int*> nextGuesses) {

    const int* nextGuess;

    for (int i = 0; i < nextGuesses.size(); ++i) {  // search candidate code with max entrophy
    	for (int j = 0; j < comb.size(); ++j)
        	if (comb[j].getCode()[4] != -1 && comb[j].getCode() == nextGuesses[i])       	
            	return nextGuesses[i];
        
    }
    for (int i = 0; i < nextGuesses.size(); ++i) {  // if the maximum entrophy is not candidate, search in the codes that are not candidate
    	for (int j = 0; j < comb.size(); ++j)
        	if (comb[j].getCode()[4] == -1 && comb[j].getCode() == nextGuesses[i])       	
            	return nextGuesses[i];
        
    }

    return nextGuess;
}
