from __future__ import annotations
import subprocess
import sys
import shutil
import os
from pathlib import Path

def main() -> int:
    # 1. Liste des outils à chercher
    tools = ["pyrcc6.exe", "pyside6-rcc.exe", "pyrcc6", "pyside6-rcc"]
    cmd = None

    # 2. Dossiers de recherche (Système, Local et Roaming)
    search_dirs = [
        Path(sys.executable).parent / "Scripts", # Local (Standard)
        Path(os.environ.get("APPDATA", "")) / "Python" / f"Python{sys.version_info.major}{sys.version_info.minor}" / "Scripts", # Roaming (User)
    ]

    # 3. Recherche de l'outil
    for tool in tools:
        # Essai via le PATH global
        cmd = shutil.which(tool)
        if cmd: break

        # Essai dans les dossiers spécifiques
        for s_dir in search_dirs:
            if (s_dir / tool).exists():
                cmd = str(s_dir / tool)
                break
        if cmd: break

    if not cmd:
        print("ERREUR : Aucun outil trouvé dans :")
        for d in search_dirs: print(f" - {d}")
        return 1

    print(f"Outil détecté : {cmd}")
    try:
        # Génération du fichier
        subprocess.check_call([cmd, "resources.qrc", "-o", "resources_rc.py"])

        # Si on a utilisé l'outil PySide, on corrige l'import pour PyQt6
        if "pyside6" in cmd.lower():
            res_file = Path("resources_rc.py")
            content = res_file.read_text(encoding="utf-8")
            content = content.replace("from PySide6", "from PyQt6")
            res_file.write_text(content, encoding="utf-8")
            print("Correction : Import PySide6 converti en PyQt6.")

        print("Succès : resources_rc.py a été généré.")
        return 0
    except Exception as e:
        print(f"Erreur technique : {e}")
        return 1

if __name__ == "__main__":
    sys.exit(main())
