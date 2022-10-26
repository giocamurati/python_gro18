# Python bindings [Gro18](https://hal.archives-ouvertes.fr/hal-02901386)

This repository provides Python bindings for the key rank estimation algorithm
proposed by Vincent Grosso at CARDIS18 [paper](https://hal.archives-ouvertes.fr/hal-02901386).
All credits for the development of this algorithm and library go to the original
author.
The coded provided in this repo is given without any guarantee of correctness
nor efficiency.

This project was developed to be used as baseline for 
[MCRank](https://github.com/giocamurati/mcrank).

Please feel free to contact us ([Giovanni Camurati](mailto://camurati@eurecom.fr)) for any comment, issue, or question.

# Index

* [Files](#Files)
* [Explanation](#Explanation)
* [Installation](#Installation)
* [Examples](#Examples)
* [License](#License)

## <a name="Files"></a>Files

```
.
├── LICENSE
├── README.md
├── lib # Original code turned into a library
│   ├── Makefile
│   ├── libgro18.cpp
│   └── libgro18.h
└── python_gro18 # This wrapper
    ├── python_gro18
    │   ├── __init__.py
    │   ├── example_data.py
    │   └── gro18.py
    └── setup.py
```

## <a name="Explanation"></a>Explanation

Please refer to the original [paper](https://hal.archives-ouvertes.fr/hal-02901386) for a detailed
explanation of the algorithm.

## <a name="Installation"></a>Installation

We tested this on Ubuntu22.04.

Requirements.
```
apt install libntl-dev
apt install libgmp-dev
```

Clone the repository.
```
git clone https://gitlab.eurecom.fr/montecarlo/python_gro18.git
cd python_gro18
```

Compile and install the library.
```
cd lib
make
sudo make install
sudo ldconfig
```

Run the following to uninstall.
```
sudo make uninstall
```

Then, you have to install the python module.
```
cd python_gro18/python_gro18
python3 setup.py install
# python3 setup.py install --user # To install locally instead of system wide
# python3 setup.py develop # To make changes to the source effective immediately
```

## <a name="Examples"></a>Examples

Quick test.
```
python3 python_gro18/python_gro18/gro18.py
```

This project was developed to be used as baseline for 
[MCRank](https://github.com/giocamurati/mcrank).
You can find more examples there.

## <a name="License"></a>License

Copyright (C) ETH Zurich
Copyright (C) Giovanni Camurati

Certain files in this project may have specific licenses or copyright
restrictions, as this project uses multiple open-source projects.
Files in this project without any specific license can be assumed
to follow the following general clause:

Python bindings for Gro18
is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Python bindings for Gro18
is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Python bindings for Gro18.
If not, see <http://www.gnu.org/licenses/>.


