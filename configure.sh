#!/bin/sh

# Add submodule if required
git submodule --quiet init
if [ $? -eq 1 ]; then
    echo "Unable to initialize git submodule for googletest"
    exit 1
else
    echo "Submodules initialised"
fi

if [ $# -gt 0 ]; then
    if [ $1 = "--show-output" ]; then
        mkdir -p ./build && cd build && cmake ../ -DDEFINE_OUTPUT=ON
    else
        echo "Unrecognised flag: " $1
    fi
else
        mkdir -p ./build && cd build && cmake ../
fi
