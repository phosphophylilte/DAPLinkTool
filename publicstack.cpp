#include "publicstack.h"

QMutex program_mutex;
QString startAddress = "0x08000000";
uint8_t eventFlag = 0;

publicStack::publicStack()
{

}
