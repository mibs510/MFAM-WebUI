//
// Created by Connor on 2/13/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMRUNNINGMODE_H
#define HTTP_BACKEND_SERVER_MFAMRUNNINGMODE_H

enum class MfamRunningMode
{
    builtInTest = 15,
    calibration = 7,
    magnetometer = 2,
    startup = 1,
    hibernate = 0,
};

inline QString toString(const MfamRunningMode& runningMode)
{
    switch (runningMode)
    {
    case MfamRunningMode::builtInTest:
        return "Built In Test";
    case MfamRunningMode::calibration:
        return "Calibration";
    case MfamRunningMode::magnetometer:
        return "Magnetometer";
    case MfamRunningMode::startup:
        return "Startup";
    case MfamRunningMode::hibernate:
        break;
    }
    return "Unknown";
}

inline QDebug operator<<(QDebug debug, const MfamRunningMode& runningMode)
{
    QDebugStateSaver saver(debug);
    switch (runningMode)
    {
    case MfamRunningMode::builtInTest:
        return debug << "Built In Test";
    case MfamRunningMode::calibration:
        return debug << "Calibration";
    case MfamRunningMode::magnetometer:
        return debug << "Magnetometer";
    case MfamRunningMode::startup:
        return debug << "Startup";
    case MfamRunningMode::hibernate:
        return debug << "Hibernate";
    default:
        return debug << static_cast<int>(runningMode);
    }
    return debug;
}

#endif // HTTP_BACKEND_SERVER_MFAMRUNNINGMODE_H
