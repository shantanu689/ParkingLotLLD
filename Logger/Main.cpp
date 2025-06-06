#include <iostream>
#include "Logger.cpp"

using namespace std;

int main()
{
    Logger& logger = Logger::GetInstance();
    logger.Debug("Entered part 1");
    logger.Info("Completed Database call");
    logger.Error("Failed to send HTTP request missing credentials");
}