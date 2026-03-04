//
// Created by Connor on 2/15/2026.
//

#ifndef HTTP_BACKEND_SERVER_ECHOSERVER_H
#define HTTP_BACKEND_SERVER_ECHOSERVER_H
#include <qtconfigmacros.h>
#include <QObject>
#include <QList>

#include "MfamDataSample.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class EchoServer : public QObject
{
    Q_OBJECT
public:
    explicit EchoServer(quint16 port, bool debug = false,
        QObject *parent = nullptr,
        QVector<QJsonObject*> *jsonDataSamples = nullptr);
    ~EchoServer();

    Q_SIGNALS:
        void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QVector<QJsonObject*> *jsonDataSamples;
    bool m_debug;
};

#endif // HTTP_BACKEND_SERVER_ECHOSERVER_H
