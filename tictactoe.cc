#include "tictactoe.h"
#include <iostream> 
using namespace std; 

void showMenu(); 
TicTacToe game; 

int main() {

  showMenu();

  return 0; 
} 

void showMenu() {

  int option;

  system("clear");
  cout << "\033[1;32m\t\t  EDER Zedboard Tic-Tac-Toe  \t\t\n\033[0m" << endl;

  cout << "1. Single Player\n2. Multi Player\n3. Exit" << endl;
  cin >> option;

  switch (option) {
    case 1 : game.startGame();
             break;
    default : cout << "Bye.";
             break;
  }

}