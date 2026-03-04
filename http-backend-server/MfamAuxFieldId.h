//
// Created by Connor on 2/10/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMAUXFIELDID_H
#define HTTP_BACKEND_SERVER_MFAMAUXFIELDID_H

enum class MfamAuxFieldId
{
    internalDiagnosticDataOne = 0,
    compass = 1,
    gyro = 2,
    internalDiagnosticDataTwo = 3,
    accelerometer = 4,
    internalDiagnosticDataThree = 5,
    aux = 6,
    serialNumber = 7,
};

inline QString toString(const MfamAuxFieldId& auxFieldId)
{
    switch (auxFieldId)
    {
        case MfamAuxFieldId::internalDiagnosticDataOne:
            return "Internal Diagnostic Data One";
        case MfamAuxFieldId::compass:
            return "Compass";
        case MfamAuxFieldId::gyro:
            return "Gyro";
        case MfamAuxFieldId::internalDiagnosticDataTwo:
            return "Internal Diagnostic Data Two";
        case MfamAuxFieldId::accelerometer:
            return "Accelerometer";
        case MfamAuxFieldId::internalDiagnosticDataThree:
            return "Internal Diagnostic Data Three";
        case MfamAuxFieldId::aux:
            return "Aux";
        case MfamAuxFieldId::serialNumber:
            return "Serial Number";
    }
        return "Unknown";
}


inline QDebug operator<<(QDebug debug, const MfamAuxFieldId& auxFieldId)
{
    QDebugStateSaver saver(debug);
    switch (auxFieldId)
    {
        case MfamAuxFieldId::internalDiagnosticDataOne:
            return debug << "Internal Diagnostic Data One";
        case MfamAuxFieldId::compass:
            return debug << "Compass";
        case MfamAuxFieldId::gyro:
            return debug << "Gyro";
        case MfamAuxFieldId::internalDiagnosticDataTwo:
            return debug << "Internal Diagnostic Data Two";
        case MfamAuxFieldId::accelerometer:
            return debug << "Accelerometer";
        case MfamAuxFieldId::internalDiagnosticDataThree:
            return debug << "Internal Diagnostic Data Three";
        case MfamAuxFieldId::aux:
            return debug << "Aux";
        case MfamAuxFieldId::serialNumber:
            return debug << "Serial Number";
        default:
            return debug << static_cast<int>(auxFieldId);
        }
    return debug;
}

#endif //HTTP_BACKEND_SERVER_MFAMAUXFIELDID_H