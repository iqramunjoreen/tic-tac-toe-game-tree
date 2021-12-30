#include "tttboard.h"
#include <vector>
#include <iostream>

using namespace std;


tttboard::tttboard(int n)
{
	n_ = n;
	for (int i=0; i<n*n; i++)
		b_.push_back(0);
}

tttboard::tttboard(const tttboard& a)
{
	this->n_=a.n_;
	for (int i=0;i<n_*n_;i++)
	{
		this->b_.push_back(a.b_[i]);
	}
}

tttboard::tttboard(int n, vector<int> b)
{
	this->n_=n;
	this->b_=b;
}

vector<int> tttboard::getBoard()
{
	return this->b_;
}

vector<tttboard> tttboard::possibleNextBoards(int turn) const
{
	vector<tttboard> children;
	//ToDo for step 2
	for (int i=0;i<n_*n_;i++)
	{
		tttboard temp(*this);
		if (temp.b_[i]==0)
		{
			temp.b_[i]=turn;
			children.push_back(temp);
		}
	}

	return children;		
}

bool tttboard::operator== (const tttboard& a) const
{
	for (int i=0;i<n_*n_;i++)
	{
		if (this->b_[i]!=a.b_[i])
			return false;
	}
	return true;
}

ostream& operator<< (ostream& output, const tttboard& a)
{
	output<<"{";
	for (int i=0;i<a.n_*a.n_;i++)
	{
		output<<a.b_[i]<<",";
	}
	output<<"\b} ";

	return output;
}


