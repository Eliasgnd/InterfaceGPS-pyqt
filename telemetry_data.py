from __future__ import annotations

from math import isclose

from PyQt6.QtCore import QObject, pyqtProperty, pyqtSignal, pyqtSlot


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

    @pyqtProperty(float, notify=speedKmhChanged)
    def speedKmh(self) -> float:
        return self._speed_kmh

    @speedKmh.setter
    def speedKmh(self, value: float) -> None:
        self.setSpeedKmh(value)

    @pyqtSlot(float)
    def setSpeedKmh(self, value: float) -> None:
        if isclose(self._speed_kmh, value):
            return
        self._speed_kmh = value
        self.speedKmhChanged.emit()

    @pyqtProperty(int, notify=batteryPercentChanged)
    def batteryPercent(self) -> int:
        return self._battery_percent

    @batteryPercent.setter
    def batteryPercent(self, value: int) -> None:
        self.setBatteryPercent(value)

    @pyqtSlot(int)
    def setBatteryPercent(self, value: int) -> None:
        value = max(0, min(value, 100))
        if self._battery_percent == value:
            return
        self._battery_percent = value
        self.batteryPercentChanged.emit()

    @pyqtProperty(bool, notify=reverseChanged)
    def reverse(self) -> bool:
        return self._reverse

    @reverse.setter
    def reverse(self, value: bool) -> None:
        self.setReverse(value)

    @pyqtSlot(bool)
    def setReverse(self, value: bool) -> None:
        if self._reverse == value:
            return
        self._reverse = value
        self.reverseChanged.emit()

    @pyqtProperty(bool, notify=gpsOkChanged)
    def gpsOk(self) -> bool:
        return self._gps_ok

    @gpsOk.setter
    def gpsOk(self, value: bool) -> None:
        self.setGpsOk(value)

    @pyqtSlot(bool)
    def setGpsOk(self, value: bool) -> None:
        if self._gps_ok == value:
            return
        self._gps_ok = value
        self.gpsOkChanged.emit()

    @pyqtProperty(float, notify=latChanged)
    def lat(self) -> float:
        return self._lat

    @lat.setter
    def lat(self, value: float) -> None:
        self.setLat(value)

    @pyqtSlot(float)
    def setLat(self, value: float) -> None:
        if isclose(self._lat, value):
            return
        self._lat = value
        self.latChanged.emit()

    @pyqtProperty(float, notify=lonChanged)
    def lon(self) -> float:
        return self._lon

    @lon.setter
    def lon(self, value: float) -> None:
        self.setLon(value)

    @pyqtSlot(float)
    def setLon(self, value: float) -> None:
        if isclose(self._lon, value):
            return
        self._lon = value
        self.lonChanged.emit()

    @pyqtProperty(float, notify=headingChanged)
    def heading(self) -> float:
        return self._heading

    @heading.setter
    def heading(self, value: float) -> None:
        self.setHeading(value)

    @pyqtSlot(float)
    def setHeading(self, value: float) -> None:
        if isclose(self._heading, value):
            return
        self._heading = value
        self.headingChanged.emit()

    @pyqtProperty(str, notify=alertTextChanged)
    def alertText(self) -> str:
        return self._alert_text

    @alertText.setter
    def alertText(self, value: str) -> None:
        self.setAlertText(value)

    @pyqtSlot(str)
    def setAlertText(self, value: str) -> None:
        if self._alert_text == value:
            return
        self._alert_text = value
        self.alertTextChanged.emit()

    @pyqtProperty(int, notify=alertLevelChanged)
    def alertLevel(self) -> int:
        return self._alert_level

    @alertLevel.setter
    def alertLevel(self, value: int) -> None:
        self.setAlertLevel(value)

    @pyqtSlot(int)
    def setAlertLevel(self, value: int) -> None:
        if self._alert_level == value:
            return
        self._alert_level = value
        self.alertLevelChanged.emit()
