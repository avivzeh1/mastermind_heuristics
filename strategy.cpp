#include <iostream>
#include<vector>
#include "strategy.h"
#include "code.h"
#include <thread>

strategy::strategy() : moves(0){

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			for (int k = 0; k < 6; k++)
				for (int l = 0; l < 6; l++)
					comb.push_back(code(i,j,k,l));					

}

strategy::~strategy() {
	
}


void strategy::filter(Game &g,int bulls, int cows, code c){
	
	int cows_ = 0,	bulls_ = 0, row = 0;

	for(int j = 0; j < comb.size(); j++){
		if(comb[j].getCode()[4] != -1){
		checkResult(g,comb[j].getCode(),row,&bulls_,&cows_,-1,c);
			if(bulls_ != bulls || cows_ != cows)   // 
				comb[j].setCode(4,-1); // mark that it is removed code
			}
	}
	
}


int strategy::getCombSize() const{
	
	int size = 0;
	
	for(code c : comb)
		if(c.getCode()[4] != -1)
			size++;
		
		return size;
	
}

const vector<code>& strategy::getComb() const{

	return comb;
}


int strategy::getMoves() const{
	
	return moves;
}








