//
// Created by Connor on 2/10/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMSYSTEMFAULTIDS_H
#define HTTP_BACKEND_SERVER_MFAMSYSTEMFAULTIDS_H
#include <QString>

enum class MfamSystemFaultIds
{
    none = 0,
    compassFailed = 3,
    fpgaTemperature = 9,
};

inline QString toString(const MfamSystemFaultIds& systemFaultId)
{
    switch (systemFaultId)
    {
        case MfamSystemFaultIds::none:
            return "No Fault";
        case MfamSystemFaultIds::compassFailed:
            return "Compass Failed";
        case MfamSystemFaultIds::fpgaTemperature:
            return "FPGA Temperature";
    }
    return "Unknown";
}

inline QDebug operator<<(QDebug debug, const MfamSystemFaultIds& systemFaultId)
{
    QDebugStateSaver saver(debug);
    switch (systemFaultId)
    {
        case MfamSystemFaultIds::none:
            return debug << "No Fault";
        case MfamSystemFaultIds::compassFailed:
            return debug << "Compass Failed";
        case MfamSystemFaultIds::fpgaTemperature:
            return debug << "FPGA Temperature";
        default:
            return debug << static_cast<int>(systemFaultId);
    }
    return debug;
}

#endif //HTTP_BACKEND_SERVER_MFAMSYSTEMFAULTIDS_H