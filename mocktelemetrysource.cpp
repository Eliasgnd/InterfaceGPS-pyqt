#include "mocktelemetrysource.h"
#include "telemetrydata.h"
#include <QtMath>
#include <QRandomGenerator>
#include <QDebug>

MockTelemetrySource::MockTelemetrySource(TelemetryData* data, QObject* parent)
    : QObject(parent), m_data(data)
{
    // --- 1. Définition du trajet : IUT -> Centre Ville (Via Av. Anatole France) ---
    // J'ai relevé ces points sur une carte pour suivre la route
    m_route << QGeoCoordinate(48.2715, 4.0645)  // Départ: IUT (Parking)
            << QGeoCoordinate(48.2718, 4.0668)  // Sortie rue de Québec
            << QGeoCoordinate(48.2732, 4.0691)  // Carrefour Av. des Lombards
            << QGeoCoordinate(48.2755, 4.0695)  // Remontée Av. Lombards
            << QGeoCoordinate(48.2785, 4.0702)  // Rond-point
            << QGeoCoordinate(48.2818, 4.0712)  // Av. Anatole France (début)
            << QGeoCoordinate(48.2855, 4.0722)  // Av. Anatole France (milieu)
            << QGeoCoordinate(48.2890, 4.0735)  // Carrefour de l'Europe
            << QGeoCoordinate(48.2925, 4.0745)  // Bd du 14 Juillet
            << QGeoCoordinate(48.2960, 4.0750)  // Approche Centre
            << QGeoCoordinate(48.2975, 4.0742); // Arrivée: Place de l'Hôtel de Ville

    // Initialisation au point de départ
    if (!m_route.isEmpty()) {
        m_currentPos = m_route.first();
        m_currentWaypointIndex = 1; // On vise le 2ème point direct
    }

    // Timer à 100ms (10 images par seconde) pour la fluidité
    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &MockTelemetrySource::tick);
}

void MockTelemetrySource::start(){ m_timer.start(); }
void MockTelemetrySource::stop(){ m_timer.stop(); }

void MockTelemetrySource::tick(){
    if(!m_data || m_route.isEmpty()) return;

    // --- 2. Gestion de la Vitesse (Accélération / Freinage) ---
    // On ralentit si on tourne fort, sinon on accélère vers 50 km/h
    if (m_currentSpeed < m_speedTarget) m_currentSpeed += 1.5;
    if (m_currentSpeed > m_speedTarget) m_currentSpeed -= 1.5;

    // --- 3. Déplacement ---
    QGeoCoordinate target = m_route[m_currentWaypointIndex];

    // Calcul de la distance et de l'angle vers le prochain point
    double distance = m_currentPos.distanceTo(target); // en mètres
    double azimuth = m_currentPos.azimuthTo(target);   // en degrés (0 = Nord)

    // Distance à parcourir en 0.1s (vitesse en m/s = kmh / 3.6)
    double stepDistance = (m_currentSpeed / 3.6) * 0.1;

    if (distance <= stepDistance) {
        // On est arrivé au point de passage ! On passe au suivant
        m_currentPos = target;
        m_currentWaypointIndex++;

        // Si on est à la fin, on s'arrête ou on boucle
        if (m_currentWaypointIndex >= m_route.size()) {
            m_currentWaypointIndex = 0; // Boucle (retour départ)
            m_currentPos = m_route.first();
            m_currentSpeed = 0; // On marque un stop virtuel
        }
    } else {
        // On avance vers la cible
        // QGeoCoordinate::atDistanceAndAzimuth calcule la nouvelle lat/lon
        m_currentPos = m_currentPos.atDistanceAndAzimuth(stepDistance, azimuth);
    }

    // --- 4. Mise à jour des données de l'interface ---
    m_data->setLat(m_currentPos.latitude());
    m_data->setLon(m_currentPos.longitude());
    m_data->setSpeedKmh(m_currentSpeed);

    // IMPORTANT: On envoie le CAP (Heading) pour tourner la flèche bleue !
    // Si tu n'as pas ajouté setHeading dans TelemetryData, fais-le,
    // ou utilise une propriété existante.
    // Pour l'instant, je suppose que tu l'as ajouté ou que tu utilises "gpsTrack" s'il existe.
    // Sinon, tu peux utiliser un signal custom.
    // m_data->setHeading(azimuth);

    // --- 5. Simulation Batterie et Alertes (inchangé) ---
    if(QRandomGenerator::global()->bounded(100)==0) m_batt = qMax(0, m_batt-1);
    m_data->setBatteryPercent(m_batt);
    m_data->setGpsOk(true);
}
