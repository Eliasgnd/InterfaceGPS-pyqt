from __future__ import annotations

import math
from typing import Optional

from PyQt6.QtCore import QObject, QTimer

from telemetry_data import TelemetryData


class MockTelemetrySource(QObject):
    """Fallback telemetry source: generates synthetic movement and can replay a route."""

    def __init__(self, telemetry: TelemetryData, parent: Optional[QObject] = None) -> None:
        super().__init__(parent)
        self._telemetry = telemetry
        self._timer = QTimer(self)
        self._timer.setInterval(200)
        self._timer.timeout.connect(self._tick)

        self._route: list[dict[str, float]] = []
        self._route_index = 0
        self._phase = 0.0
        self._base_lat = telemetry.lat
        self._base_lon = telemetry.lon

        self._telemetry.simulateRouteRequested.connect(self.start_route_simulation)

    def start(self) -> None:
        self._telemetry.setGpsOk(True)
        self._timer.start()

    def stop(self) -> None:
        self._timer.stop()

    def start_route_simulation(self, route_coords: list) -> None:
        cleaned: list[dict[str, float]] = []
        for item in route_coords:
            if isinstance(item, dict) and "lat" in item and "lon" in item:
                try:
                    cleaned.append({"lat": float(item["lat"]), "lon": float(item["lon"])})
                except (TypeError, ValueError):
                    continue

        if len(cleaned) >= 2:
            self._route = cleaned
            self._route_index = 0
            self._telemetry.setAlertLevel(1)
            self._telemetry.setAlertText("Simulation itinéraire en cours")

    def _tick(self) -> None:
        if self._route:
            self._tick_route()
            return

        # Idle synthetic movement around initial point
        self._phase += 0.05
        lat = self._base_lat + (math.sin(self._phase) * 0.0003)
        lon = self._base_lon + (math.cos(self._phase * 0.7) * 0.0003)
        heading = (math.degrees(self._phase) * 3) % 360
        speed = 18 + 8 * (1 + math.sin(self._phase * 1.4))

        self._telemetry.setLat(lat)
        self._telemetry.setLon(lon)
        self._telemetry.setHeading(heading)
        self._telemetry.setSpeedKmh(speed)
        self._telemetry.setGpsOk(True)

    def _tick_route(self) -> None:
        if self._route_index >= len(self._route):
            self._route = []
            self._telemetry.setSpeedKmh(0.0)
            self._telemetry.setAlertLevel(1)
            self._telemetry.setAlertText("Simulation terminée")
            return

        current = self._route[self._route_index]
        self._telemetry.setLat(current["lat"])
        self._telemetry.setLon(current["lon"])

        if self._route_index > 0:
            prev = self._route[self._route_index - 1]
            dy = current["lat"] - prev["lat"]
            dx = current["lon"] - prev["lon"]
            heading = (math.degrees(math.atan2(dx, dy)) + 360) % 360
            self._telemetry.setHeading(heading)

        self._telemetry.setSpeedKmh(40.0)
        self._telemetry.setGpsOk(True)
        self._route_index += 1
