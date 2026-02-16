from __future__ import annotations

from PyQt6.QtCore import QObject, QTimer
from PyQt6.QtPositioning import QGeoCoordinate

from telemetry_data import TelemetryData


class MockTelemetrySource(QObject):
    def __init__(self, data: TelemetryData, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self._data = data
        self._route_points: list[QGeoCoordinate] = [
            QGeoCoordinate(48.269593, 4.079829),
            QGeoCoordinate(48.267314, 4.076437),
            QGeoCoordinate(48.267109, 4.076079),
            QGeoCoordinate(48.266902, 4.076267),
            QGeoCoordinate(48.265805, 4.078167),
            QGeoCoordinate(48.265751, 4.078509),
            QGeoCoordinate(48.265811, 4.078861),
            QGeoCoordinate(48.265971, 4.079096),
            QGeoCoordinate(48.266183, 4.079264),
            QGeoCoordinate(48.266268, 4.079301),
            QGeoCoordinate(48.266330, 4.079389),
            QGeoCoordinate(48.266389, 4.079547),
            QGeoCoordinate(48.266724, 4.079708),
            QGeoCoordinate(48.266847, 4.079909),
            QGeoCoordinate(48.266970, 4.080257),
            QGeoCoordinate(48.267120, 4.080900),
            QGeoCoordinate(48.267252, 4.081123),
            QGeoCoordinate(48.268008, 4.082088),
            QGeoCoordinate(48.268121, 4.082421),
            QGeoCoordinate(48.268126, 4.083243),
            QGeoCoordinate(48.268186, 4.083592),
            QGeoCoordinate(48.268387, 4.083990),
            QGeoCoordinate(48.268982, 4.084626),
            QGeoCoordinate(48.270582, 4.081287),
        ]
        self._current_index = 0
        self._current_exact_pos = self._route_points[0] if self._route_points else QGeoCoordinate()

        self._timer = QTimer(self)
        self._timer.setInterval(50)
        self._timer.timeout.connect(self.tick)

        self._data.simulateRouteRequested.connect(self._on_simulate_route_requested)

    def _on_simulate_route_requested(self, route_coords: list) -> None:
        if not route_coords:
            return

        points: list[QGeoCoordinate] = []
        for point in route_coords:
            lat = point.get("lat") if isinstance(point, dict) else None
            lon = point.get("lon") if isinstance(point, dict) else None
            if lat is None or lon is None:
                continue
            points.append(QGeoCoordinate(float(lat), float(lon)))

        if not points:
            return

        self._route_points = points
        self._current_index = 0
        self._current_exact_pos = self._route_points[0]

    def start(self) -> None:
        self._timer.start()

    def stop(self) -> None:
        self._timer.stop()

    def tick(self) -> None:
        if self._data is None or not self._route_points:
            return

        next_index = self._current_index + 1
        if next_index >= len(self._route_points):
            self._data.speedKmh = 0.0
            return

        target = self._route_points[next_index]

        speed_kmh = 50.0
        speed_ms = speed_kmh / 3.6
        step_distance = speed_ms * 0.05
        dist_to_target = self._current_exact_pos.distanceTo(target)
        azimuth = self._current_exact_pos.azimuthTo(target)

        if dist_to_target <= step_distance:
            self._current_exact_pos = target
            self._current_index = next_index
            next_next = next_index + 1
            if next_next < len(self._route_points):
                azimuth = self._current_exact_pos.azimuthTo(self._route_points[next_next])
        else:
            self._current_exact_pos = self._current_exact_pos.atDistanceAndAzimuth(step_distance, azimuth)

        self._data.lat = self._current_exact_pos.latitude()
        self._data.lon = self._current_exact_pos.longitude()
        self._data.heading = azimuth
        self._data.speedKmh = speed_kmh
        self._data.gpsOk = True
