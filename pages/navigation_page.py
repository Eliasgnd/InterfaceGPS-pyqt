from __future__ import annotations

import json
import os
from pathlib import Path

from PyQt6 import uic
from PyQt6.QtCore import QTimer, Qt, QUrl
from PyQt6.QtQml import QQmlContext
from PyQt6.QtQuickWidgets import QQuickWidget
from PyQt6.QtWidgets import QCompleter, QWidget
from PyQt6.QtCore import QStringListModel

from telemetry_data import TelemetryData


class NavigationPage(QWidget):
    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        uic.loadUi(Path(__file__).resolve().parent.parent / "navigationpage.ui", self)
        self._telemetry: TelemetryData | None = None
        self._last_calculated_route: list = []

        self._suggestions_model = QStringListModel(self)
        self._completer = QCompleter(self._suggestions_model, self)
        self._completer.setCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)
        self._completer.setFilterMode(Qt.MatchFlag.MatchContains)
        self._completer.setCompletionMode(QCompleter.CompletionMode.UnfilteredPopupCompletion)
        self.editSearch.setCompleter(self._completer)

        self._debounce = QTimer(self)
        self._debounce.setSingleShot(True)
        self._debounce.setInterval(300)
        self._ignore_text_update = False

        self._completer.activated.connect(self._on_suggestion_chosen)
        self._debounce.timeout.connect(self._trigger_suggestions_search)
        self.editSearch.textEdited.connect(self._on_text_edited)

        self._map_view = QQuickWidget(self)
        self._map_view.setResizeMode(QQuickWidget.ResizeMode.SizeRootObjectToView)
        root_ctx: QQmlContext = self._map_view.rootContext()
        root_ctx.setContextProperty("mapboxApiKey", os.getenv("MAPBOX_API_KEY", "").strip())
        root_ctx.setContextProperty("hereApiKey", os.getenv("HERE_API_KEY", "").strip())
        root_ctx.setContextProperty("iconsBasePath", Path(__file__).resolve().parent.parent.as_uri() + "/")

        self._map_view.statusChanged.connect(self._setup_qml_connections)
        self._map_view.setSource(QUrl("qrc:/map.qml"))
        if self._map_view.status() == QQuickWidget.Status.Error:
            self._map_view.setSource(QUrl.fromLocalFile(str(Path(__file__).resolve().parent.parent / "map.qml")))

        self.lblMap.setVisible(False)
        self.mapLayout.addWidget(self._map_view)

        self.btnZoomIn.clicked.connect(lambda: self._set_zoom_delta(1))
        self.btnZoomOut.clicked.connect(lambda: self._set_zoom_delta(-1))
        self.btnCenter.clicked.connect(self._recenter)
        self.btnSearch.clicked.connect(lambda: self._request_route_for_text(self.editSearch.text()))
        self.editSearch.returnPressed.connect(self._request_from_enter)
        self.btnSimulate.clicked.connect(self._simulate_route)

    def _setup_qml_connections(self, _status: object) -> None:
        root = self._map_view.rootObject()
        if not root:
            return
        root.routeInfoUpdated.connect(self._on_route_info_received)
        root.suggestionsUpdated.connect(self._on_suggestions_received)
        root.routeReadyForSimulation.connect(self._on_route_ready_for_simulation)

    def _on_text_edited(self, text: str) -> None:
        if not self._ignore_text_update and len(text) >= 2:
            self._debounce.start()

    def _set_zoom_delta(self, delta: int) -> None:
        root = self._map_view.rootObject()
        if not root:
            return
        current = float(root.property("carZoom"))
        root.setProperty("carZoom", current + delta)

    def _recenter(self) -> None:
        root = self._map_view.rootObject()
        if root:
            root.recenterMap()

    def _request_from_enter(self) -> None:
        self._request_route_for_text(self.editSearch.text())
        self.editSearch.clearFocus()

    def _request_route_for_text(self, destination: str) -> None:
        text = destination.strip()
        root = self._map_view.rootObject()
        if text and root:
            root.searchDestination(text)

    def _on_suggestion_chosen(self, suggestion: str) -> None:
        self._ignore_text_update = True
        self.editSearch.setText(suggestion)
        self._ignore_text_update = False
        self._request_route_for_text(suggestion)

    def _trigger_suggestions_search(self) -> None:
        query = self.editSearch.text().strip()
        if len(query) < 3:
            self._suggestions_model.setStringList([])
            return
        root = self._map_view.rootObject()
        if root:
            root.requestSuggestions(query)

    def _on_suggestions_received(self, json_suggestions: str) -> None:
        data = json.loads(json_suggestions)
        suggestions = [str(item) for item in data]
        self._suggestions_model.setStringList(suggestions)
        if suggestions and self.editSearch.hasFocus():
            self._completer.complete()

    def _on_route_info_received(self, distance: str, duration: str) -> None:
        self.lblLat.setText(f"Dist: {distance}")
        self.lblLon.setText(f"Temps: {duration}")

    def _on_route_ready_for_simulation(self, path_obj: list) -> None:
        self._last_calculated_route = list(path_obj)

    def _simulate_route(self) -> None:
        if self._telemetry and self._last_calculated_route:
            self._telemetry.simulateRouteRequested.emit(self._last_calculated_route)

    def bindTelemetry(self, telemetry: TelemetryData | None) -> None:
        self._telemetry = telemetry
        if not telemetry:
            return

        def refresh() -> None:
            root = self._map_view.rootObject()
            if root:
                root.setProperty("carLat", telemetry.lat)
                root.setProperty("carLon", telemetry.lon)
                root.setProperty("carHeading", telemetry.heading)
                root.setProperty("carSpeed", telemetry.speedKmh)

        refresh()
        telemetry.latChanged.connect(refresh)
        telemetry.lonChanged.connect(refresh)
        telemetry.headingChanged.connect(refresh)
        telemetry.speedKmhChanged.connect(refresh)
