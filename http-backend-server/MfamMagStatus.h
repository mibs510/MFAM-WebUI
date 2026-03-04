//
// Created by Connor on 2/10/2026.
//

#ifndef HTTP_BACKEND_SERVER_MAGSTATUS_H
#define HTTP_BACKEND_SERVER_MAGSTATUS_H
#include <QJsonObject>
#include <QByteArray>

#include "MfamMagStartupDiagnosticState.h"
#include "MfamSensorFaultId.h"

class MfamMagStatus
{
    public:
    MfamMagStartupDiagnosticState startupDiagnosticStatus;
    MfamSensorFaultId sensorFaultId;
    bool lowHeLowNoiseMode = false;
    bool regularNoDzMode = false;
    bool deadZoneIndicator = false;

    MfamMagStatus(const QByteArray& magStatus)
    {
        uint16_t magStatusWord = 0;
        memcpy(&magStatusWord, magStatus.data(), sizeof(magStatusWord));
        startupDiagnosticStatus =
            static_cast<MfamMagStartupDiagnosticState>(static_cast<uint8_t>((magStatusWord & 0xE000) >> 13));
        // qDebug() << "Startup Diagnostic Status: " << startupDiagnosticStatus;
        sensorFaultId = static_cast<MfamSensorFaultId>(static_cast<uint8_t>((magStatusWord & 0x3C0) >> 6));
        // qDebug() << "Sensor Fault ID: " << sensorFaultId;
        lowHeLowNoiseMode = magStatusWord & 0x20;
        // qDebug() << "Low He Noise Mode: " << lowHeLowNoiseMode;
        regularNoDzMode = magStatusWord & 0x10;
        // qDebug() << "Regular No Dead Zone Mode: " << regularNoDzMode;
        deadZoneIndicator = magStatusWord & 0x1;
        // qDebug() << "Dead Zone Indicator: " << deadZoneIndicator;
    }

    QJsonObject toJson() const
    {
        QJsonObject json;
        json["startupDiagnosticStatus"] = toString(startupDiagnosticStatus);
        json["sensorFaultId"] = toString(sensorFaultId);
        json["lowHeLowNoiseMode"] = lowHeLowNoiseMode;
        json["regularNoDzMode"] = regularNoDzMode;
        json["deadZoneIndicator"] = deadZoneIndicator;
        return json;
    }
};

#endif //HTTP_BACKEND_SERVER_MAGSTATUS_H