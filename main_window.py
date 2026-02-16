from __future__ import annotations

from PyQt6 import uic
from PyQt6.QtWidgets import QMainWindow

from camera_page import CameraPage
from home_page import HomePage
from navigation_page import NavigationPage
from settings_page import SettingsPage
from telemetry_data import TelemetryData


class MainWindow(QMainWindow):
    def __init__(self, telemetry: TelemetryData, parent=None) -> None:
        super().__init__(parent)
        uic.loadUi("mainwindow.ui", self)

        self._telemetry = telemetry
        self._home = HomePage(self)
        self._nav = NavigationPage(self)
        self._cam = CameraPage(self)
        self._settings = SettingsPage(self)

        self._home.bind_telemetry(self._telemetry)
        self._nav.bind_telemetry(self._telemetry)
        self._cam.bind_telemetry(self._telemetry)
        self._settings.bind_telemetry(self._telemetry)

        self.stackedPages.addWidget(self._home)
        self.stackedPages.addWidget(self._nav)
        self.stackedPages.addWidget(self._cam)
        self.stackedPages.addWidget(self._settings)
        self.stackedPages.setCurrentWidget(self._home)

        self.btnHome.clicked.connect(self.go_home)
        self.btnNav.clicked.connect(self.go_nav)
        self.btnCam.clicked.connect(self.go_cam)
        self.btnSettings.clicked.connect(self.go_settings)

        self._home.requestNavigation.connect(self.go_nav)
        self._home.requestCamera.connect(self.go_cam)

        self.update_top_bar_and_alert()
        self._telemetry.speedKmhChanged.connect(self.update_top_bar_and_alert)
        self._telemetry.batteryPercentChanged.connect(self.update_top_bar_and_alert)
        self._telemetry.gpsOkChanged.connect(self.update_top_bar_and_alert)
        self._telemetry.reverseChanged.connect(self.update_top_bar_and_alert)
        self._telemetry.alertLevelChanged.connect(self.update_top_bar_and_alert)
        self._telemetry.alertTextChanged.connect(self.update_top_bar_and_alert)

    def go_home(self) -> None:
        self.stackedPages.setCurrentWidget(self._home)

    def go_nav(self) -> None:
        self.stackedPages.setCurrentWidget(self._nav)

    def go_cam(self) -> None:
        self.stackedPages.setCurrentWidget(self._cam)

    def go_settings(self) -> None:
        self.stackedPages.setCurrentWidget(self._settings)

    def update_top_bar_and_alert(self) -> None:
        self.lblSpeed.setText(f"{int(round(self._telemetry.speedKmh))} km/h")
        self.lblBattery.setText(f"Bat {self._telemetry.batteryPercent}%")
        self.lblGps.setText("GPS OK" if self._telemetry.gpsOk else "GPS LOST")
        self.lblGear.setText("R" if self._telemetry.reverse else "D")

        if self._telemetry.alertLevel == 0:
            self.alertFrame.setVisible(False)
            return

        self.alertFrame.setVisible(True)
        self.lblAlertTitle.setText("CRITIQUE" if self._telemetry.alertLevel == 2 else "ALERTE")
        self.lblAlertText.setText(self._telemetry.alertText)

        if self._telemetry.alertLevel == 2:
            self.alertFrame.setStyleSheet("QFrame{background:#8B1E1E;border-radius:10px;} QLabel{color:white;}")
        else:
            self.alertFrame.setStyleSheet("QFrame{background:#6B4B16;border-radius:10px;} QLabel{color:white;}")
