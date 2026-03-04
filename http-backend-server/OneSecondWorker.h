//
// Created by Connor on 2/16/2026.
//
#include <QDebug>
#include <QThread>

#include "MfamDataSample.h"

class OneSecondWorker : public QObject
{
    Q_OBJECT
    public:
    OneSecondWorker(QObject *parent = nullptr,
        QVector<MfamDataSample*> *dataSamples = nullptr) : QObject(parent), dataSamples(dataSamples) {}
    ~OneSecondWorker() { qDebug() << "oneSecondWorker destroyed"; }

    public slots:
    void work()
    {
        while (true)
        {
            QThread::msleep(500);
            if (dataSamples->size() == 1000)
                qDebug() << "oneSecondWorker working";
        }
    }

    signals:
    void finished();
    void error(QString error);

    private:
    QVector<MfamDataSample*> *dataSamples;
};