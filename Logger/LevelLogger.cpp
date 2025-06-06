#ifndef LEVELLOGGER_CPP
#define LEVELLOGGER_CPP

#include <iostream>
#include "LogSubject.cpp"
using namespace std;

class AbstractLevelLogger
{
    protected:
        AbstractLevelLogger* nextLogger;
        int logLevel;

        virtual void HandleMessage(string message, LogSubject* logSubject) = 0;

    public:
        AbstractLevelLogger(int logLevel)
            : logLevel(logLevel), nextLogger(nullptr) {}

        ~AbstractLevelLogger()
        {
            delete nextLogger;
        }

        void SetNextLogger(AbstractLevelLogger* _nextLogger)
        {
            nextLogger = _nextLogger;
        }    

        void LogMessage(int logLevel, string message, LogSubject* logSubject)
        {
            if(this->logLevel <= logLevel)
            {
                HandleMessage(message, logSubject);
                if(nextLogger != nullptr)
                {
                    nextLogger->LogMessage(logLevel, message, logSubject);
                }                
            }
        }
};


class DebugLogger : public AbstractLevelLogger
{
    public:
        DebugLogger(int logLevel)
            : AbstractLevelLogger(logLevel) {}

        void HandleMessage(string message, LogSubject* logSubject) override
        {
            //cout << "DEBUG: " << message << endl;
            logSubject->NotifyObservers(message, this->logLevel);
        }
};

class InfoLogger : public AbstractLevelLogger
{
    public:
        InfoLogger(int logLevel)
            : AbstractLevelLogger(logLevel) {}

        void HandleMessage(string message, LogSubject* logSubject) override
        {
            //cout << "INFO: " << message << endl;
            logSubject->NotifyObservers(message, this->logLevel);
        }
};

class ErrorLogger : public AbstractLevelLogger
{
    public:
        ErrorLogger(int logLevel)
            : AbstractLevelLogger(logLevel) {}

        void HandleMessage(string message, LogSubject* logSubject) override
        {
            //cout << "ERROR: " << message << endl;
            logSubject->NotifyObservers(message, this->logLevel);
        }
};

#endif