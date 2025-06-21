#ifndef GAMEOBJECT_CPP
#define GAMEOBJECT_CPP

#include <iostream>

using namespace std;

class GameObject
{
    public:
        int source, destination;
        
        GameObject(int source, int destination)
            : source(source), destination(destination) {}

};

#endif