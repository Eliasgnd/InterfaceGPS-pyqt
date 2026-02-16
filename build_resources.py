from __future__ import annotations

import shutil
import subprocess
import sys


def main() -> int:
    cmd = shutil.which("pyrcc6")
    if cmd:
        subprocess.check_call([cmd, "resources.qrc", "-o", "resources_rc.py"])
        return 0

    try:
        subprocess.check_call([sys.executable, "-m", "PyQt6.pyrcc_main", "resources.qrc", "-o", "resources_rc.py"])
        return 0
    except subprocess.CalledProcessError:
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
