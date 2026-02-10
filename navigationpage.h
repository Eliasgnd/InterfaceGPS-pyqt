#pragma once
#include <QWidget>
#include <QQuickWidget> // <--- Ajout

namespace Ui { class NavigationPage; }
class TelemetryData;

class NavigationPage : public QWidget {
    Q_OBJECT
public:
    explicit NavigationPage(QWidget* parent=nullptr);
    ~NavigationPage();
    void bindTelemetry(TelemetryData* t);

private:
    Ui::NavigationPage* ui;
    TelemetryData* m_t=nullptr;

    QQuickWidget* m_mapView = nullptr; // <--- Ajout
    double m_currentZoom = 15.0;       // Pour gérer le zoom
};
