//
// Created by Connor on 2/8/2026.
//

#include "MfamClient.h"
#include "MfamDataSample.h"

MfamClient::MfamClient(QObject* parent,
    QVector<MfamDataSample*> *dataSamples,
    QVector<QJsonObject> *jsonDataSamples) :
QObject(parent), port(0), dataSamples(dataSamples), jsonDataSamples(jsonDataSamples)
{
    // timer->setSingleShot(true);
    // connect(timer, &QTimer::timeout, this, &MfamClient::disconnectFromMFAM);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &MfamClient::onConnect);
    connect(socket, &QTcpSocket::readyRead, this, &MfamClient::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &MfamClient::onErrorOccurred);
}

/*
MfamClient::~MfamClient()
{
    disconnectFromMFAM();
    delete socket;
    qDeleteAll(dataSamples);
}
*/

void MfamClient::connectToMFAM(QHostAddress mfamIpAddress, quint16 mfamPort)
{
    socket->connectToHost(mfamIpAddress, mfamPort);
    this->ipAddress = std::move(mfamIpAddress);
    this->port = mfamPort;
}

void MfamClient::onConnect() const
{
    // timer->start(1000);
    qDebug() << "Connected to MFAM" << ipAddress.toString() << ":" << port;
}

void MfamClient::onReadyRead()
{
    /* For debugging purposes. Stop after 1000 samples/1 second */
    if (dataBlocks >= MFAM_DATA_BLOCK_COUNT)
    {
        qDebug() << "MFAM data block limit reached(" << dataBlocks << "), disconnecting";
        dataSamples->clear();
        dataBlocks = 0;
        disconnectFromMFAM();
        return;
    }
    /* Are the bytes available to read less than one whole data block? */
    if (socket->bytesAvailable() < MFAM_DATA_BLOCK_SIZE)
    {
        /* If the buffer is not full, read more data */
        if (packetBuffer.size() < MFAM_DATA_BLOCK_SIZE)
            packetBuffer += socket->readAll();
        /* Did readAll() fill the buffer? */
        if (packetBuffer.size() == MFAM_DATA_BLOCK_SIZE)
        {
            /* Process the data block */
            processDataBlock();
            /* Clear buffer */
            packetBuffer.clear();
            dataBlocks++;
        }
        /* Are the bytes available to read exactly one whole data block? */
    } else if (socket->bytesAvailable() == MFAM_DATA_BLOCK_SIZE)
    {
        /* Read the data block */
        packetBuffer = socket->readAll();
        /* Process the data block */
        processDataBlock();
        /* Clear buffer */
        packetBuffer.clear();
        dataBlocks++;
    }
}

void MfamClient::processDataBlock()
{

    // qDebug() << "Header:" << packetBuffer.mid(0, 15);
    for (int i = MFAM_FIRST_DATA_SAMPLE_OFFSET; i < MFAM_LAST_DATA_SAMPLE_OFFSET; i += MFAM_DATA_SAMPLE_SIZE)
    {
        // qDebug() << "Data Sample Offset:" << i;
        // qDebug() << "Data Sample Offset End:" << i + MFAM_DATA_SAMPLE_SIZE - 1;
        MfamDataSample* sample = new MfamDataSample(packetBuffer.mid(i, i + MFAM_DATA_SAMPLE_SIZE - 1));
        jsonDataSamples->push_back(sample->magnetometersToJson());
        delete sample;
    }
}

void MfamClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error: " << error;
}

void MfamClient::disconnectFromMFAM() const
{
    socket->disconnectFromHost();
    // parent()->thread()->quit();
}
