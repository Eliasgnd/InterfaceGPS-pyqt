#include "mocktelemetrysource.h"
#include "telemetrydata.h"
#include <QGeoCoordinate>
#include <QDebug>

MockTelemetrySource::MockTelemetrySource(TelemetryData* data, QObject* parent)
    : QObject(parent), m_data(data)
{
    // On vide l'ancienne liste
    m_routePoints.clear();

    // --- TON TRACÉ RÉEL (Converti en Lat, Lon) ---
    // C'est une boucle autour de l'IUT/Technopole
    m_routePoints << QGeoCoordinate(48.269593, 4.079829)
                  << QGeoCoordinate(48.267314, 4.076437)
                  << QGeoCoordinate(48.267109, 4.076079)
                  << QGeoCoordinate(48.266902, 4.076267)
                  << QGeoCoordinate(48.265805, 4.078167)
                  << QGeoCoordinate(48.265751, 4.078509)
                  << QGeoCoordinate(48.265811, 4.078861)
                  << QGeoCoordinate(48.265971, 4.079096)
                  << QGeoCoordinate(48.266183, 4.079264)
                  << QGeoCoordinate(48.266268, 4.079301)
                  << QGeoCoordinate(48.266330, 4.079389)
                  << QGeoCoordinate(48.266389, 4.079547)
                  << QGeoCoordinate(48.266724, 4.079708)
                  << QGeoCoordinate(48.266847, 4.079909)
                  << QGeoCoordinate(48.266970, 4.080257)
                  << QGeoCoordinate(48.267120, 4.080900)
                  << QGeoCoordinate(48.267252, 4.081123)
                  << QGeoCoordinate(48.268008, 4.082088)
                  << QGeoCoordinate(48.268121, 4.082421)
                  << QGeoCoordinate(48.268126, 4.083243)
                  << QGeoCoordinate(48.268186, 4.083592)
                  << QGeoCoordinate(48.268387, 4.083990)
                  << QGeoCoordinate(48.268982, 4.084626)
                  << QGeoCoordinate(48.270582, 4.081287);
    // Le dernier point rejoint le premier automatiquement grâce à la logique de boucle

    m_currentIndex = 0;

    // Vitesse de la simulation : 1 seconde par point
    // Tu peux réduire à 500ms si tu veux que ça aille plus vite
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, this, &MockTelemetrySource::tick);
}

void MockTelemetrySource::start(){ m_timer.start(); }
void MockTelemetrySource::stop(){ m_timer.stop(); }

void MockTelemetrySource::tick(){
    if(!m_data || m_routePoints.isEmpty()) return;

    // 1. On récupère la position cible
    QGeoCoordinate target = m_routePoints[m_currentIndex];

    // 2. On met à jour la position dans le système
    m_data->setLat(target.latitude());
    m_data->setLon(target.longitude());

    // 3. Calcul intelligent du cap (Heading) pour que la voiture tourne
    // Si on n'est pas au dernier point, on regarde le suivant
    // Sinon, on regarde le premier point (pour boucler proprement)
    QGeoCoordinate nextPoint;
    if (m_currentIndex < m_routePoints.size() - 1) {
        nextPoint = m_routePoints[m_currentIndex + 1];
    } else {
        nextPoint = m_routePoints[0]; // Bouclage
    }

    // azimuthTo calcule l'angle exact entre deux coordonnées GPS
    m_data->setHeading(target.azimuthTo(nextPoint));

    // 4. On avance au point suivant
    m_currentIndex++;
    if (m_currentIndex >= m_routePoints.size()) {
        m_currentIndex = 0; // Retour au départ
    }

    // --- SIMULATION DES CAPTEURS ---
    m_data->setSpeedKmh(50.0); // On roule à 50 km/h
    m_data->setGpsOk(true);

    // Note : On ne définit plus 'setSpeedLimit' ici manuellement !
    // C'est ton fichier map.qml qui va le chercher sur internet grâce à la position.
}
