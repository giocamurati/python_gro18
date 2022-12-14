from setuptools import setup, find_packages

setup(
    name="gro18",
    version="1.0",
    packages=find_packages(),
    python_requires=">=2.7,!=3.0.*,!=3.1.*,!=3.2.*,!=3.3.*",
    install_requires=[
        "numpy",
    ],

    author="Giovanni Camurati",
    author_email="camurati@eurecom.fr",
    description="Python bindings for Grosso's improvement of HEL",
    license="GNU General Public License v3.0"
)
