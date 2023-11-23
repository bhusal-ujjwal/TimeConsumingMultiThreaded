#ifndef WORKER_H
#define WORKER_H

#include "QtCore/qdebug.h"
#include "QtCore/qrunnable.h"
#include <QObject>
#include <QThread>

class Worker : public QObject, public QRunnable {
    Q_OBJECT
public:
    explicit Worker(qint64 target, QObject *parent = nullptr);
    void run() override;

private:
  qint64 m_target;
  bool m_paused;
  bool m_stopped;

signals:
    void progress(int percent);
    void finished(qint64 result);
    void runningTimeChanged(int seconds);
    void estimatedTimeChanged(int estmtdTime);
    void disableStartButton();
    void enableStartButton();



public slots:
    void pause() { m_paused = true; }
    void stop() { m_stopped = true; }
};




#endif // WORKER_H
