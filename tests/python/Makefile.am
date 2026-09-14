all:
	ln -s -f $(top_srcdir)/python/mplib_ctypes.py

EXTRA_DIST = conftest.py test_mplib.py reference_values.json

# Primary test suite (see conftest.py/test_mplib.py). Requires pytest;
# run `pip install pytest` if this fails with "No module named pytest".
check-local:
	LD_LIBRARY_PATH="$(abs_top_builddir)/lib/.libs:$$LD_LIBRARY_PATH" \
		$(PYTHON) -m pytest "$(srcdir)" -q
