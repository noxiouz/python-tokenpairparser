try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

setup(
    name = "Tokenparser",
    version = "0.2",
    author = "noxiouz",
    license="GPL2",
    description="Fast string parser",
    long_description="Fast string parsing based on Boost.Spirit",
    url="https://github.com/noxiouz/python-Tokenpair-parser-on-C-API",
    author_email = "noxiouz@yandex.ru",
    packages=["Tokenparser"],
    ext_modules = [Extension("Tokenparser/_tokenparser",
                             ["src/tokenparser.cpp","src/module.cpp"],
                             include_dirs = ["include"])]
)
