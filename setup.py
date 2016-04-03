from setuptools import setup, Extension

module = Extension("bytesop", sources=["bytesop.cpp"])
setup(
    name="BytesOp",
    author="Jan Brohl",
    author_email="janbrohl@t-online.de",
    url="https://github.com/janbrohl/BytesOp",
    version="0.3",
    description="Module for bitwise operations on bytestrings.",
    ext_modules=[module]
)
