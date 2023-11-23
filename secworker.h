#ifndef SECWORKER_H
#define SECWORKER_H

#include "QtCore/qdebug.h"
#include "QtCore/qrunnable.h"
#include <QObject>
#include <QThread>

class Secworker : public QObject, public QRunnable {
    Q_OBJECT
public:
    explicit Secworker(qint64 target, QObject *parent = nullptr);
    void run() override;

private:
  qint64 m_target;
  bool m_paused;
  bool m_stopped;

signals:
    void progressErato(qint64 p,int i);
    void finishedErato();
    void runningTimeChangedErato(int seconds);
    void estimatedTimeChangedErato(int estmtdTime);

public slots:
    void pause() { m_paused = true; }
    void stop() { m_stopped = true; }
};



#endif // WORKER2_H
