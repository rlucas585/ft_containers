#!/bin/sh

# Check to see if submodules are initialised, and initialise if required.
cat .gitmodules | grep "external/googletest" > /dev/null
if [ $? -eq 1 ]; then
    git submodule add https://github.com/google/googletest.git external/googletest
    if [ $? -eq 1 ]; then
        echo "Unable to initialize git submodule for googletest"
        exit 1
    fi
else
    echo "Submodules are already initialised"
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
