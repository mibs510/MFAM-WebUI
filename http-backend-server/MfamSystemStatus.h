//
// Created by Connor on 2/10/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMSYSTEMSTATUS_H
#define HTTP_BACKEND_SERVER_MFAMSYSTEMSTATUS_H
#include <QJsonObject>
#include <QByteArray>
#include "MfamRunningMode.h"
#include "MfamSystemFaultIds.h"

class MfamSystemStatus
{
public:
    bool ppsLocked = false;
    bool ppsAvailable = false;
    bool tenMhzAvailable = false;
    bool tenMhzLocked = false;
    MfamSystemFaultIds systemFaultId;
    bool nonCriticalFault = false;
    MfamRunningMode runningMode;
    bool criticalFault = false;

    MfamSystemStatus(const QByteArray& systemStatus)
    {
        uint16_t sysStatus = 0;
        memcpy(&sysStatus, systemStatus.data(), sizeof(sysStatus));
        ppsLocked = sysStatus & 0x800;
        // qDebug() << "PPS Locked: " << ppsLocked;
        ppsAvailable = sysStatus & 0x400;
        // qDebug() << "PPS Available: " << ppsAvailable;
        tenMhzAvailable = sysStatus & 0x200;
        // qDebug() << "10 MHz Available: " << tenMhzAvailable;
        tenMhzLocked = sysStatus & 0x100;
        // qDebug() << "10 MHz Locked: " << tenMhzLocked;
        systemFaultId = static_cast<MfamSystemFaultIds>(static_cast<uint8_t>((sysStatus & 0xF00) >> 8));
        // qDebug() << "System Fault ID: " << systemFaultId;
        nonCriticalFault = sysStatus & 0x80;
        // qDebug() << "Non-Critical Fault: " << nonCriticalFault;
        runningMode = static_cast<MfamRunningMode>(static_cast<uint8_t>((sysStatus & 0x1E) >> 1));
        // qDebug() << "Running Mode: " << runningMode;
        criticalFault = sysStatus & 0x1;
        // qDebug() << "Critical Fault: " << criticalFault;
    }

    QJsonObject toJson() const
    {
        QJsonObject json;
        json["ppsLocked"] = ppsLocked;
        json["ppsAvailable"] = ppsAvailable;
        json["tenMhzAvailable"] = tenMhzAvailable;
        json["tenMhzLocked"] = tenMhzLocked;
        json["systemFaultId"] = toString(systemFaultId);
        json["nonCriticalFault"] = nonCriticalFault;
        json["runningMode"] = toString(runningMode);
        json["criticalFault"] = criticalFault;
        return json;
    }
};

#endif //HTTP_BACKEND_SERVER_MFAMSYSTEMSTATUS_H