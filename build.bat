del /s /q dist build BytesOp.egg-info
py -2 -m autopep8 --in-place setup.py test_bytesop.py
py -2 setup.py test
py -3 setup.py test
py -2 setup.py sdist
py -2 setup.py build bdist --plat-name=win32 bdist_wininst bdist_egg
py -2 setup.py build bdist --plat-name=win-amd64 bdist_wininst bdist_egg
py -2 setup.py bdist_wheel --plat-name=win32
py -2 setup.py bdist_wheel --plat-name=win-amd64
py -3 setup.py build bdist --plat-name=win32 bdist_wininst bdist_egg
py -3 setup.py build bdist --plat-name=win-amd64 bdist_wininst bdist_egg
py -3 setup.py bdist_wheel --plat-name=win32
py -3 setup.py bdist_wheel --plat-name=win-amd64
