#pragma once
#include <QObject>
#include <QSerialPort>
#include <QGeoCoordinate>

class TelemetryData;

class GpsTelemetrySource : public QObject {
    Q_OBJECT
public:
    explicit GpsTelemetrySource(TelemetryData* data, QObject* parent = nullptr);
    ~GpsTelemetrySource();

    void start(const QString& portName = "/dev/serial0");
    void stop();

private slots:
    void onReadyRead();

private:
    void parseNmeaLine(const QByteArray& line);
    double convertNmeaToDecimal(const QString& nmeaPos, const QString& quadrant);

    TelemetryData* m_data = nullptr;
    QSerialPort* m_serial = nullptr;
};
