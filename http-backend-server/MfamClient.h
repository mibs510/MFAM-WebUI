//
// Created by Connor on 2/8/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMCLIENT_H
#define HTTP_BACKEND_SERVER_MFAMCLIENT_H
#include <qabstractsocket.h>
#include <QThread>
#include <QTcpSocket>
#include <QTimer>

#include "MfamDataSample.h"
#include "Settings.h"


class MfamClient : public QObject
{
Q_OBJECT
public:
    MfamClient(QObject *parent = nullptr,
        QVector<MfamDataSample*> *dataSamples = nullptr,
        QVector<QJsonObject> *jsonDataSamples = nullptr);
    /* ~MfamClient(); */
    void connectToMFAM(QHostAddress mfamIpAddress, quint16 mfamPort);

private slots:
    void onConnect() const;
    void onReadyRead();
    void processDataBlock();
    static void onErrorOccurred(QAbstractSocket::SocketError error);
    void disconnectFromMFAM() const;

private:
    QTcpSocket *socket;
    QHostAddress ipAddress;
    uint16_t port;
    QByteArray packetBuffer;
    QVector<MfamDataSample*> *dataSamples;
    QVector<QJsonObject> *jsonDataSamples;
    uint8_t dataBlocks = 0;
};


#endif //HTTP_BACKEND_SERVER_MFAMCLIENT_H