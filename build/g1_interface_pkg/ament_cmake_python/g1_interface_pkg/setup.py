from setuptools import find_packages
from setuptools import setup

setup(
    name='g1_interface_pkg',
    version='0.1.0',
    packages=find_packages(
        include=('g1_interface_pkg', 'g1_interface_pkg.*')),
)
