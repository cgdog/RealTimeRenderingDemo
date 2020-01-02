#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <ctime>

namespace LXY {


class TimeManager
{
public:
    TimeManager();
    ~TimeManager();

    void initialize();
    int getTime();

private:
    time_t initTime;

};

}
#endif // TIMEMANAGER_H
