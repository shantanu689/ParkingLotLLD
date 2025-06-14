#include <iostream>
#include "SnakeGame.cpp"

using namespace std;

int main()
{
    int height, width;
    cout << "Enter board height and width" << endl;
    cin >> height >> width;
    SnakeGame game(height, width);

    int score;
    do
    {
        game.DisplayBoard();
        cout << "Enter your move: " << endl;
        char inputMove;
        cin >> inputMove;
        score = game.Move(inputMove);
        if(score != -1)
        {
            cout << "Your score is: " << score << endl;
        }
    } while (score != -1);
    
}