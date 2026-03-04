//
// Created by Connor on 2/8/2026.
//

#ifndef HTTP_BACKEND_SERVER_SETTINGS_H
#define HTTP_BACKEND_SERVER_SETTINGS_H
#include <QSettings>
#include <QHostAddress>

class Settings
{
    public:
        Settings();
        void save();
        void load();
        [[nodiscard]] QHostAddress getMfamIpAddress() const
        {
            return mfamIpAddress;
        }

        [[nodiscard]] quint16 getMfamPort() const
        {
            return mfamPort;
        }

        [[nodiscard]] quint16 getHttpPort() const
        {
            return httpPort;
        }
    private:
        QSettings qSettings = QSettings("config.ini", QSettings::IniFormat);
        QHostAddress mfamIpAddress;
        quint16 mfamPort;
        quint16 httpPort;
};


#endif //HTTP_BACKEND_SERVER_SETTINGS_H