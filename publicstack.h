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
 * bit1：是否确认转换 exchangeFileSure
 * bit2：文件转换类型（0为bin，1为hex） exchangeFileType
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
