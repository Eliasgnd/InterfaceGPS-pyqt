from __future__ import annotations

from PyQt6 import uic
from PyQt6.QtCore import pyqtSignal
from PyQt6.QtWidgets import QWidget

from telemetry_data import TelemetryData


class SettingsPage(QWidget):
    themeChanged = pyqtSignal(int)
    brightnessChanged = pyqtSignal(int)

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        uic.loadUi("settingspage.ui", self)
        self._telemetry: TelemetryData | None = None

        self.sliderBrightness.valueChanged.connect(self._on_brightness_changed)
        self.cmbTheme.currentIndexChanged.connect(self.themeChanged)

    def _on_brightness_changed(self, value: int) -> None:
        self.lblBrightnessValue.setText(str(value))
        self.brightnessChanged.emit(value)

    def bind_telemetry(self, telemetry: TelemetryData) -> None:
        self._telemetry = telemetry
