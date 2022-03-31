
#include "lexicStrategy.h"
#include<graphics.h>
#include <thread>
#include "code.h"

lexicStrategy::lexicStrategy() : strategy() {


}

lexicStrategy::~lexicStrategy() {

}

void lexicStrategy::play(Game &g){
	
	initwindow(1000, 1000);

	int bulls, cows, row = 0;

	for (int j = 0; j < 1296; j++) {

		char str1[5];
		char str2[5];

		if (comb[j].getCode()[4] != -1) {
			for (int i = 0; i < 4; i++) {  // play the code
				std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // delay for visual simulation
				g.strategyPlay(comb[j].getCode()[i], row, i, comb[j], &bulls,&cows, 1);
				settextstyle(10, 0, 3);
				setcolor (YELLOW);
				outtextxy(796, 602, itoa(moves + 1, str2, 10));
			}

			moves++;
			strategy::filter(g, bulls, cows, comb[j]);
			settextstyle(10, 0, 1);
			setcolor (LIGHTRED);
			outtextxy(360, 7 + row * 40, "options left: ");
			outtextxy(510, 7 + row * 40,itoa(strategy::getCombSize(), str1, 10));

			row++;
			if (row == 18)  // end of board, build a new one 
				row = 0;

			if (bulls == 4)
				break;

		}
	}
		
}














