try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

setup(
    name = "TokenParser",
    version = "0.1",
    author = "Tyurin Anton",
    author_email = "noxiouz@yandex.ru",
    ext_modules = [Extension("_tokenparser",
                             ["src/tokenparser.cpp","src/module.cpp"],
                             include_dirs = ["include"])]
)
