from __future__ import annotations

from pathlib import Path

from PyQt6 import uic
from PyQt6.QtWidgets import QWidget

from telemetry_data import TelemetryData


class CameraPage(QWidget):
    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        uic.loadUi(Path(__file__).resolve().parent.parent / "camerapage.ui", self)
        self._telemetry: TelemetryData | None = None
        self.btnRear.clicked.connect(lambda: self._set_mode("REAR"))
        self.btnFront.clicked.connect(lambda: self._set_mode("FRONT"))
        self.btnMosaic.clicked.connect(lambda: self._set_mode("MOSAIC"))
        self.btnBird.clicked.connect(lambda: self._set_mode("BIRD-EYE"))

    def _set_mode(self, mode: str) -> None:
        self.lblMode.setText(f"Mode: {mode}")

    def bindTelemetry(self, telemetry: TelemetryData | None) -> None:
        self._telemetry = telemetry
        if not telemetry:
            return

        def refresh() -> None:
            if telemetry.reverse:
                self.lblVideo.setText("Flux caméra / Bird-eye - placeholder\n(REVERSE engagé)")
                self.lblVideo.setStyleSheet("QLabel{color:#FFD27C; font-size:16px;}")
            else:
                self.lblVideo.setText("Flux caméra / Bird-eye - placeholder")
                self.lblVideo.setStyleSheet("QLabel{color:#b8c0cc; font-size:16px;}")

        refresh()
        telemetry.reverseChanged.connect(refresh)
