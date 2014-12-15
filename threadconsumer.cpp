#include "threadconsumer.h"
#include "buffershared.h"
#include <QDebug>

ThreadConsumer::ThreadConsumer(QObject *parent) :
    QThread(parent),
    m_Stopped(false)
{
    connect(this, SIGNAL(started()), this, SLOT(Reset()));
    connect(this, SIGNAL(finished()), this, SLOT(Reset()));
}

void ThreadConsumer::run()
{
    while (!m_Stopped)
    {
        // this ensures that we will exit this loop
        // either the button stop is clicked
        // or the main window is closed
        if (m_Stopped)
            break;

        gMutex.lock();
        //qDebug() << "Consumer: " << gUsedSpace;
        // if the buffer is empty then wait in the "buffer not empty" condition
        if (gUsedSpace == 0)
        {
            if (m_Stopped)
                break;
            gBufferIsNotEmpty.wait(&gMutex);
        }
        gMutex.unlock();

        if (m_Stopped)
            break;
        QString msg = tr("Consumer: %1").arg(BufferShared::GetInstance()->getStringFromBuffer());
        //qDebug() << msg;
        gMutex.lock();
        --gUsedSpace;
        gMutex.unlock();

        gBufferIsNotFull.wakeAll();

        emit onUpdCons(msg);

        msleep(50);
    }


}

void ThreadConsumer::Stop()
{
    m_Stopped = true;

}

void ThreadConsumer::Reset()
{
    m_Stopped = false;
}
