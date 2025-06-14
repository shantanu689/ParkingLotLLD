#include <iostream>
#include <deque>

using namespace std;

class FoodItem
{
    public:
        int row,col;
        
        FoodItem(int row, int col)
            : row(row), col(col) {}
};