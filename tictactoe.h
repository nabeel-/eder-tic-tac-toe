#include <iostream> 
#include <curses.h>
using namespace std;

int P1 = 1; 
int P2 = 2;

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
  int imove = 0; 
  while (winner != turn) { 
    draw();
    cout << "Player " << turn << "'s turn.\n"; 

    while(imove < 10) {
      int c;
      switch((c = getch())) {
        case KEY_UP:
            cout << endl << "Up" << endl;//key up
            imove++;
            break;
        case KEY_DOWN:
            cout << endl << "Down" << endl;   // key down
            imove++;
            break;
        case KEY_LEFT:
            cout << endl << "Left" << endl;  // key left
            imove++;
            break;
        case KEY_RIGHT:
            cout << endl << "Right" << endl;  // key right
            imove++;
            break;
        }
    }
    
    move(imove); 
  } 
  cout << "Player Number " << turn << " Wins!" << endl; 
} 

void TicTacToe::draw() { 
  system("clear");
  cout << "\033[1;32m\t\t  EDER Zedboard Tic-Tac-Toe  \t\t\n\033[0m" << endl;
  for(int i = 0; i < 3; i++) {
    cout << "\t\t         |         |         " << endl;
    for(int j = 0; j < 3; j++) { 
      if(j == 0) cout << "\t\t";
      char val = board[i][j] == 0 ? ' ' : board[i][j] == 1 ? 88 : 79;

      j == 1 ? cout << "|    " << val << "    |" : cout << "    " << val << "    ";
      
    }
    cout << "\n\t\t         |         |         \n";
    if(i != 2) cout << "\t\t-----------------------------" << endl;
  }
  cout << endl;
}




















