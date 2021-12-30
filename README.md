# tic-tac-toe-game-tree

Game trees are of interest because they are helpful for finding the best next move or for determining if there is any chance of winning
(otherwise one could resign). Given any state of a game, if all next states are winning states (for the other player), this state is a losing state
(because no matter what move the current player plays, they will end up in a state that the other player can win); and if at least one of the next
states are a losing state (for the other player) this state is a winning state because the current player has one move that he/she can play that leads
to the ultimate loss of the other player. While not all games can be played only based on game trees, some are simple enough that this approach is
attemptable. An example of such simple game is Tic-Tac-Toe.

Tic-Tac-Toe can be represented as a tree where nodes are boards and children of a board are all possible boards that we can get from the current board
by playing only one move.

This program implements a tree of tic-tac-toe and determining if the player who's to play a given board will win or will lose. 
We will assume that X always starts the game and is presented as 1 on the board and O always plays second and is presented as -1 on the board.

try it:

g++ -c tttboard.cpp

g++ -o tic_tac_toe.o tic_tac_toe.cpp tttboard.o

./tic_tac_toe.o 3 "{0,1,1,-1,0,1,0,0,-1}"

winning board

./tic_tac_toe.o 3 "{-1,1,1,-1,0,1,0,0,-1}"

losing board

./tic_tac_toe.o 3 "{0,0,0,0,0,0,0,0,0}"

not sure
