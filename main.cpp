#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include<graphics.h>
#include<conio.h>
#include "Game.h"
#include "lexicStrategy.h"
#include "MPStrategy.h"
#include "randomStrategy.h"
#include "knuthStrategy.h"
#include "entrophyStrategy.h"
#include <fstream>
#include <map>
using namespace std;

int main( int argc, char* argv[] ) {
	

	char mode;
	cout << "Press 0 and ENTER for user mode, 1 and ENTER for srategies to play" << endl;
	code c;
	Game g(c);	
	lexicStrategy s1;
	randomStrategy s2(0);
	randomStrategy s3(1);
	knuthStrategy s4;
	entrophyStrategy s5;
	MPStrategy s6;
	
	while (1) {
		cin >> mode;
		switch (mode) {
		case '0':
			g.userPlay();
			return 0;
			break;
		case '1': // code for simulation of one strategy game
			s1.play(g);
			s2.play(g);		
			s3.play(g);
			s4.play(g);
			s5.play(g);
			s6.play(g);
			return 0;
			break;
		default:
			break;
		}
	}

///////////////////////////////////////

// code for strategy play all 1296 games, and print to file the statistics
	strategy s;
	vector<code> allOptions = s.getComb(); // get the vector of all 1296 combinations
	ofstream f("statistics2");
	int moves, maxMoves = 0;
	float avgMoves;
	map<int, int> result;

	for (int j = 0; j < 6; j++) {
		avgMoves = 0;
		maxMoves = 0;
		for (int i = 0; i < allOptions.size(); i++) {
			Game g(allOptions[i]);
			lexicStrategy s1;
			randomStrategy s2(0);
			randomStrategy s3(1);
			knuthStrategy s4;
			entrophyStrategy s5;
			MPStrategy s6;
			switch (j) {

			case 0:
				s1.play(g);
				moves = s1.getMoves();
				avgMoves += moves;
				maxMoves = maxMoves > moves ? maxMoves : moves;
				if (result.count(moves) == 1) // if this result in the map
					result.at(moves)++;else
					result.emplace(moves, 1);
				break;
			case 1:
				s2.play(g);
				moves = s2.getMoves();
				avgMoves += moves;
				maxMoves = maxMoves > moves ? maxMoves : moves;
				if (result.count(moves) == 1) // if this result in the map
					result.at(moves)++;else
					result.emplace(moves, 1);
				break;
			case 2:
				s3.play(g);
				moves = s3.getMoves();
				avgMoves += moves;
				maxMoves = maxMoves > moves ? maxMoves : moves;
				if (result.count(moves) == 1) // if this result in the map
					result.at(moves)++;else
					result.emplace(moves, 1);
				break;
			case 3:
				s4.play(g);
				moves = s4.getMoves();
				avgMoves += moves;
				maxMoves = maxMoves > moves ? maxMoves : moves;
				if (result.count(moves) == 1) // if this result in the map
					result.at(moves)++;else
					result.emplace(moves, 1);
				break;
			case 4:
				s5.play(g);
				moves = s5.getMoves();
				avgMoves += moves;
				maxMoves = maxMoves > moves ? maxMoves : moves;
				if (result.count(moves) == 1) // if this result in the map
					result.at(moves)++;else
					result.emplace(moves, 1);
				break;
			case 5:
				s6.play(g);
				moves = s6.getMoves();
				avgMoves += moves;
				maxMoves = maxMoves > moves ? maxMoves : moves;
				if (result.count(moves) == 1) // if this result in the map
					result.at(moves)++;else
					result.emplace(moves, 1);
				break;
			default:
				break;
			}

		}

		avgMoves = avgMoves / 1296;

		switch (j) {

		case 0:
			f << "lexicographic strategy:" << endl
					<< "______________________________" << endl;
			break;
		case 1:
			f << "Random strategy with seed 0:" << endl
					<< "______________________________" << endl;
			break;
		case 2:
			f << "Random strategy with seed 1:" << endl
					<< "______________________________" << endl;
			break;
		case 3:
			f << "Knuth strategy:" << endl << "______________________________"
					<< endl;
			break;
		case 4:
			f << "Entrophy strategy:" << endl
					<< "______________________________" << endl;
		case 5:
			f << "Most Parts strategy:" << endl
					<< "______________________________" << endl;
			break;
		}

		f << "Average moves: " << avgMoves << endl;
		f << "Worst case moves: " << maxMoves << endl << endl;
		f << "Number of games that was resolved by..." << endl;
		for (auto pair : result)
			f << pair.first << " moves: " << pair.second << " games" << endl;

		result.clear();

	}
	return 0;

}
