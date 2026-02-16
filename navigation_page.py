from __future__ import annotations

import json
import os

from PyQt6 import uic
from PyQt6.QtCore import QTimer, Qt, QStringListModel, QUrl
from PyQt6.QtQuickWidgets import QQuickWidget
from PyQt6.QtWidgets import QCompleter, QWidget

from telemetry_data import TelemetryData


class NavigationPage(QWidget):
    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        uic.loadUi("navigationpage.ui", self)

        self._telemetry: TelemetryData | None = None
        self._last_calculated_route: list = []
        self._ignore_text_update = False

        self._suggestions_model = QStringListModel(self)
        self._search_completer = QCompleter(self._suggestions_model, self)
        self._search_completer.setCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)
        self._search_completer.setFilterMode(Qt.MatchFlag.MatchContains)
        self._search_completer.setCompletionMode(QCompleter.CompletionMode.UnfilteredPopupCompletion)
        self.editSearch.setCompleter(self._search_completer)

        self._suggestion_debounce_timer = QTimer(self)
        self._suggestion_debounce_timer.setSingleShot(True)
        self._suggestion_debounce_timer.setInterval(300)

        self._search_completer.activated[str].connect(self.on_suggestion_chosen)
        self._suggestion_debounce_timer.timeout.connect(self.trigger_suggestions_search)
        self.editSearch.textEdited.connect(self._on_text_edited)

        self._map_view = QQuickWidget(self)
        self._map_view.rootContext().setContextProperty("mapboxApiKey", os.environ.get("MAPBOX_API_KEY", "").strip())
        self._map_view.rootContext().setContextProperty("hereApiKey", os.environ.get("HERE_API_KEY", "").strip())
        self._map_view.setResizeMode(QQuickWidget.ResizeMode.SizeRootObjectToView)
        self._map_view.statusChanged.connect(self._on_qml_status_changed)
        self._map_view.setSource(QUrl("qrc:/map.qml"))

        self.lblMap.setVisible(False)
        self.mapLayout.addWidget(self._map_view)

        self.btnZoomIn.clicked.connect(self._zoom_in)
        self.btnZoomOut.clicked.connect(self._zoom_out)
        self.btnCenter.clicked.connect(lambda: self._call_qml("recenterMap"))
        self.btnSearch.clicked.connect(lambda: self.request_route_for_text(self.editSearch.text()))
        self.editSearch.returnPressed.connect(self._on_search_return)
        self.btnSimulate.clicked.connect(self._simulate_last_route)

        self._qml_connected = False
        self._setup_qml_connections()

    def _on_text_edited(self, text: str) -> None:
        if not self._ignore_text_update and len(text) >= 2:
            self._suggestion_debounce_timer.start()

    def _on_qml_status_changed(self, status: QQuickWidget.Status) -> None:
        if status == QQuickWidget.Status.Ready:
            self._setup_qml_connections()

    def _setup_qml_connections(self) -> None:
        root = self._map_view.rootObject()
        if root is None or self._qml_connected:
            return

        if hasattr(root, "routeInfoUpdated"):
            root.routeInfoUpdated.connect(self.on_route_info_received)
        if hasattr(root, "suggestionsUpdated"):
            root.suggestionsUpdated.connect(self.on_suggestions_received)
        if hasattr(root, "routeReadyForSimulation"):
            root.routeReadyForSimulation.connect(self.on_route_ready_for_simulation)

        self._qml_connected = True

    def _zoom_in(self) -> None:
        root = self._map_view.rootObject()
        if root is None:
            return
        z = float(root.property("carZoom"))
        root.setProperty("carZoom", z + 1)

    def _zoom_out(self) -> None:
        root = self._map_view.rootObject()
        if root is None:
            return
        z = float(root.property("carZoom"))
        root.setProperty("carZoom", z - 1)

    def _on_search_return(self) -> None:
        self.request_route_for_text(self.editSearch.text())
        self.editSearch.clearFocus()

    def _simulate_last_route(self) -> None:
        if self._telemetry and self._last_calculated_route:
            self._telemetry.simulateRouteRequested.emit(self._last_calculated_route)

    def _call_qml(self, method_name: str, *args) -> None:
        root = self._map_view.rootObject()
        if root is None:
            return
        method = getattr(root, method_name, None)
        if callable(method):
            method(*args)

    def on_suggestions_received(self, json_suggestions: str) -> None:
        try:
            suggestions = [str(item) for item in json.loads(json_suggestions)]
        except (json.JSONDecodeError, TypeError, ValueError):
            suggestions = []

        self._suggestions_model.setStringList(suggestions)
        if suggestions and self.editSearch.hasFocus():
            self._search_completer.complete()

    def on_route_info_received(self, distance: str, duration: str) -> None:
        self.lblLat.setText(f"Dist: {distance}")
        self.lblLon.setText(f"Temps: {duration}")

    def bind_telemetry(self, telemetry: TelemetryData) -> None:
        self._telemetry = telemetry
        if self._telemetry is None:
            return

        refresh = self._refresh_telemetry
        refresh()
        self._telemetry.latChanged.connect(refresh)
        self._telemetry.lonChanged.connect(refresh)
        self._telemetry.headingChanged.connect(refresh)
        self._telemetry.speedKmhChanged.connect(refresh)

    def _refresh_telemetry(self) -> None:
        if self._telemetry is None:
            return

        root = self._map_view.rootObject()
        if root is None:
            return

        root.setProperty("carLat", self._telemetry.lat)
        root.setProperty("carLon", self._telemetry.lon)
        root.setProperty("carHeading", self._telemetry.heading)
        root.setProperty("carSpeed", self._telemetry.speedKmh)

    def request_route_for_text(self, destination: str) -> None:
        destination = destination.strip()
        if not destination:
            return
        self._call_qml("searchDestination", destination)

    def on_suggestion_chosen(self, suggestion: str) -> None:
        self._ignore_text_update = True
        self.editSearch.setText(suggestion)
        self._ignore_text_update = False
        self.request_route_for_text(suggestion)

    def trigger_suggestions_search(self) -> None:
        query = self.editSearch.text().strip()
        if len(query) < 3:
            self._suggestions_model.setStringList([])
            return
        self._call_qml("requestSuggestions", query)

    def on_route_ready_for_simulation(self, path_obj) -> None:
        self._last_calculated_route = list(path_obj or [])
