from __future__ import annotations

from PyQt6 import uic
from PyQt6.QtWidgets import QWidget

from telemetry_data import TelemetryData


class CameraPage(QWidget):
    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        uic.loadUi("camerapage.ui", self)
        self._telemetry: TelemetryData | None = None

        self.btnRear.clicked.connect(lambda: self.set_mode("REAR"))
        self.btnFront.clicked.connect(lambda: self.set_mode("FRONT"))
        self.btnMosaic.clicked.connect(lambda: self.set_mode("MOSAIC"))
        self.btnBird.clicked.connect(lambda: self.set_mode("BIRD-EYE"))

    def set_mode(self, mode: str) -> None:
        self.lblMode.setText(f"Mode: {mode}")

    def bind_telemetry(self, telemetry: TelemetryData) -> None:
        self._telemetry = telemetry
        if self._telemetry is None:
            return

        refresh = self._refresh
        refresh()
        self._telemetry.reverseChanged.connect(refresh)

    def _refresh(self) -> None:
        if self._telemetry is None:
            return

        if self._telemetry.reverse:
            self.lblVideo.setText("Flux caméra / Bird-eye - placeholder\n(REVERSE engagé)")
            self.lblVideo.setStyleSheet("QLabel{color:#FFD27C; font-size:16px;}")
        else:
            self.lblVideo.setText("Flux caméra / Bird-eye - placeholder")
            self.lblVideo.setStyleSheet("QLabel{color:#b8c0cc; font-size:16px;}")
