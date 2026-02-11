#include <QApplication>
#include <QLoggingCategory> // <--- AJOUTER CECI
#include "mainwindow.h"
#include "telemetrydata.h"
#include "mocktelemetrysource.h"
#include <QNetworkProxyFactory>

int main(int argc, char *argv[]) {
    // 1. Activer les logs détaillés pour le réseau et la localisation
    QLoggingCategory::setFilterRules(
        "qt.network.ssl.warning=true\n"
        "qt.location.mapping.osm.debug=true\n"
        "qt.location.mapping.network.debug=true\n"
        "qt.network.access.debug=true" // Attention, ça va être très bavard !
        );

    // 2. Force le rendu logiciel (indispensable sur certains Linux)
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

    QApplication a(argc, argv);

    // 3. Configuration Proxy (Déjà fait, on garde)
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    TelemetryData telemetry;
    MockTelemetrySource mock(&telemetry);
    mock.start();

    MainWindow w(&telemetry);
    w.showFullScreen();
    return a.exec();
}
