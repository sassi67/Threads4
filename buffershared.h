#ifndef BUFFERSHARED_H
#define BUFFERSHARED_H

#include <QString>
#include <QWaitCondition>
#include <QMutex>

// global variables
extern int gUsedSpace;
extern QWaitCondition gBufferIsNotFull;
extern QWaitCondition gBufferIsNotEmpty;
extern QMutex gMutex;

static const int BUFFER_SIZE = 4096;

class BufferShared
{
public:
    static BufferShared *GetInstance();

    void setStringInBuffer(const QString& s);
    QString getStringFromBuffer();

private:
    BufferShared();
    BufferShared(const BufferShared& rhs);
    BufferShared& operator=(const BufferShared& rhs);

    static BufferShared *m_Instance;

    QString m_Buffer[BUFFER_SIZE];
    static int m_IndexSet;
    static int m_IndexGet;

};

#endif // BUFFERSHARED_H
