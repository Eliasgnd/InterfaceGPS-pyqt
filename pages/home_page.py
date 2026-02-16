from __future__ import annotations

from pathlib import Path

from PyQt6 import uic
from PyQt6.QtCore import pyqtSignal
from PyQt6.QtWidgets import QWidget

from telemetry_data import TelemetryData


class HomePage(QWidget):
    requestNavigation = pyqtSignal()
    requestCamera = pyqtSignal()

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        uic.loadUi(Path(__file__).resolve().parent.parent / "homepage.ui", self)
        self._telemetry: TelemetryData | None = None
        self.btnNav.clicked.connect(self.requestNavigation.emit)
        self.btnCam.clicked.connect(self.requestCamera.emit)

    def bindTelemetry(self, telemetry: TelemetryData | None) -> None:
        self._telemetry = telemetry
        if not telemetry:
            return

        def refresh() -> None:
            self.lblSpeedBig.setText(str(round(telemetry.speedKmh)))
            self.lblBattery.setText(f"{telemetry.batteryPercent}%")
            self.lblGps.setText("GPS OK" if telemetry.gpsOk else "GPS LOST")
            self.lblReverse.setText("R" if telemetry.reverse else "D")

        refresh()
        telemetry.speedKmhChanged.connect(refresh)
        telemetry.batteryPercentChanged.connect(refresh)
        telemetry.gpsOkChanged.connect(refresh)
        telemetry.reverseChanged.connect(refresh)
