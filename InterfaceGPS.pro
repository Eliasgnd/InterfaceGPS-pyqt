TEMPLATE = aux
CONFIG += ordered

TARGET = InterfaceGPS

# Fichiers Python
SOURCES += \
    main.py \
    main_window.py \
    gps_source.py \
    mock_source.py \
    telemetry_data.py \
    build_resources.py \
    resources_rc.py \
    pages/home_page.py \
    pages/navigation_page.py \
    pages/settings_page.py \
    pages/camera_page.py \
    pages/__init__.py

# Fichiers Qt Designer
FORMS += \
    mainwindow.ui \
    homepage.ui \
    navigationpage.ui \
    settingspage.ui \
    camerapage.ui

# Ressources Qt
RESOURCES += resources.qrc

# Fichiers additionnels
DISTFILES += \
    map.qml \
    dir_arrival.svg \
    dir_left.svg \
    dir_right.svg \
    dir_slight_left.svg \
    dir_slight_right.svg \
    dir_straight.svg \
    dir_uturn.svg \
    rond_point.svg
