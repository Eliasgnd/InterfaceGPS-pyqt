from __future__ import annotations

import os
import sys

from PyQt6.QtCore import QCoreApplication, Qt
from PyQt6.QtNetwork import QNetworkProxyFactory
from PyQt6.QtWidgets import QApplication

try:
    import resources_rc  # generated via: pyrcc6 resources.qrc -o resources_rc.py
except ImportError:
    resources_rc = None
from main_window import MainWindow
from mock_telemetry import MockTelemetrySource
from telemetry_data import TelemetryData


def main() -> int:
    QCoreApplication.setAttribute(Qt.ApplicationAttribute.AA_UseSoftwareOpenGL)
    app = QApplication(sys.argv)

    cache_path = os.path.join(QCoreApplication.applicationDirPath(), "qtlocation_cache")
    os.makedirs(cache_path, exist_ok=True)
    os.environ["QTLOCATION_OSM_CACHE_DIR"] = cache_path
    QNetworkProxyFactory.setUseSystemConfiguration(True)

    telemetry = TelemetryData()
    mock = MockTelemetrySource(telemetry)
    mock.start()

    window = MainWindow(telemetry)
    window.showFullScreen()
    return app.exec()


if __name__ == "__main__":
    raise SystemExit(main())
