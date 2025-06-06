#ifndef LOGSUBJECT_CPP
#define LOGSUBJECT_CPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include "LogObserver.cpp"

using namespace std;

class LogSubject
{
    private:
        unordered_map<int,vector<ILogObserver*>> observers;
    public:
        ~LogSubject()
        {
            for(auto it=observers.begin();it!=observers.end();it++)
            {
                for(auto observer : it->second)
                {
                    delete observer;
                }
            }
        }

        void AddObserver(ILogObserver* observer, int logLevel)
        {
            observers[logLevel].push_back(observer);
        }

        void RemoveObserver(ILogObserver* observer)
        {
            //implement
        }

        void NotifyObservers(string data, int logLevel)
        {
            for(int i=0;i<observers[logLevel].size();i++)
            {
                observers[logLevel][i]->HandleEvent(data);
            }
        }   
};

#endif