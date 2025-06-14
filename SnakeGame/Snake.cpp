#include <iostream>
#include <unordered_set>
#include <set>
#include <deque>

using namespace std;

class Snake
{
    public:
        deque<pair<int,int>> snakePosition;
        set<pair<int,int>> snakePositionSet;
        
        Snake()
        {
            snakePosition.push_back({0,0});
            snakePositionSet.insert({0,0});
        }
};