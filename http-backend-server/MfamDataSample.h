//
// Created by Connor on 2/11/2026.
//

#ifndef HTTP_BACKEND_SERVER_MFAMDATASAMPLE_H
#define HTTP_BACKEND_SERVER_MFAMDATASAMPLE_H

#include <bitset>
#include <qbytearray.h>
#include <qjsonobject.h>

#include "MfamFiducial.h"
#include "MfamMagStatus.h"
#include "MfamSystemStatus.h"

/* Ethernet Packet Structure */
#define ONE_SECOND_OF_DATA_SIZE 34500
#define MFAM_DATA_BLOCK_COUNT 25
#define MFAM_DATA_BLOCK_SIZE 1380
#define MFAM_HEADER_OFFSET 0
#define MFAM_HEADER_SIZE 15
#define MFAM_FIRST_DATA_SAMPLE_OFFSET MFAM_HEADER_SIZE + 1
#define MFAM_LAST_DATA_SAMPLE_OFFSET MFAM_FIRST_DATA_SAMPLE_OFFSET + (MFAM_DATA_SAMPLE_COUNT * MFAM_DATA_SAMPLE_SIZE)
#define MFAM_DATA_SAMPLE_COUNT 40
#define MFAM_DATA_SAMPLE_SIZE 32
#define MFAM_DATA_BLOCK_BLANK_SIZE 84

/* Data Sample Structure */
#define MFAM_FID_OFFSET 0
#define MFAM_FID_SIZE 2

#define MFAM_SYSTEM_STATUS_OFFSET 2
#define MFAM_SYSTEM_STATUS_SIZE 2

#define MFAM_MAG_1_OFFSET 4
#define MFAM_MAG_1_SIZE 4

#define MFAM_MAG_1_STATUS_OFFSET 8
#define MFAM_MAG_1_STATUS_SIZE 2

#define MFAM_MAG_2_STATUS_OFFSET 10
#define MFAM_MAG_2_STATUS_SIZE 2

#define MFAM_MAG_2_OFFSET 12
#define MFAM_MAG_2_SIZE 4

#define MFAM_AUX_X_OFFSET 16
#define MFAM_AUX_X_SIZE 2

#define MFAM_AUX_Y_OFFSET 18
#define MFAM_AUX_Y_SIZE 2

#define MFAM_AUX_Z_OFFSET 20
#define MFAM_AUX_Z_SIZE 2

#define MFAM_AUX_T_OFFSET 22
#define MFAM_AUX_T_SIZE 2

#define MFAM_ADC_CHAN_0_OFFSET 24
#define MFAM_ADC_CHAN_0_SIZE 2

#define MFAM_ADC_CHAN_1_OFFSET 26
#define MFAM_ADC_CHAN_1_SIZE 2

#define MFAM_ADC_CHAN_2_OFFSET 28
#define MFAM_ADC_CHAN_2_SIZE 2

#define MFAM_ADC_CHAN_3_OFFSET 30
#define MFAM_ADC_CHAN_3_SIZE 2

/* Masks & Right Shifts */
/* MfamFiducial */
#define MFAM_MAG_2_DATA_VALID_MASK 0x8000
#define MFAM_MAG_1_DATA_VALID_MASK 0x4000
#define MFAM_AUX_FIELD_ID_MASK 0x3800
#define MFAM_AUX_FIELD_ID_SHIFT 11
#define MFAM_COUNTER_MASK 0x07FF

class MfamDataSample : public QObject
{
    Q_OBJECT
public:
    MfamFiducial fidicuial;
    MfamSystemStatus systemStatus;
    double magnetometerOne = 0;
    MfamMagStatus magOneStatus;
    MfamMagStatus magTwoStatus;
    double magnetometerTwo = 0;
    QString auxX = "";
    QString auxY = "";
    QString auxZ = "";
    QString auxT = "";
    uint16_t adcChan0 = 0; /* Ignore */
    uint16_t adcChan1 = 0; /* Ignore */
    uint16_t adcChan2 = 0;
    uint16_t adcChan3 = 0;

    MfamDataSample(const QByteArray& dataSample) :
    fidicuial(MfamFiducial(dataSample.mid(MFAM_FID_OFFSET, MFAM_FID_SIZE))),
    systemStatus(MfamSystemStatus(dataSample.mid(MFAM_SYSTEM_STATUS_OFFSET, MFAM_SYSTEM_STATUS_SIZE))),
    magOneStatus(MfamMagStatus(dataSample.mid(MFAM_MAG_1_STATUS_OFFSET, MFAM_MAG_1_STATUS_SIZE))),
    magTwoStatus(MfamMagStatus(dataSample.mid(MFAM_MAG_2_STATUS_OFFSET, MFAM_MAG_2_STATUS_SIZE)))
    {
        uint32_t magOne = 0;
        memcpy(&magOne, dataSample.mid(MFAM_MAG_1_OFFSET, MFAM_MAG_1_SIZE), sizeof(magOne));
        magnetometerOne = magOne * 50E-6;
        // qDebug() << "Magnetometer One: " << QString::number(magnetometerOne, 'f', 4);
        uint32_t magTwo = 0;
        memcpy(&magTwo, dataSample.mid(MFAM_MAG_2_OFFSET, MFAM_MAG_2_SIZE), sizeof(magTwo));
        magnetometerTwo = magTwo * 50E-6;
        // qDebug() << "Magnetometer Two: " << QString::number(magnetometerTwo, 'f', 4);
        int16_t auxChan0 = 0;
        memcpy(&auxChan0, dataSample.mid(MFAM_AUX_X_OFFSET, MFAM_AUX_X_SIZE), sizeof(auxChan0));
        int16_t auxChan1 = 0;
        memcpy(&auxChan1, dataSample.mid(MFAM_AUX_Y_OFFSET, MFAM_AUX_Y_SIZE), sizeof(auxChan1));
        int16_t auxChan2 = 0;
        memcpy(&auxChan2, dataSample.mid(MFAM_AUX_Z_OFFSET, MFAM_AUX_Z_SIZE), sizeof(auxChan2));
        int16_t auxChan3 = 0;
        memcpy(&auxChan3, dataSample.mid(MFAM_AUX_T_OFFSET, MFAM_AUX_T_SIZE), sizeof(auxChan3));
        if (fidicuial.auxFieldId == MfamAuxFieldId::compass)
        {
            auxX = QString::number(auxChan0 * 75E-9, 'f', 4) + " uT";
            // qDebug() << "Aux X:" << auxX;
            auxY = QString::number(auxChan1 * 75E-9, 'f', 4) + " uT";
            // qDebug() << "Aux Y:" << auxY;
            auxZ = QString::number(auxChan2 * 75E-9, 'f', 4) + " uT";
            // qDebug() << "Aux Z:" << auxZ;
        } else if (fidicuial.auxFieldId == MfamAuxFieldId::gyro)
        {
            auxX = QString::number(auxChan0 / 16.384, 'f', 4) + " deg/s";
            auxY = QString::number(auxChan1 / 16.384, 'f', 4) + " deg/s";
            auxZ = QString::number(auxChan2 / 16.384, 'f', 4) + " deg/s";
            auxT = QString::number(auxChan3 / 16.384, 'f', 4) + " deg/s";
        } else if (fidicuial.auxFieldId == MfamAuxFieldId::accelerometer)
        {
            auxX = QString::number(auxChan0 / 16384.0, 'f', 4) + " G";
            auxY = QString::number(auxChan1 / 16384.0, 'f', 4) + " G";
            auxZ = QString::number(auxChan2 / 16384.0, 'f', 4) + " G";
            auxT = QString::number(auxChan3 / 16384.0, 'f', 4) + " G";
        } else if (fidicuial.auxFieldId == MfamAuxFieldId::aux)
        {
            auxX = QString::number(auxChan0 * 503.975 / (4096 - 273.15), 'f', 4) + "C";
            auxY = QString::number((4096 - auxChan1 - 1720) / 8.2 - 35, 'f', 4) + "C";
            auxZ = QString::number(auxChan2 * 34.1325 / 4096, 'f', 4) + "V";
            auxT = QString::number(1 / auxChan3, 'f', 4) + "h";
        } else if (fidicuial.auxFieldId == MfamAuxFieldId::serialNumber)
        {
            if (auxChan3 >> 8 < 10)
            {
                auxX = "0" + QString::number(static_cast<uint8_t>(auxChan3 >> 8));
            } else
            {
                auxX = QString::number(static_cast<uint8_t>(auxChan3 >> 8));
            }
            if ((auxChan3 & 0xFF) < 10)
            {
                auxX = auxX + "0" +  QString::number(static_cast<uint8_t>(auxChan3 & 0xFF));
            } else
            {
                auxX = auxX + QString::number(static_cast<uint8_t>(auxChan3 & 0xFF));
            }
            auxY = QChar(auxChan2 >> 8);
            if ((auxChan2 & 0xFF) < 10)
            {
                auxY = auxY + "0" +  QString::number(static_cast<uint8_t>(auxChan2 & 0xFF));
            } else
            {
                auxY = auxY + QString::number(static_cast<uint8_t>(auxChan2 & 0xFF));
            }
            if (auxChan1 >> 8 < 10)
            {
                auxZ = "0" + QString::number(static_cast<uint8_t>(auxChan1 >> 8));
            } else
            {
                auxZ = QString::number(static_cast<uint8_t>(auxChan1 >> 8));
            }
            if ((auxChan1 & 0xFF) < 10)
            {
                auxZ = auxZ + "0" +  QString::number(static_cast<uint8_t>(auxChan1 & 0xFF));
            } else
            {
                auxZ = auxZ + QString::number(static_cast<uint8_t>(auxChan1 & 0xFF));
            }
            if (auxChan0 >> 8 < 10)
            {
                auxT = "0" + QString::number(static_cast<uint8_t>(auxChan0 >> 8));
            } else
            {
                auxT = QString::number(static_cast<uint8_t>(auxChan0 >> 8));
            }
            if ((auxChan0 & 0xFF) < 10)
            {
                auxT = auxT + "0" + QString::number(static_cast<uint8_t>(auxChan0 & 0xFF));
            } else
            {
                auxT = auxT + QString::number(static_cast<uint8_t>(auxChan0 & 0xFF));

            }
            // qDebug() << "Serial Number: " + auxX + auxY + auxZ + auxT;
        }

        memcpy(&adcChan2,
            dataSample.mid(MFAM_ADC_CHAN_2_OFFSET, MFAM_ADC_CHAN_2_SIZE),
            sizeof(adcChan2));
        // qDebug() << "ADC Chan 2: " << adcChan2;
        memcpy(&adcChan3,
            dataSample.mid(MFAM_ADC_CHAN_3_OFFSET, MFAM_ADC_CHAN_3_SIZE),
            sizeof(adcChan3));
        // qDebug() << "ADC Chan 3: " << adcChan3;
    }

    QJsonObject toJson() const
    {
        QJsonObject json;
        json["fidicuial"] = fidicuial.toJson();
        json["systemStatus"] = systemStatus.toJson();
        json["magnetometerOne"] = magnetometerOne;
        json["magOneStatus"] = magOneStatus.toJson();
        json["magTwoStatus"] = magTwoStatus.toJson();
        json["magnetometerTwo"] = magnetometerTwo;
        json["auxX"] = auxX;
        json["auxY"] = auxY;
        json["auxZ"] = auxZ;
        json["auxT"] = auxT;
        json["adcChan2"] = adcChan2;
        json["adcChan3"] = adcChan3;

        return json;
    }

    QJsonObject magnetometersToJson() const
    {
        QJsonObject json;
        json["magnetometerOne"] = magnetometerOne;
        json["magnetometerTwo"] = magnetometerTwo;
        return json;
    }
};

#endif // HTTP_BACKEND_SERVER_MFAMDATASAMPLE_H
