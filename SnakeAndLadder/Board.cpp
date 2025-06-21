#ifndef BOARD_CPP
#define BOARD_CPP

#include <queue>
#include <unordered_map>
#include <map>
#include "GameObject.cpp"

using namespace std;

class Board
{
    private:
        unordered_map<int,int> playerToPositionMapping;
        map<int, GameObject*> positionToObjectMapping;
        int boardRows, boardCols;

    public:
        Board(vector<pair<int,int>> &gameObjects, int rows, int cols)
        {
            boardRows = rows;
            boardCols = cols;
            for(int i=0;i<gameObjects.size();i++)
            {
                if(positionToObjectMapping.count(gameObjects[i].first) > 0)
                {
                    throw "Invalid config supplied for objects on the board";
                }

                positionToObjectMapping[gameObjects[i].first] = new GameObject(gameObjects[i].first, gameObjects[i].second);
            }
        }

        ~Board()
        {
            for(auto it=positionToObjectMapping.begin(); it!=positionToObjectMapping.end();it++)
            {
                if(it->second != nullptr)
                {
                    delete it->second;
                }
            }
        }

        void AddPlayer(int playerId)
        {
            playerToPositionMapping[playerId] = 1;
        }

        bool MovePlayer(int playerId, int steps, string name)
        {
            // {1,0} 6 {1,1} 5 {1,2} 4
            // {0,0} 1 {0,1} 2 {0,2} 3
            int currPos = playerToPositionMapping[playerId];
            currPos += steps;

            if(currPos > boardRows*boardCols)
            {
                cout << name << " going out of board, skip moving" << endl;
                return false; // Player is going out of board so dont move
            }

            while(positionToObjectMapping.count(currPos) > 0)
            {
                GameObject* obj = positionToObjectMapping[currPos];
                if(obj->destination > obj->source)
                {
                    cout << name << " acquired ladder from " << obj->source << " to " << obj->destination << endl;
                }
                else
                {
                    cout << name << " bitten by snake from " << obj->source << " to " << obj->destination << endl;
                }

                currPos = obj->destination;
            }

            cout << name << " is now on " << currPos << endl;
            playerToPositionMapping[playerId] = currPos;

            if(currPos == boardRows*boardCols)
            {
                return true;
            }

            return false;
        }
};


#endif