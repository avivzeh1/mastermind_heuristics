#include "MPStrategy.h"
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

MPStrategy::MPStrategy() : strategy()  {			
			
}

MPStrategy::~MPStrategy() {
	
}

void MPStrategy::play(Game &g){
	
	initwindow(1000, 1000);

	int bulls,cows,row = 0;
	
	char str1[5];  // string for display candidates code amount
	char str2[5];  // string for display moves amount
		
	moves++;
	
	code start(0,0,1,2); // starting move
			
	for (int i = 0; i < 4; i++) {  // play the code
		std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));  // delay for visual simulation
		g.strategyPlay(start.getCode()[i], row, i,start,&bulls,&cows,5);
		settextstyle(10, 0, 3);
        setcolor (YELLOW);
		outtextxy(796, 602, itoa(moves,str2,10));  
	}
			
	if(bulls == 4) // win situation
		return;
			  
	strategy::filter(g,bulls,cows,start); // filter candidates codes
		
    setcolor (LIGHTRED);
    settextstyle(10, 0, 1);
    outtextxy(360, 7 + row*40, "options left: ");
    outtextxy(510, 7 + row*40, itoa(strategy::getCombSize(),str1,10));  // diplay candidates amount
        
    if(strategy::getCombSize() == 1){ // if one code left
		row++;	
		moves++;
		settextstyle(10, 0, 3);
       	setcolor (YELLOW);
		outtextxy(796, 602, itoa(moves,str2,10));  	
		
		for (int i = 0; i < 4; i++) {  // play the code
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // delay for visual simulation
			g.strategyPlay(getWinnerCode().getCode()[i], row, i,getWinnerCode(),&bulls,&cows,5);
		}
		return;
	}

		row++;
			
	while(1){ // play until game over
		
		const int* co = nextMove(g); // get the next move
		code c(co[0],co[1],co[2],co[3]); //build the next code
			
		moves++;
		settextstyle(10, 0, 3);
        setcolor (YELLOW);
		outtextxy(796, 602, itoa(moves,str2,10));  
		
		for (int i = 0; i < 4; i++) {  // play the code
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // delay for visual simulation
			g.strategyPlay(c.getCode()[i], row, i,c,&bulls,&cows,5);
		}
			
		if(bulls == 4)
			break;
  
		strategy::filter(g,bulls,cows,c);
		
        setcolor (LIGHTRED);
        settextstyle(10, 0, 1);
        outtextxy(360, 7 + row*40, "options left: ");
        outtextxy(510, 7 + row*40, itoa(strategy::getCombSize(),str1,10));
			
		if(strategy::getCombSize() == 1){
			moves++;
			row++;
			settextstyle(10, 0, 3);
        	setcolor (YELLOW);
			outtextxy(796, 602, itoa(moves,str2,10));  
			for (int i = 0; i < 4; i++) {  // play the code
				std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // delay for visual simulation
				g.strategyPlay(getWinnerCode().getCode()[i], row, i,getWinnerCode(),&bulls,&cows,5);
			}
		}
			
		if(bulls == 4)
			break;
				
		row++;
		
	}
}

const int* MPStrategy::nextMove(Game &g){
	
	int cows_ = 0, bulls_ = 0, row = 0;
	map<vector<int>, int> scoreCount;
	vector<const int*> next;

    const int* ret = nullptr;
	int max = 0;

		
		for(int i = 0; i < comb.size(); i++){

			if(comb[i].getCode()[4] != -1){ // candidte codes
	
				for(int j = 0; j < comb.size(); j++){
					if(comb[j].getCode()[4] != -1){  // candidate code
						checkResult(g,comb[i].getCode(),row,&bulls_,&cows_,-1,comb[j]);
						vector<int> result; //the result
						result.push_back(bulls_);
						result.push_back(cows_);

           	 		if (scoreCount.count(result) == 1) // if this result in the map
              			 scoreCount.at(result)++;
             		else 
               			 scoreCount.emplace(result, 1);
            
           		 	}
	   			}
	   			if(scoreCount.size() > max){
	   				ret = comb[i].getCode();  // the code with the most possibilties of result
	   				max =  scoreCount.size();
	   			}
				scoreCount.clear();
			}
		
		}
		return ret;			
}

const code& MPStrategy::getWinnerCode() const{

	for(int i = 0; i < comb.size(); i++)
		if(comb[i].getCode()[4] != -1)
			return comb[i];
}


