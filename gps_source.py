from __future__ import annotations

from typing import Optional

from PyQt6.QtCore import QIODevice, QObject, pyqtSignal
# Ajout de QGeoPositionInfoSource pour gérer les erreurs (UpdateTimeoutError)
from PyQt6.QtPositioning import QGeoPositionInfo, QNmeaPositionInfoSource, QGeoPositionInfoSource
from PyQt6.QtSerialPort import QSerialPort

from telemetry_data import TelemetryData


class GpsTelemetrySource(QObject):
    """Live telemetry source reading NMEA from /dev/serial0 via QSerialPort."""

    sourceError = pyqtSignal(str)

    def __init__(
        self,
        telemetry: TelemetryData,
        parent: Optional[QObject] = None,
        port_name: str = "/dev/serial0",
        baud_rate: int = 9600,
    ) -> None:
        super().__init__(parent)
        self._telemetry = telemetry
        self._serial = QSerialPort(self)
        self._serial.setPortName(port_name)
        self._serial.setBaudRate(baud_rate)
        self._serial.setDataBits(QSerialPort.DataBits.Data8)
        self._serial.setParity(QSerialPort.Parity.NoParity)
        self._serial.setStopBits(QSerialPort.StopBits.OneStop)
        self._serial.setFlowControl(QSerialPort.FlowControl.NoFlowControl)

        self._nmea = QNmeaPositionInfoSource(QNmeaPositionInfoSource.UpdateMode.RealTimeMode, self)
        self._nmea.setDevice(self._serial)

        self._nmea.positionUpdated.connect(self._on_position_updated)
        # CORRECTION : updateTimeout n'existe plus, on utilise errorOccurred
        self._nmea.errorOccurred.connect(self._on_nmea_error)
        self._serial.errorOccurred.connect(self._on_serial_error)

    def start(self) -> bool:
        if not self._serial.open(QIODevice.OpenModeFlag.ReadOnly):
            self._telemetry.setGpsOk(False)
            msg = f"Impossible d'ouvrir {self._serial.portName()} ({self._serial.errorString()})"
            self.sourceError.emit(msg)
            return False

        self._telemetry.setGpsOk(True)
        self._nmea.startUpdates()
        return True

    def stop(self) -> None:
        self._nmea.stopUpdates()
        if self._serial.isOpen():
            self._serial.close()

    def _on_position_updated(self, info: QGeoPositionInfo) -> None:
        if not info.isValid():
            self._telemetry.setGpsOk(False)
            return

        coord = info.coordinate()
        self._telemetry.setLat(coord.latitude())
        self._telemetry.setLon(coord.longitude())
        self._telemetry.setGpsOk(True)

        speed = info.attribute(QGeoPositionInfo.Attribute.GroundSpeed)
        if speed > 0:
            self._telemetry.setSpeedKmh(speed * 3.6)

        heading = info.attribute(QGeoPositionInfo.Attribute.Direction)
        if heading >= 0:
            self._telemetry.setHeading(float(heading))

    # CORRECTION : Cette fonction est bien alignée (au niveau de la classe)
    def _on_nmea_error(self, error: QGeoPositionInfoSource.Error) -> None:
        if error == QGeoPositionInfoSource.Error.UpdateTimeoutError:
            self._telemetry.setGpsOk(False)
            self.sourceError.emit("Timeout GPS: aucune trame NMEA reçue")
        elif error == QGeoPositionInfoSource.Error.AccessError:
            self.sourceError.emit("Erreur d'accès aux données GPS")

    def _on_serial_error(self, error: QSerialPort.SerialPortError) -> None:
        if error == QSerialPort.SerialPortError.NoError:
            return
        self._telemetry.setGpsOk(False)
        self.sourceError.emit(f"Erreur série: {self._serial.errorString()}")
