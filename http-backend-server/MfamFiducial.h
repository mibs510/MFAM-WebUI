//
// Created by Connor on 2/10/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMFID_H
#define HTTP_BACKEND_SERVER_MFAMFID_H
#include <QMetaEnum>
#include <QJsonObject>

#include "MfamAuxFieldId.h"

class MfamFiducial : public QObject
{
    public:
    bool magOneDataValid = false;
    bool magTwoDataValid = false;
    MfamAuxFieldId auxFieldId;
    uint16_t count = 0; /* 11 Bits wide (7FFh) */

    MfamFiducial(const QByteArray& fid)
    {
        uint16_t fiducial = 0;
        memcpy(&fiducial, fid.data(), sizeof(fiducial));
        magTwoDataValid = fiducial & 0x8000;
        // qDebug() << "Mag Two Data Valid: " << magTwoDataValid;
        magOneDataValid = fiducial & 0x4000;
        // qDebug() << "Mag One Data Valid: " << magOneDataValid;
        auxFieldId = static_cast<MfamAuxFieldId>(static_cast<uint8_t>((fiducial & 0x3800) >> 11));
        // qDebug() << "Aux Field ID:" << auxFieldId;
        count = fiducial & 0x7FF;
        // qDebug() << "Count:" << count;
    }

    QJsonObject toJson() const
    {
        QJsonObject json;
        json["magOneDataValid"] = magOneDataValid;
        json["magTwoDataValid"] = magTwoDataValid;
        json["auxFieldId"] = toString(auxFieldId);
        json["count"] = count;
        return json;
    }


};

#endif //HTTP_BACKEND_SERVER_MFAMFID_H