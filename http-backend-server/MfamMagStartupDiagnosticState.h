//
// Created by Connor on 2/14/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMMAGSTARTUPDIAGNOSTICSTATE_H
#define HTTP_BACKEND_SERVER_MFAMMAGSTARTUPDIAGNOSTICSTATE_H

enum class MfamMagStartupDiagnosticState
{
    noDiagnostics = 0,
    cellHeating = 1,
    probeLaserLocking = 2,
    pumpLaserLocking = 3,
    finalizeLaserLockingParameters = 4,
    startupComplete = 5
};

inline QString toString(const MfamMagStartupDiagnosticState& startupDiagnosticState)
{
    switch (startupDiagnosticState)
    {
    case MfamMagStartupDiagnosticState::noDiagnostics:
        return "No Diagnostics";
    case MfamMagStartupDiagnosticState::cellHeating:
        return "Cell Heating";
    case MfamMagStartupDiagnosticState::probeLaserLocking:
        return "Probe Laser Locking";
    case MfamMagStartupDiagnosticState::pumpLaserLocking:
        return "Pump Laser Locking";
    case MfamMagStartupDiagnosticState::finalizeLaserLockingParameters:
        return "Finalize Laser Locking Parameters";
    case MfamMagStartupDiagnosticState::startupComplete:
        return "Startup Complete";
    }
    return "Unknown";
}

inline QDebug operator<<(QDebug debug, const MfamMagStartupDiagnosticState& startupDiagnosticState)
{
    QDebugStateSaver saver(debug);
    switch (startupDiagnosticState)
    {
    case MfamMagStartupDiagnosticState::noDiagnostics:
        return debug << "No Diagnostics";
    case MfamMagStartupDiagnosticState::cellHeating:
        return debug << "Cell Heating";
    case MfamMagStartupDiagnosticState::probeLaserLocking:
        return debug << "Probe Laser Locking";
    case MfamMagStartupDiagnosticState::pumpLaserLocking:
        return debug << "Pump Laser Locking";
    case MfamMagStartupDiagnosticState::finalizeLaserLockingParameters:
        return debug << "Finalize Laser Locking Parameters";
    case MfamMagStartupDiagnosticState::startupComplete:
        return debug << "Startup Complete";
    default:
        return debug << static_cast<int>(startupDiagnosticState);
    }
    return debug;
}

#endif // HTTP_BACKEND_SERVER_MFAMMAGSTARTUPDIAGNOSTICSTATE_H
