from setuptools import setup, Extension

module = Extension("bytesop", sources=["bytesop.cpp"]) 
setup( 
     name = "BytesOp", 
     version = "0.1", 
     description = "Module for bitwise operations on bytestrings.", 
     ext_modules = [module] 
     )