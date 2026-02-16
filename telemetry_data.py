from __future__ import annotations

import math

from PyQt6.QtCore import QObject, pyqtProperty, pyqtSignal


class TelemetryData(QObject):
    speedKmhChanged = pyqtSignal()
    batteryPercentChanged = pyqtSignal()
    reverseChanged = pyqtSignal()
    gpsOkChanged = pyqtSignal()
    latChanged = pyqtSignal()
    lonChanged = pyqtSignal()
    headingChanged = pyqtSignal()
    alertTextChanged = pyqtSignal()
    alertLevelChanged = pyqtSignal()
    simulateRouteRequested = pyqtSignal(list)

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self._speed_kmh = 0.0
        self._battery_percent = 100
        self._reverse = False
        self._gps_ok = True
        self._lat = 48.8566
        self._lon = 2.3522
        self._heading = 0.0
        self._alert_text = ""
        self._alert_level = 0

    def get_speed_kmh(self) -> float:
        return self._speed_kmh

    def set_speed_kmh(self, value: float) -> None:
        if math.isclose(self._speed_kmh, value, rel_tol=1e-9, abs_tol=1e-9):
            return
        self._speed_kmh = value
        self.speedKmhChanged.emit()

    speedKmh = pyqtProperty(float, fget=get_speed_kmh, fset=set_speed_kmh, notify=speedKmhChanged)

    def get_battery_percent(self) -> int:
        return self._battery_percent

    def set_battery_percent(self, value: int) -> None:
        bounded = max(0, min(int(value), 100))
        if self._battery_percent == bounded:
            return
        self._battery_percent = bounded
        self.batteryPercentChanged.emit()

    batteryPercent = pyqtProperty(int, fget=get_battery_percent, fset=set_battery_percent, notify=batteryPercentChanged)

    def get_reverse(self) -> bool:
        return self._reverse

    def set_reverse(self, value: bool) -> None:
        flag = bool(value)
        if self._reverse == flag:
            return
        self._reverse = flag
        self.reverseChanged.emit()

    reverse = pyqtProperty(bool, fget=get_reverse, fset=set_reverse, notify=reverseChanged)

    def get_gps_ok(self) -> bool:
        return self._gps_ok

    def set_gps_ok(self, value: bool) -> None:
        flag = bool(value)
        if self._gps_ok == flag:
            return
        self._gps_ok = flag
        self.gpsOkChanged.emit()

    gpsOk = pyqtProperty(bool, fget=get_gps_ok, fset=set_gps_ok, notify=gpsOkChanged)

    def get_lat(self) -> float:
        return self._lat

    def set_lat(self, value: float) -> None:
        if math.isclose(self._lat, value, rel_tol=1e-9, abs_tol=1e-9):
            return
        self._lat = value
        self.latChanged.emit()

    lat = pyqtProperty(float, fget=get_lat, fset=set_lat, notify=latChanged)

    def get_lon(self) -> float:
        return self._lon

    def set_lon(self, value: float) -> None:
        if math.isclose(self._lon, value, rel_tol=1e-9, abs_tol=1e-9):
            return
        self._lon = value
        self.lonChanged.emit()

    lon = pyqtProperty(float, fget=get_lon, fset=set_lon, notify=lonChanged)

    def get_heading(self) -> float:
        return self._heading

    def set_heading(self, value: float) -> None:
        if math.isclose(self._heading, value, rel_tol=1e-9, abs_tol=1e-9):
            return
        self._heading = value
        self.headingChanged.emit()

    heading = pyqtProperty(float, fget=get_heading, fset=set_heading, notify=headingChanged)

    def get_alert_text(self) -> str:
        return self._alert_text

    def set_alert_text(self, value: str) -> None:
        text = str(value)
        if self._alert_text == text:
            return
        self._alert_text = text
        self.alertTextChanged.emit()

    alertText = pyqtProperty(str, fget=get_alert_text, fset=set_alert_text, notify=alertTextChanged)

    def get_alert_level(self) -> int:
        return self._alert_level

    def set_alert_level(self, value: int) -> None:
        level = int(value)
        if self._alert_level == level:
            return
        self._alert_level = level
        self.alertLevelChanged.emit()

    alertLevel = pyqtProperty(int, fget=get_alert_level, fset=set_alert_level, notify=alertLevelChanged)
