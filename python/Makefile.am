#python_PYTHON = mplib_ctypes.py

PYTHON = mplib_ctypes.py
install-exec-hook:
	mkdir -p `python3 -m site --user-site`
	cp $(PYTHON) `python3 -m site --user-site`
