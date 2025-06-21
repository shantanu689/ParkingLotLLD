#include <iostream>
#include <ctime>
#include <vector>
#include "Board.cpp"
#include "GameObject.cpp"

using namespace std;

class SnakeAndLadderGame
{
    private:
        Board* gameBoard;
        int numberOfDice;
        queue<int> playersQueue;
        unordered_map<int, string> playerIdToNameMapping;

        int RollDice()
        {
            int totalSteps = 0;
            for(int i=0;i<numberOfDice;i++)
            {
                totalSteps += (rand() % 6) + 1;
            }

            return totalSteps;
        }

    public:
        SnakeAndLadderGame(int rows, int cols, vector<pair<int,int>> &gameObjects, int numberOfDice)
        {
            gameBoard = new Board(gameObjects, rows, cols);
            this->numberOfDice = numberOfDice;
        }

        void AddPlayer(string userName)
        {
            // check that game hasnt started yet
            int currentPlayers = playersQueue.size();
            int newPlayerId = currentPlayers + 1;
            gameBoard->AddPlayer(newPlayerId);
            playersQueue.push(newPlayerId);
            playerIdToNameMapping[newPlayerId] = userName;
        }

        void StartGame()
        {
            srand(time(0));
            while(playersQueue.size() > 1)
            {
                int currentPlayer = playersQueue.front();
                playersQueue.pop();
                cout << playerIdToNameMapping[currentPlayer] << " please roll the dice" << endl;
                char c;
                cin >> c;

                int steps = RollDice();
                string playerName = playerIdToNameMapping[currentPlayer];
                cout << playerName << " has got total of " << steps << " on the dice(s)" << endl;

                if(gameBoard->MovePlayer(currentPlayer, steps, playerName))
                {
                    cout << "Player " << playerName << " has won the game!" << endl;
                }
                else
                {
                    playersQueue.push(currentPlayer); 
                } 
            }        
        }
};