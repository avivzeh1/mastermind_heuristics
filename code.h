#ifndef CODE_H_
#define CODE_H_
#include <iostream>
using namespace std;

class code {
	
	int c[5];
	
public:
	code();
	code(const code& oth);
	code(int i, int j, int k, int l);
	virtual ~code();
	code& operator=(const code& oth);
	friend ostream& operator<<(ostream&, const code&);
	const int* getCode() const;
	void setCode(int index, int val); // set val in c[index]
};

#endif /* CODE_H_ */
