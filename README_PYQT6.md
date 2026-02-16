# Portage Python (PyQt6)

## Prérequis

```bash
python -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

## Génération des ressources Qt

Compiler le `.qrc` pour Python :

```bash
pyrcc6 resources.qrc -o resources_rc.py
```

Le code Python importe ensuite ce module : `import resources_rc`.

## (Option alternative) Conversion des `.ui`

Le projet charge les interfaces dynamiquement via `uic.loadUi(...)`.
Si vous préférez une conversion statique :

```bash
pyuic6 mainwindow.ui -o ui_mainwindow.py
pyuic6 homepage.ui -o ui_homepage.py
pyuic6 navigationpage.ui -o ui_navigationpage.py
pyuic6 camerapage.ui -o ui_camerapage.py
pyuic6 settingspage.ui -o ui_settingspage.py
```

## Variables d'environnement (QML map)

```bash
export MAPBOX_API_KEY="..."
export HERE_API_KEY="..."
```

Ces clés sont injectées dans `map.qml` via le `rootContext()` du `QQuickWidget`.

## Lancement

```bash
python main.py
```
