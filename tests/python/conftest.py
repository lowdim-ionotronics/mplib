import os
import sys

_PYTHON_DIR = os.path.join(os.path.dirname(__file__), "..", "..", "python")
sys.path.insert(0, os.path.abspath(_PYTHON_DIR))

try:
    import mplib_ctypes  # noqa: F401
except OSError as e:
    import pytest
    pytest.exit(
        "Could not load libmplib.so (%s). Build it first (./configure && make "
        "in the repo root) and make sure it's on LD_LIBRARY_PATH, or run "
        "`make install` and set LD_LIBRARY_PATH to the install prefix's lib/."
        % e,
        returncode=1,
    )
