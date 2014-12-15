#include "buffershared.h"

int gUsedSpace = 0;
QWaitCondition gBufferIsNotFull;
QWaitCondition gBufferIsNotEmpty;
QMutex gMutex;

BufferShared* BufferShared::m_Instance = NULL;
int  BufferShared::m_IndexGet = 0;
int  BufferShared::m_IndexSet = 0;

BufferShared* BufferShared::GetInstance()
{
    if (NULL == m_Instance)
    {
        m_Instance = new BufferShared();
    }

    return m_Instance;
}

void BufferShared::setStringInBuffer(const QString &s)
{
    if (m_IndexSet == BUFFER_SIZE)
        m_IndexSet = 0;

    m_Buffer[m_IndexSet++] = s;
}

QString BufferShared::getStringFromBuffer()
{
    if (m_IndexGet == BUFFER_SIZE)
        m_IndexGet = 0;

    return m_Buffer[m_IndexGet++];
}

BufferShared::BufferShared()
{
}
