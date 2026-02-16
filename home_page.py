from __future__ import annotations

from PyQt6 import uic
from PyQt6.QtCore import pyqtSignal
from PyQt6.QtWidgets import QWidget

from telemetry_data import TelemetryData


class HomePage(QWidget):
    requestNavigation = pyqtSignal()
    requestCamera = pyqtSignal()

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        uic.loadUi("homepage.ui", self)
        self._telemetry: TelemetryData | None = None

        self.btnNav.clicked.connect(self.requestNavigation)
        self.btnCam.clicked.connect(self.requestCamera)

    def bind_telemetry(self, telemetry: TelemetryData) -> None:
        self._telemetry = telemetry
        if self._telemetry is None:
            return

        refresh = self._refresh
        refresh()

        self._telemetry.speedKmhChanged.connect(refresh)
        self._telemetry.batteryPercentChanged.connect(refresh)
        self._telemetry.gpsOkChanged.connect(refresh)
        self._telemetry.reverseChanged.connect(refresh)

    def _refresh(self) -> None:
        if self._telemetry is None:
            return

        self.lblSpeedBig.setText(str(int(round(self._telemetry.speedKmh))))
        self.lblBattery.setText(f"{self._telemetry.batteryPercent}%")
        self.lblGps.setText("GPS OK" if self._telemetry.gpsOk else "GPS LOST")
        self.lblReverse.setText("R" if self._telemetry.reverse else "D")
