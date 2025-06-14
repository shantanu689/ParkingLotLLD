#include <iostream>
#include "Snake.cpp"
#include "Food.cpp"

using namespace std;

class SnakeGame
{
    private:
        int boardHeight,boardWidth;
        Snake* snake;
        FoodItem* food;
        int score;

        FoodItem* GenerateFoodItem()
        {
            int foodItemRow,foodItemCol;
            do
            {
                foodItemRow = rand() % boardHeight;
                foodItemCol = rand() % boardWidth;
            } while (snake->snakePositionSet.count({foodItemRow, foodItemCol}) > 0);

            FoodItem* newFoodItem = new FoodItem(foodItemRow, foodItemCol);
            return newFoodItem;
        }

        pair<int,int> GetNewHead(pair<int,int> currHead, char input)
        {
            pair<int,int> delta;
            switch(input)
            {
                case 'U': delta = {-1,0}; break;
                case 'D': delta = {1,0}; break;
                case 'L': delta = {0,-1}; break;
                case 'R': delta = {0,1};
            }
            
            pair<int,int> newHead = {(currHead.first + delta.first + boardHeight)%boardHeight, (currHead.second + delta.second + boardWidth)%boardWidth};
            return newHead;
        }

    public:
        SnakeGame(int boardHeight, int boardWidth)
        {
            this->boardHeight = boardHeight;
            this->boardWidth = boardWidth;
            snake = new Snake();            
            food = GenerateFoodItem();
            score = 0;
        }

        ~SnakeGame()
        {
            delete snake;
            delete food;
        }

        int Move(char inputMove)
        {
            pair<int,int> currHead = snake->snakePosition[0];
            pair<int,int> newHead = GetNewHead(currHead, inputMove);

            bool genenateNewFood = false;
            if(food->row == newHead.first && food->col == newHead.second)
            {
                score++;
                genenateNewFood = true;
            }
            else
            {
                pair<int,int> tail = snake->snakePosition.back();
                snake->snakePositionSet.erase(tail);
                snake->snakePosition.pop_back();
            }

            if(snake->snakePositionSet.count(newHead) > 0)
            {
                cout << "GAME OVER: Your final score is " << score << endl;
                return -1;
            }

            snake->snakePosition.push_front(newHead);
            snake->snakePositionSet.insert(newHead);

            if(genenateNewFood)
            {
                delete food;
                food = GenerateFoodItem();
            }

            return score;
        }

        void DisplayBoard()
        {
            for(int i=0;i<boardHeight;i++)
            {
                for(int j=0;j<boardWidth;j++)
                {
                    if(food->row == i && food->col == j)
                    {
                        cout << "F";
                    }
                    else if(snake->snakePositionSet.count({i,j}) > 0)
                    {
                        pair<int,int> coordinate = {i,j};
                        if(snake->snakePosition[0] == coordinate)
                        {
                            cout << "H";
                        }
                        else if(snake->snakePosition.back() == coordinate)
                        {
                            cout << "T";
                        }
                        else
                        {
                            cout << "S";
                        }                        
                    }
                    else
                    {
                        cout << ".";
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
};