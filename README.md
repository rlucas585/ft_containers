# ft_containers

## About the project

This project is from the 42 school curriculum. The aim of this project
was to re-implement from scratch, 5 containers from the C++ standard
template library. All containers were re-implemented in C++98, and have
the same functionality as the containers from C++98 (ie, no move
semantics, missing some member functions from modern C++).

The containers re-implemented are:
* vector
* list
* map
* stack
* queue

All containers were defined under the `ft` namespace, so that the
following code should produce identical results:
```
ft::vector<int> vec;
std::vector<int> real_vec;

for (int i = 0; i < 30; i += 4) {
  vec.push_back(i);
  real_vec.push_back(i);
}

ft::vector<int>::const_iterator it = vec.begin();
std::vector<int>::const_iterator real_it = real_vec.begin();

// Output should be identical for both containers.
for (; it != vec.end(); ++it, ++real_it) {
  std::cout << "vec: " << *it << ", real_vec: " << *real_it << std::endl;
}
```

Memory footprint is identical to that of standard library containers.
Performance of operations on the containers has not been benchmarked for
speed yet, but `ft::map` in particular is implemented as a Red-Black
Binary Tree for efficiency and speed, rather than a basic binary tree
or simply wrapping a vector.

Tests for this project were created with GoogleTest - and include a
number of TYPED_TEST_SUITE directives - meaning that tests will be run
for `int`, `std::string`, and an `Example` class for all containers.

## Getting Started

### Prerequisites

**Required only for testing** - The containers in this project are
header-only, and can be simply used with a C++ compiler (An example can
be seen in the Usage section).
The tests associated with the containers however are easiest to compile
using CMake (version 3.10.2). To install CMake (or update if required):

1. Visit https://cmake.org/download/ and download the latest binaries.
2. Run `tar xzvf cmake-<version>.tar.gz` with your CMake version.
3. Following the instructions in CMake's README, run
`./bootstrap && make && sudo make install` to install CMake from source.
4. Check `cmake --version` to confirm successful installation.

### Installation

`ft_containers` comes with an assortment of shell scripts to make the
compilation of a basic executable or tests very simple.

To prepare `build` directory and project Makefiles:
```
./configure.sh                    # No printed output from test executable
./configure.sh --show-output      # Print test output
```

To compile the mock executable and tests:
```
./build.sh
```

To run the executable:
```
./run.sh
```

To run all tests, or a subset of tests:
```
./test.sh                                   # Run all tests
./test.sh --gtest_filter="map_tester/*"     # Run all ft::map tests
./test.sh --gtest_filter="list_tester/*"    # Run all ft::list tests
./test.sh --gtest_filter="vector_tester/*"  # Run all ft::vector tests
```
Click
[here](https://github.com/google/googletest/blob/master/docs/advanced.md#running-a-subset-of-the-tests)
for a detailed explanation of how to run a subset of tests.

To remove all compiled tests and executable:
```
rm -rf build
```

To remove all compiled tests, executable, and deinitialise the
googletest submodule:
```
./clean.sh
```

## Usage

Using ft_containers is another project is very simple. Simply `#include`
the path to whichever container you'd like, or use the `-I` flag during
compilation.

For example, in a directory structure like this:
```
.
├── ft_containers
└── test.cpp
```

Then the following code in `test.cpp` will compile:
```
#include <iostream>
#include "ft_containers/src/vector.hpp"

int main(void) {
    ft::vector<int> vec;

    for (int i = 0; i < 30; i += 4)
        vec.push_back(i);
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << ", ";
    std::cout << std::endl;
    return 0;
}
```

## Authors

Ryan Lucas - ryanl585codam@gmail.com

## Acknowledgements

* [GoogleTest](https://github.com/google/googletest)
* [CMake](https://cmake.org/)

