#ifndef PUBLICSTACK_H
#define PUBLICSTACK_H

#include <QSemaphore.h>
#include <QThread>
#include <QMutex>

extern QMutex program_mutex;
extern QString startAddress;

/***
 * 用户自设状态标志
 * bit0：是否确认烧写 writeFlashSure
 * bit1：
 * bit2：
 * bit3：
 * bit4：
 * bit5：
 * bit6：
 * bit7：
 */
extern uint8_t eventFlag;

#define writeFlashSure  (eventFlag>>7)

class publicStack
{
public:
    publicStack();
};

#endif // PUBLICSTACK_H
