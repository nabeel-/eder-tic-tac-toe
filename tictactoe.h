#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int P1 = 1; 
int P2 = 2; // CPU if single player mode
int current_pos = 0;

class TicTacToe { 

  int board[9];
  int turn; 
  int winner; 

  void play(int cpu); 

public: 
  void startGame(int cpu);  
  
protected:
  int nextOpenPos();
  int tryMove(int i);
  int checkForWin(int b[9]); 
  int minimax(int b[9], int player);
  void draw();
  void computerMove();
  void moveCharTo(int i);
  void potentialMove(int i);
  void mutateBoard(int i, int f, int dir);
};

///////////////////////////////////////////////////////////////////////////////
// Game Runners

void TicTacToe::startGame(int cpu) { 
  turn   = P1;  
  winner = 0;

  for(int i = 0; i < 9; i++) {
    board[i] = 0;
  } 
  play(cpu);  
}

void TicTacToe::play(int cpu) { 
  int c;
  draw();
  while (winner != turn) { 

    if(cpu && turn == 2) {
      computerMove();
    } else {
      cout << "Player " << turn << "'s turn.\n"; 
      c = getchar();
      potentialMove(c);
    }
    
  } 
  cout << "Player Number " << turn << " Wins!" << endl; 
} 

///////////////////////////////////////////////////////////////////////////////
// Drawing

void TicTacToe::draw() { 
  system("clear");
  cout << "\033[1;32m\t\t  EDER Zedboard Tic-Tac-Toe  \t\t\n\033[0m" << endl;

  int tmp_board[3][3];

  for(int i = 0; i < 9; i++) {
    int row, col;
    if(i <= 2) {
      row = 0;
      col = i;
    } else if (i <= 5) {
      row = 1;
      col = i - 3;
    } else {
      row = 2;
      col = i - 6;
    }
    tmp_board[row][col] = board[i];
  }

  for(int i = 0; i < 3; i++) {
    cout << "\t\t         |         |         " << endl;
    for(int j = 0; j < 3; j++) {
      string val;
      if(j == 0) cout << "\t\t";

      if(tmp_board[i][j] == 3) {
        string my_sym = (turn == 1) ? "X" : "O";
        val = "\033[1;32m" + my_sym + "\033[0m";
      } else {
        val = tmp_board[i][j] == 0 ? " " : tmp_board[i][j] == 1 ? "X" : "O";
      }

      j == 1 ? cout << "|    "<<val<< "    |" : cout <<"    "<<val<< "    ";
      
    }
    cout << "\n\t\t         |         |         \n";
    if(i != 2) cout << "\t\t-----------------------------" << endl;
  }
  cout << endl;
}

///////////////////////////////////////////////////////////////////////////////
// Main Movements 

void TicTacToe::computerMove() {
  int move = -1;
  int score = -2;
  int i;
  for(i = 0; i < 9; ++i) {
    if(board[i] == 0) {
      board[i] = 2;
      int tempScore = -minimax(board, 1);
      board[i] = 0;
      if(tempScore > score) {
        score = tempScore;
        move = i;
      }
    }
  }

  tryMove(move);
  draw();
}

void TicTacToe::potentialMove(int dir) {

  mutateBoard(current_pos, 0, dir);

  if(dir == 99) {
    tryMove(current_pos);
  } else {
    moveCharTo(dir);
  }

  mutateBoard(current_pos, 3, dir);
  draw();
}

int TicTacToe::tryMove(int i) {

  if(board[i] == 0 || board[i] == 3) {
    board[i] = turn;
  } else {
    cout << "Invalid move." << endl;
  }

  winner = checkForWin(board);
  
  if (winner != turn) { 
    turn = turn == P1 ? P2 : P1;     
    mutateBoard(current_pos, 0, 119);
    current_pos = nextOpenPos();
  };
  return i; 
}

///////////////////////////////////////////////////////////////////////////////
// Movement Helpers

void TicTacToe::moveCharTo(int dir) {
  switch(dir) {
    case 119: // Up
      // need to handle negative case separate
    current_pos = (current_pos - 3) < 0 ? current_pos + 6 : current_pos - 3;
    break;
    case 115: // Down
    current_pos = (current_pos + 3) > 8 ? current_pos - 6 : current_pos + 3;
    break;
    case 100: // Left
    current_pos = (current_pos + 1) % 3 == 0 ? current_pos - 2 : current_pos + 1;
    break;
    case 97: // Right
    current_pos = (current_pos % 3 == 0) ? current_pos + 2 : current_pos - 1;
    break;
  }
}

int TicTacToe::nextOpenPos() {
  for(int i = 0; i < 9; i++) {
    if(board[i] == 0) {
      return i;
    }
  }
  return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Board Manipulation

void TicTacToe::mutateBoard(int pos, int flag, int dir) {
  // Don't overwrite x's or o's values
  if(board[pos] == 0 || board[pos] == 3) {
    board[pos] = flag;
  } else {
    moveCharTo(dir);
  }
}

int TicTacToe::checkForWin(int board[9]) { 
  unsigned wins[8][3] = { {0,1,2},{3,4,5},{6,7,8},
  {0,3,6},{1,4,7},{2,5,8},
  {0,4,8},{2,4,6}};
  int i;
  for(i = 0; i < 8; ++i) {
    if(board[wins[i][0]] != 0 &&
     board[wins[i][0]] == board[wins[i][1]] &&
     board[wins[i][0]] == board[wins[i][2]])
      return board[wins[i][2]];
  }
  return 0;
} 

///////////////////////////////////////////////////////////////////////////////
// CPU Movement Algorithm

int TicTacToe::minimax(int b[9], int player) {
  int w = checkForWin(b);
  if(w != 0) return player == turn ? player * turn : player * -turn;

  int move = -1;
  int score = -2;
  int i;
  for(i = 0; i < 9; ++i) {
    if(b[i] == 0) {
      b[i] = player;
      int thisScore = -minimax(b, (player % 2) + 1);
      if(thisScore > score) {
        score = thisScore;
        move = i;
      }
      b[i] = 0;
    }
  }
  if(move == -1) return 0;
  return score;
}

























