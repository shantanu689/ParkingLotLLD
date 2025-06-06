#include "LevelLogger.cpp"
#include "LogSubject.cpp"
#include "LogObserver.cpp"

using namespace std;

class LogManager
{   
    public:
        static AbstractLevelLogger* BuildChainOfLoggers()
        {
            AbstractLevelLogger* debugLogger = new DebugLogger(0);
            AbstractLevelLogger* infoLogger = new InfoLogger(1);
            AbstractLevelLogger* errorLogger = new ErrorLogger(2);

            debugLogger->SetNextLogger(infoLogger);
            infoLogger->SetNextLogger(errorLogger);

            return debugLogger;
        }

        static LogSubject* BuildLogSubject()
        {
            LogSubject* logSubject = new LogSubject();
            ILogObserver* consoleLogger = new ConsoleLogger();
            ILogObserver* fileLogger = new FileLogger();
            
            logSubject->AddObserver(consoleLogger, 0);
            logSubject->AddObserver(fileLogger, 1);
            return logSubject;
        }
};