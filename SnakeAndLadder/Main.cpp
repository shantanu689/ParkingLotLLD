#include <iostream>
#include "SnakeAndLadderGame.cpp"

using namespace std;

int main()
{
    int boardRows = 4, boardCols = 4;
    int numberOfDice = 1;
    vector<pair<int,int>> gameObjects = {{5,1},{2,6},{10,1},{7,9},{11,15},{13,8}};
    SnakeAndLadderGame game(boardRows, boardCols, gameObjects, numberOfDice);
    game.AddPlayer("Shantanu");
    game.AddPlayer("Sumant");
    game.StartGame();
}