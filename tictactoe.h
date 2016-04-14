#include <iostream>
#include <string>
using namespace std;

int P1 = 1; 
int P2 = 2;
int current_pos = 1;

class TicTacToe { 

  int board[3][3];
  int turn; 
  int winner; 

  void play(); 

public: 
  void startGame();  
  void nextTurn(); 
  int  move(int); 

  void checkForWin(); 
  void draw();

protected:
  void initBoard();
  void potentialMove(int);
  void mutateBoard(int, int);
}; 

void TicTacToe::startGame() { 
  turn   = P1;  
  winner = 0;

  initBoard(); 
  play();  
} 

// Helper function to initialize the board
void TicTacToe::initBoard() {
  int i,j;
  for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
      board[i][j] = 0;
    }
  }
}

int TicTacToe::move(int i) {
  nextTurn();

  return i; 
} 

void TicTacToe::nextTurn() {
  turn = turn == P1 ? P2 : P1; 
} 

void TicTacToe::checkForWin() { 
  
} 

void TicTacToe::play() { 
  //int imove = 0;
  int c;
  draw();
  while (winner != turn) { 
    cout << "Player " << turn << "'s turn.\n"; 
    c = getchar();
    potentialMove(c);
  } 
  cout << "Player Number " << turn << " Wins!" << endl; 
} 

void TicTacToe::draw() { 
  system("clear");
  cout << "\033[1;32m\t\t  EDER Zedboard Tic-Tac-Toe  \t\t\n\033[0m" << endl;
  for(int i = 0; i < 3; i++) {
    cout << "\t\t         |         |         " << endl;
    for(int j = 0; j < 3; j++) {
      string val;
      if(j == 0) cout << "\t\t";

      if(board[i][j] == 3) {
        val = "\033[1;32mP\033[0m";
      } else {
        val = board[i][j] == 0 ? " " : board[i][j] == 1 ? "X" : "O";
      }

      j == 1 ? cout << "|    " << val << "    |" : cout << "    " << val << "    ";
      
    }
    cout << "\n\t\t         |         |         \n";
    if(i != 2) cout << "\t\t-----------------------------" << endl;
  }
  cout << endl;
}

// Show the move as a potential move
// dir is:
//    119 : Up
//    115 : Down
//    100 : Right
//    97  : Left
void TicTacToe::potentialMove(int dir) {

  mutateBoard(current_pos, 0);

  switch(dir) {
    case 119:
        // need to handle negative case separate
        current_pos = (current_pos - 3) < 0 ? current_pos + 6 : current_pos - 3;
        break;
    case 115:
        current_pos = (current_pos + 3) % 9;
        break;
    case 100:
        current_pos = current_pos % 3 == 0 ? current_pos - 2 : current_pos + 1;
        break;
    case 97:
        current_pos = ((current_pos - 1) % 3 == 0) ? current_pos + 2 : current_pos - 1;
        break;
    
  }

  mutateBoard(current_pos, 3);
  draw();
}

void TicTacToe::mutateBoard(int pos, int flag) {
  int row, col;

  if(current_pos <= 3) {
    row = 0;
    col = current_pos - 1;
  } else if (current_pos <= 6) {
    row = 1;
    col = current_pos - 4;
  } else {
    row = 2;
    col = current_pos - 7;
  }

  // Don't overwrite x's or o's values
  if(board[row][col] == 0 || board[row][col] == 3) {
    board[row][col] = flag;
  }
}




















