from __future__ import annotations

import argparse
import sys
import os  # <--- AJOUT 1

from PyQt6.QtWidgets import QApplication
from PyQt6.QtCore import QLibraryInfo  # <--- AJOUT 2

try:
    import resources_rc
except Exception:
    resources_rc = None

from gps_source import GpsTelemetrySource
from main_window import MainWindow
from mock_source import MockTelemetrySource
from telemetry_data import TelemetryData


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="InterfaceGPS - version PyQt6")
    parser.add_argument("--mock", action="store_true", help="Force la source de télémétrie simulée")
    parser.add_argument("--serial-port", default="/dev/serial0", help="Port série GPS (défaut: /dev/serial0)")
    parser.add_argument("--baudrate", type=int, default=9600, help="Baudrate GPS (défaut: 9600)")
    return parser.parse_args()


def main() -> int:
    # --- DÉBUT DU CORRECTIF QML ---
    # On force le chemin des plugins pour être sûr que le QML trouve QtLocation
    os.environ["QT_PLUGIN_PATH"] = QLibraryInfo.path(QLibraryInfo.LibraryPath.PluginsPath)
    os.environ["QML_IMPORT_PATH"] = QLibraryInfo.path(QLibraryInfo.LibraryPath.QmlImportsPath)
    os.environ["QML2_IMPORT_PATH"] = QLibraryInfo.path(QLibraryInfo.LibraryPath.QmlImportsPath)
    # --- FIN DU CORRECTIF QML ---

    args = _parse_args()
    app = QApplication(sys.argv)

    telemetry = TelemetryData()
    # ... le reste du code reste identique ...
    window = MainWindow(telemetry)

    mock_source = MockTelemetrySource(telemetry, window)
    gps_source = GpsTelemetrySource(telemetry, window, port_name=args.serial_port, baud_rate=args.baudrate)

    using_mock = args.mock
    if not using_mock:
        using_mock = not gps_source.start()

    if using_mock:
        mock_source.start()
    else:
        telemetry.setAlertLevel(0)
        telemetry.setAlertText("")

    window.show()
    exit_code = app.exec()

    gps_source.stop()
    mock_source.stop()
    return exit_code


if __name__ == "__main__":
    raise SystemExit(main())
