from __future__ import annotations

from pathlib import Path

from PyQt6 import uic
from PyQt6.QtWidgets import QMainWindow

from pages import CameraPage, HomePage, NavigationPage, SettingsPage
from telemetry_data import TelemetryData


class MainWindow(QMainWindow):
    def __init__(self, telemetry: TelemetryData, parent=None) -> None:
        super().__init__(parent)
        self._telemetry = telemetry
        uic.loadUi(Path(__file__).resolve().parent / "mainwindow.ui", self)

        self._home = HomePage(self)
        self._nav = NavigationPage(self)
        self._cam = CameraPage(self)
        self._settings = SettingsPage(self)

        self._home.bindTelemetry(telemetry)
        self._nav.bindTelemetry(telemetry)
        self._cam.bindTelemetry(telemetry)
        self._settings.bindTelemetry(telemetry)

        self.stackedPages.addWidget(self._home)
        self.stackedPages.addWidget(self._nav)
        self.stackedPages.addWidget(self._cam)
        self.stackedPages.addWidget(self._settings)
        self.stackedPages.setCurrentWidget(self._home)

        self.btnHome.clicked.connect(self.goHome)
        self.btnNav.clicked.connect(self.goNav)
        self.btnCam.clicked.connect(self.goCam)
        self.btnSettings.clicked.connect(self.goSettings)

        self._home.requestNavigation.connect(self.goNav)
        self._home.requestCamera.connect(self.goCam)

        self.updateTopBarAndAlert()
        telemetry.speedKmhChanged.connect(self.updateTopBarAndAlert)
        telemetry.batteryPercentChanged.connect(self.updateTopBarAndAlert)
        telemetry.gpsOkChanged.connect(self.updateTopBarAndAlert)
        telemetry.reverseChanged.connect(self.updateTopBarAndAlert)
        telemetry.alertLevelChanged.connect(self.updateTopBarAndAlert)
        telemetry.alertTextChanged.connect(self.updateTopBarAndAlert)

    def goHome(self) -> None:
        self.stackedPages.setCurrentWidget(self._home)

    def goNav(self) -> None:
        self.stackedPages.setCurrentWidget(self._nav)

    def goCam(self) -> None:
        self.stackedPages.setCurrentWidget(self._cam)

    def goSettings(self) -> None:
        self.stackedPages.setCurrentWidget(self._settings)

    def updateTopBarAndAlert(self) -> None:
        self.lblSpeed.setText(f"{round(self._telemetry.speedKmh)} km/h")
        self.lblBattery.setText(f"Bat {self._telemetry.batteryPercent}%")
        self.lblGps.setText("GPS OK" if self._telemetry.gpsOk else "GPS LOST")
        self.lblGear.setText("R" if self._telemetry.reverse else "D")

        if self._telemetry.alertLevel == 0:
            self.alertFrame.setVisible(False)
            return

        self.alertFrame.setVisible(True)
        critical = self._telemetry.alertLevel == 2
        self.lblAlertTitle.setText("CRITIQUE" if critical else "ALERTE")
        self.lblAlertText.setText(self._telemetry.alertText)
        if critical:
            self.alertFrame.setStyleSheet("QFrame{background:#8B1E1E;border-radius:10px;} QLabel{color:white;}")
        else:
            self.alertFrame.setStyleSheet("QFrame{background:#6B4B16;border-radius:10px;} QLabel{color:white;}")
