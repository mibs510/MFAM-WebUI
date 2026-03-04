//
// Created by Connor on 2/8/2026.
//

#include "Settings.h"

Settings::Settings()
{
    load();
    save();
}

void Settings::load()
{
    mfamIpAddress = QHostAddress(qSettings.value("MFAM_IP_ADDRESS", "192.168.0.2").toString());
    mfamPort = qSettings.value("MFAM_PORT", 1000).toInt();
    httpPort = qSettings.value("HTTP_PORT", 8080).toInt();
}

void Settings::save()
{
    qSettings.setValue("MFAM_IP_ADDRESS", mfamIpAddress.toString());
    qSettings.setValue("MFAM_PORT", mfamPort);
    qSettings.setValue("HTTP_PORT", httpPort);
    qSettings.sync();
}