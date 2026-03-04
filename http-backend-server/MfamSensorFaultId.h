//
// Created by Connor on 2/10/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMSENSORFAULTIDS_H
#define HTTP_BACKEND_SERVER_MFAMSENSORFAULTIDS_H

enum class MfamSensorFaultId
{
    none = 0,
    probeLaserUnlocked = 10,
    pumpLaserUnlocked = 11

};

inline QString toString(const MfamSensorFaultId& sensorFaultId)
{
    switch (sensorFaultId)
    {
    case MfamSensorFaultId::none:
        return "No Fault";
    case MfamSensorFaultId::probeLaserUnlocked:
        return "Probe Laser Unlocked";
    case MfamSensorFaultId::pumpLaserUnlocked:
        return "Pump Laser Unlocked";
    default:
        return "Unknown";
    }
}

inline QDebug operator<<(QDebug debug, const MfamSensorFaultId sensorFaultId)
{
    QDebugStateSaver saver(debug);
    switch (sensorFaultId)
    {
    case MfamSensorFaultId::none:
        return debug << "No Diagnostics";
    case MfamSensorFaultId::probeLaserUnlocked:
        return debug << "Probe Laser Unlocked";
    case MfamSensorFaultId::pumpLaserUnlocked:
        return debug << "Pump Laser Unlocked";
    default:
        return debug << static_cast<int>(sensorFaultId);
    }
    return debug;
}

#endif //HTTP_BACKEND_SERVER_MFAMSENSORFAULTIDS_H