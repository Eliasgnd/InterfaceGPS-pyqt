#include "navigationpage.h"
#include "ui_navigationpage.h"
#include "telemetrydata.h"
#include <QQmlContext>
#include <QQuickItem>
#include <QtCore>
#include <QDebug>

NavigationPage::NavigationPage(QWidget* parent)
    : QWidget(parent), ui(new Ui::NavigationPage)
{
    ui->setupUi(this);

    m_mapView = new QQuickWidget(this);

    // Récupération de la clé API (si vous voulez repasser à Mapbox plus tard)
    QString apiKey = QString::fromLocal8Bit(qgetenv("MAPBOX_KEY"));
    m_mapView->rootContext()->setContextProperty("mapboxApiKey", apiKey);

    m_mapView->setSource(QUrl("qrc:/map.qml"));
    m_mapView->setResizeMode(QQuickWidget::SizeRootObjectToView);

    ui->lblMap->setVisible(false);
    ui->mapLayout->addWidget(m_mapView);

    // Zoom
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

    // Centrer
    connect(ui->btnCenter, &QPushButton::clicked, this, [this](){
        if(m_mapView && m_mapView->rootObject()){
            QMetaObject::invokeMethod(m_mapView->rootObject(), "recenterMap");
        }
    });
}

NavigationPage::~NavigationPage(){ delete ui; }

void NavigationPage::bindTelemetry(TelemetryData* t)
{
    m_t = t;
    if(!m_t) return;

    auto refresh = [this](){
        ui->lblLat->setText(QString("lat: %1").arg(m_t->lat(), 0, 'f', 6));
        ui->lblLon->setText(QString("lon: %1").arg(m_t->lon(), 0, 'f', 6));

        if(m_mapView && m_mapView->rootObject()){
            m_mapView->rootObject()->setProperty("carLat", m_t->lat());
            m_mapView->rootObject()->setProperty("carLon", m_t->lon());
            m_mapView->rootObject()->setProperty("carHeading", m_t->heading());
        }
    };

    refresh();
    connect(m_t, &TelemetryData::latChanged, this, refresh);
    connect(m_t, &TelemetryData::lonChanged, this, refresh);
    connect(m_t, &TelemetryData::headingChanged, this, refresh);
}
