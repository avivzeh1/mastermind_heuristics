#include <iostream>
#include "code.h"
#include<ctime>
#include<cstdlib>
using namespace std;
code::code() {

	srand(time(NULL));
	
	for(int i = 0; i < 4; i++)
		c[i] = rand() % 6;
		c[4] = 6;
}

code::code(const code& oth){
	
	for(int i = 0; i < 5; i++)
	  c[i] = oth.getCode()[i];
}

code::code(int i, int j, int k, int l){
	
	c[0] = i;
	c[1] = j;
	c[2] = k;
	c[3] = l;
	c[4] = 6;  //mark use
}

code::~code() {
	// TODO Auto-generated destructor stub
}

const int* code::getCode() const{
	return c;
}

void code::setCode(int index, int val){
	
	if(index <= 4 && index >= 0)
		c[index] = val;
}

code& code::operator=(const code& oth){
	
	if(&oth == this)
		return *this;
	
	for(int i = 0; i < 5; i++)
	  	c[i] = oth.getCode()[i];
	  
	return *this;
			
}

ostream & operator<<(ostream& out, const code& c) {

	for (int i = 0; i < 4; i++)
		cout << c.getCode()[i];
		
	cout << endl;
	return out;
}

