#include "tttboard.h"
#include "gTree.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

gTree<tttboard>tttTree;
gTree<tttboard>myTree;

void Tokenize(string line, vector<string> & tokens, string delimiters = "\t ")
{
string token = "";
        string OneCharString = " ";
        for (int i=0; i<line.size(); i++)
                if (find(delimiters.begin(), delimiters.end(), line[i])!=delimiters.end()) // line[i] is one of the delimiter characters
                {
                        if (token != "")
                                tokens.push_back(token);
                        token = "";
                }
                else
                {
                        OneCharString[0] = line[i];
                        token +=OneCharString;
                }

        if (token != "")
                tokens.push_back(token);
}

int getTurn(vector<int> b)
{
	int s = 0; 
	for (int i=0; i<b.size(); i++)
		s+=b[i];
	if (s==0)
		return 1;
	else 
		return -1;
}


bool fullboard(tttboard a, int size) //returns true if there are no empty spaces
{
	for (int i=0;i<size;i++)
	{
		if (a.getBoard()[i]==0)
			return false;
	}
	return true;
}

void iqra (gTNode<tttboard>* p,int n, int turn)
{
	if (fullboard(p->getData(),n)) 
	{ //ok
		return; 
	}
	else
	{                        //ok
		vector<tttboard>children;
		for (int i=0;i<p->getData().possibleNextBoards(turn).size();i++)
		{
			children.push_back(p->getData().possibleNextBoards(turn)[i]);
		}
		turn*=-1;
		for (int i=0;i<children.size();i++)
		{

			//tttTree.addNode(children[i],findItem(tttTree.getRoot(), p->getData()));
			//
			tttTree.addNode(children[i],p);
			iqra(p->getChildren()[i],n,turn);
		}
	}
}

bool isWin(vector<int> board, int mark) 
{                        // is mark the winner?
    int win = 3*mark;                           // +3 for X and -3 for O
    return ((board[0] + board[1] + board[2] == win)        // row 0
         || (board[3] + board[4] + board[5] == win)        // row 1
         || (board[6] + board[7] + board[8] == win)        // row 2
         || (board[0] + board[3] + board[6] == win)        // column 0
         || (board[1] + board[4] + board[7] == win)        // column 1
         || (board[2] + board[5] + board[8] == win)        // column 2
         || (board[0] + board[4] + board[8] == win)        // diagonal
         || (board[2] + board[4] + board[6] == win));      // diagonal
}

char status(gTNode<tttboard>* a, int turn)
{
	if ( fullboard( a->getData() , 9 ) )                       
	{ //board is full
		if (isWin(a->getData().getBoard(),turn) && isWin(a->getData().getBoard(),turn*-1))
			cout<< "INVALID!"<<endl;
		if (isWin(a->getData().getBoard(),turn))
			return 'w';
		if (isWin(a->getData().getBoard(),turn*-1))
			return 'l';

		return 'n';
	}
	if (isWin(a->getData().getBoard(),turn))
		return 'w';
	if (isWin(a->getData().getBoard(),turn*-1))
		return 'l';

	//base cases done

	for (int i=0;i<a->getChildren().size();i++)
	{
		if ( status(a->getChildren()[i], turn*-1)=='l' ) //winning
			 return 'w';
	}
	 //not winning
	for (int i=0;i<a->getChildren().size();i++)
	{
		if ( status(a->getChildren()[i], turn*-1)=='n' ) //not sure
			return 'n';
	}
	return 'l';	
}


int main(int argc, char** argv)
{
	if (argc==2)
	{
		int n=atoi(argv[1]);
		int length = n*n;
		tttboard root(n);
		
		tttTree.addNode(root,NULL);
		//=============================================================when to stop?
		iqra (tttTree.getRoot(), length, 1);

		cout << "preorder:\n" ;
		preorderPrint(tttTree.getRoot());
		cout <<"\npostorder:\n";
		postorderPrint(tttTree.getRoot());
		cout << "\nsize:" << size(tttTree.getRoot())<< endl;
		return 0;
	}

	else if (argc==3)  //losing winning board
	{
		int n= atoi(argv[1]);
		string str_board = argv[2];
		vector<string> tokens;
		Tokenize(str_board,tokens," {,}");
		vector<int> board;
		for (int i=0; i<tokens.size(); i++)
		{
			board.push_back(atoi(tokens[i].c_str()));
		}
		if (n*n!= board.size())
		{
			cout<< "n and board are not consistent!\n";
			return 1;
		}

		int length= n*n;
		tttboard p(n,board);
		int turn = getTurn(board);

		myTree.addNode(p,NULL);
		iqra (myTree.getRoot(), length, turn);

		char yes=status(myTree.getRoot(),turn);
		if (yes=='w')
			cout<<"winning board"<<endl;
		else if (yes=='l')
			cout<<"losing board"<<endl;
		else if (yes=='n')
			cout<<"not sure"<<endl;

		
		return 0;
		
	}
}