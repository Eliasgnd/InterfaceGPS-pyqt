#include "gpstelemetrysource.h"
#include "telemetrydata.h"
#include <QDebug>
#include <QRegularExpression>

GpsTelemetrySource::GpsTelemetrySource(TelemetryData* data, QObject* parent)
    : QObject(parent), m_data(data)
{
    m_serial = new QSerialPort(this);
    connect(m_serial, &QSerialPort::readyRead, this, &GpsTelemetrySource::onReadyRead);
}

GpsTelemetrySource::~GpsTelemetrySource() {
    stop();
}

void GpsTelemetrySource::start(const QString& portName) {
    if (m_serial->isOpen()) m_serial->close();

    m_serial->setPortName(portName);
    m_serial->setBaudRate(QSerialPort::Baud9600); // GY-NEO6MV2 defaut = 9600
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadOnly)) {
        qDebug() << "GPS connect� sur" << portName;
    } else {
        qCritical() << "Erreur ouverture GPS:" << m_serial->errorString();
        // Fallback: on met GPS LOST si pas de port
        if(m_data) m_data->setGpsOk(false);
    }
}

void GpsTelemetrySource::stop() {
    if (m_serial->isOpen()) m_serial->close();
}

void GpsTelemetrySource::onReadyRead() {
    while (m_serial->canReadLine()) {
        QByteArray line = m_serial->readLine().trimmed();
        parseNmeaLine(line);
    }
}

void GpsTelemetrySource::parseNmeaLine(const QByteArray& line) {
    // Exemple trame: $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
    // Champs: ID, Time, Status(A=OK), Lat, N/S, Lon, E/W, Speed(Knots), Heading, Date...

    if (!line.startsWith("$")) return;
    QList<QByteArray> tokens = line.split(',');

    // On cherche les trames RMC (Recommended Minimum)
    if (tokens.size() > 8 && (tokens[0].endsWith("RMC"))) {
        QString status = tokens[2];

        if (status == "A") { // A = Active (GPS Fix OK)
            m_data->setGpsOk(true);

            // 1. Latitude
            double lat = convertNmeaToDecimal(tokens[3], tokens[4]);
            // 2. Longitude
            double lon = convertNmeaToDecimal(tokens[5], tokens[6]);

            // 3. Vitesse (Noeuds -> Km/h)
            double speedKnots = tokens[7].toDouble();
            double speedKmh = speedKnots * 1.852;

            // 4. Cap (Heading/Track made good)
            double heading = tokens[8].toDouble();

            // Mise � jour de l'interface
            m_data->setLat(lat);
            m_data->setLon(lon);
            m_data->setSpeedKmh(speedKmh);
            m_data->setHeading(heading);

        } else {
            // V = Void (GPS Fix Lost / Recherche de satellites)
            m_data->setGpsOk(false);
        }
    }
}

// Convertit format NMEA "4807.038" (ddmm.mmm) en decimal "48.1173"
double GpsTelemetrySource::convertNmeaToDecimal(const QString& nmeaPos, const QString& quadrant) {
    if (nmeaPos.isEmpty()) return 0.0;

    double raw = nmeaPos.toDouble();
    int degrees = (int)(raw / 100);
    double minutes = raw - (degrees * 100);
    double decimal = degrees + (minutes / 60.0);

    if (quadrant == "S" || quadrant == "W") {
        decimal = -decimal;
    }
    return decimal;
}
