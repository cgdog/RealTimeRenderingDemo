#include "timemanager.h"

namespace LXY {


TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::initialize()
{
    time(&initTime);
}

int TimeManager::getTime()
{
    return static_cast<int>(time(nullptr) - initTime);
}


}
