#ifndef TTTBOARD_H
#define TTTBOARD_H

#include <iostream>
#include <vector>

using namespace std;

class tttboard
{
	public:

		tttboard(int n);

		vector<int> getBoard();

		tttboard(int n, vector<int> b);

		vector<tttboard> possibleNextBoards(int turn) const;

		//copy constructor
		tttboard(const tttboard& a);

		friend ostream& operator<< (ostream& output, const tttboard& a);

		bool operator== (const tttboard& a) const;

	private:
 		vector<int> b_;
		int n_;	
};

#endif 
