#ifndef LOGOBSERVER_CPP
#define LOGOBSERVER_CPP

#include <iostream>

using namespace std;

class ILogObserver
{
    public:
        virtual void HandleEvent(string data) = 0;        
};


class ConsoleLogger : public ILogObserver
{
    public:
        void HandleEvent(string data) override
        {
            cout << "Console: " << data << endl;
        }
};

class FileLogger : public ILogObserver
{
    public:
        void HandleEvent(string data) override
        {
            cout << "File: " << data << endl;
        }
};

#endif