#include "threadproducer.h"
#include "buffershared.h"
#include <QDebug>
#include <QMutexLocker>

ThreadProducer::ThreadProducer(QObject *parent) :
    QThread(parent),
    m_Stopped(false),
    m_IntToPrint(0)
{
    connect(this, SIGNAL(started()), this, SLOT(Reset()));
    connect(this, SIGNAL(finished()), this, SLOT(Reset()), Qt::DirectConnection);
}

void ThreadProducer::run()
{
    while (!m_Stopped)
    {
        // this ensures that we will exit this loop
        // either the button stop is clicked
        // or the main window is closed
        if (m_Stopped)
            break;

        gMutex.lock();
        // if the buffer is full then wait in the "buffer not full" condition
        if (gUsedSpace == BUFFER_SIZE)
        {
            if (m_Stopped)
                break;
            gBufferIsNotFull.wait(&gMutex);
        }
        gMutex.unlock();

        if (m_Stopped)
            break;

        QString msg = tr("Producer: index: %1").arg(QString::number(GetIntToPrint()));
        BufferShared::GetInstance()->setStringInBuffer(msg);

        gMutex.lock();
        ++gUsedSpace;
        gMutex.unlock();

        gBufferIsNotEmpty.wakeAll();

        emit onUpdProd(msg);

        msleep(50);
    }
}
void ThreadProducer::Stop()
{
    m_Stopped = true;
}

int ThreadProducer::GetIntToPrint()
{
    if (m_IntToPrint == MAX_VALUE)
        m_IntToPrint = 0;
    return m_IntToPrint++;
}

void ThreadProducer::Reset()
{
    m_Stopped = false;
}
