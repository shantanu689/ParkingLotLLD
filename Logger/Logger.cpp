#include <iostream>
#include "LevelLogger.cpp"
#include "LogManager.cpp"
#include "LogSubject.cpp"

using namespace std;

class Logger
{
    private:
        AbstractLevelLogger* levelLogger;
        LogSubject* logSubject;

        Logger()
        {   
            levelLogger = LogManager::BuildChainOfLoggers();
            logSubject = LogManager::BuildLogSubject();
        }

        Logger(const Logger& obj) = delete;
        Logger& operator=(const Logger& obj) = delete;

    public:
        ~Logger()
        {
            delete levelLogger;
            delete logSubject;
        }

        static Logger& GetInstance()
        {
            //this is inherently thread-safe
            static Logger instance;
            return instance;
        }
        
        void Debug(string message)
        {
            levelLogger->LogMessage(0, message, logSubject);
        }

        void Info(string message)
        {
            levelLogger->LogMessage(1, message, logSubject);
        }

        void Error(string message)
        {
            levelLogger->LogMessage(2, message, logSubject);
        }
};