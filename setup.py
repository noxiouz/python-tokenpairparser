try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

setup(
    name = "TokenParser",
    version = "0.1",
    #description = "Cocaine Python Framework",
    #long_description = "A simple framework to ease the development of Cocaine apps",
    #url = "https://github.com/cocaine/cocaine-framework-python",
    author = "Tyurin Anton",
    author_email = "noxiouz@yandex.ru",
    #license = "BSD 2-Clause",
    #platforms = ["Linux", "BSD", "MacOS"],
    #packages = ["cocaine", "cocaine.decorators"],
    ext_modules = [Extension("_tokenparser",
                             ["src/tokenparser.cpp","src/module.cpp"],
                             include_dirs = ["include"])]
)
