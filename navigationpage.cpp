#include "navigationpage.h"
#include "ui_navigationpage.h"
#include "telemetrydata.h"
#include <QQmlContext>
#include <QQuickItem>

NavigationPage::NavigationPage(QWidget* parent)
    : QWidget(parent), ui(new Ui::NavigationPage)
{
    ui->setupUi(this);

    // 1. Configuration de la vue Carte
    m_mapView = new QQuickWidget(this);
    m_mapView->setSource(QUrl("qrc:/map.qml"));
    m_mapView->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // 2. On cache le label placeholder et on ajoute la carte dans le layout existant
    ui->lblMap->setVisible(false);
    ui->mapLayout->addWidget(m_mapView);

    // 3. Connexion des boutons de zoom
    connect(ui->btnZoomIn, &QPushButton::clicked, this, [this](){
        m_currentZoom = qMin(20.0, m_currentZoom + 1.0);
        if(m_mapView->rootObject())
            m_mapView->rootObject()->setProperty("carZoom", m_currentZoom);
    });

    connect(ui->btnZoomOut, &QPushButton::clicked, this, [this](){
        m_currentZoom = qMax(2.0, m_currentZoom - 1.0);
        if(m_mapView->rootObject())
            m_mapView->rootObject()->setProperty("carZoom", m_currentZoom);
    });
}

NavigationPage::~NavigationPage(){ delete ui; }

void NavigationPage::bindTelemetry(TelemetryData* t)
{
    m_t = t;
    if(!m_t) return;

    // Mise à jour Latitude / Longitude
    auto refreshPos = [this](){
        ui->lblLat->setText(QString("lat: %1").arg(m_t->lat(), 0, 'f', 6));
        ui->lblLon->setText(QString("lon: %1").arg(m_t->lon(), 0, 'f', 6));

        if(m_mapView && m_mapView->rootObject()){
            m_mapView->rootObject()->setProperty("carLat", m_t->lat());
            m_mapView->rootObject()->setProperty("carLon", m_t->lon());
        }
    };

    // Mise à jour Orientation (Cap)
    auto refreshHeading = [this](){
        if(m_mapView && m_mapView->rootObject()){
            // On envoie la vraie valeur du cap au QML
            m_mapView->rootObject()->setProperty("carHeading", m_t->heading());
        }
    };

    // Appels initiaux
    refreshPos();
    refreshHeading();

    // Connexions
    connect(m_t, &TelemetryData::latChanged, this, refreshPos);
    connect(m_t, &TelemetryData::lonChanged, this, refreshPos);
    connect(m_t, &TelemetryData::headingChanged, this, refreshHeading);
}
