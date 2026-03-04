#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <qwebsocket.h>
#include <qwebsocketserver.h>

#include "MfamClient.h"
#include "OneSecondWorker.h"
#include "Settings.h"
#include "echoserver.h"


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    Settings settings;
    QVector<MfamDataSample*> dataSamples;
    QVector<QJsonObject> jsonDataSamples;

    // QThread *oneSecondWorkThread = new QThread();
    // OneSecondWorker *oneSecondWorker = new OneSecondWorker(nullptr, &dataSamples);
    // oneSecondWorker->moveToThread(oneSecondWorkThread);
    // QObject::connect(oneSecondWorkThread, &QThread::started, oneSecondWorker, &OneSecondWorker::work);
    // QObject::connect(oneSecondWorker, &OneSecondWorker::finished, oneSecondWorker, &QObject::deleteLater);
    // QObject::connect(oneSecondWorker, &OneSecondWorker::finished, oneSecondWorkThread, &QThread::quit);
    // QObject::connect(oneSecondWorkThread, &QThread::finished, oneSecondWorker, &QObject::deleteLater);
    // QObject::connect(oneSecondWorkThread, &QThread::finished, oneSecondWorkThread, &QObject::deleteLater);
    // QObject::connect(oneSecondWorkThread, &QThread::finished, &a, &QCoreApplication::quit);
    // oneSecondWorkThread->start();

    QThread *mfamThread = new QThread();
    MfamClient *mfamClient = new MfamClient(nullptr, &dataSamples, &jsonDataSamples);
    mfamClient->moveToThread(mfamThread);
    QObject::connect(mfamThread, &QThread::finished, mfamClient, &QObject::deleteLater);
    QObject::connect(mfamThread, &QThread::finished, mfamThread, &QObject::deleteLater);
    QObject::connect(mfamThread, &QThread::finished, &a, &QCoreApplication::quit);

    qDebug() << "Starting MFAM Client thread ID:" << mfamThread->currentThreadId();
    mfamThread->start();

    QMetaObject::invokeMethod(mfamClient, [mfamClient, &settings]()
    {
        mfamClient->connectToMFAM(settings.getMfamIpAddress(), settings.getMfamPort());
    }, Qt::QueuedConnection);

    // EchoServer *server = new EchoServer(settings.getHttpPort(), true);
    // QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    // 1. Create the server
    QWebSocketServer *server = new QWebSocketServer(
        QStringLiteral("Periodic Server"),
        QWebSocketServer::NonSecureMode,
        &a);

    if (server->listen(QHostAddress::Any, 8080)) {
        qDebug() << "Server listening on port 8080";
    } else {
        qFatal("Failed to start server");
    }

    // 2. Store connected clients
    QList<QWebSocket *> clients;

    QObject::connect(server, &QWebSocketServer::newConnection, [&]() {
        QWebSocket *socket = server->nextPendingConnection();
        clients << socket;
        qDebug() << "Client connected";

        QObject::connect(socket, &QWebSocket::disconnected, [&, socket]() {
            clients.removeAll(socket);
            socket->deleteLater();
            qDebug() << "Client disconnected";
        });
    });

    // 3. Setup Timer to emit data every 1 second
    QTimer *timer = new QTimer(&a);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        QString timeMsg = QDateTime::currentDateTime().toString();
        for (QWebSocket *client : clients) {
            client->sendTextMessage("Time: " + timeMsg);
            qDebug() << "Size of jsonDataSamples:" << jsonDataSamples.size();
        }
    });
    timer->start(1000); // 1000ms = 1 second

    // delete mfamThread;
    // delete mfamClient;
    // delete server;

    return a.exec();
}
