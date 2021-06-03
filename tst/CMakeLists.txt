file(GLOB TEST_SOURCES *.hpp *.cpp)

set(SOURCES ${TEST_SOURCES})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BINARY ft_containers_tests)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY}
    PUBLIC gtest
    PUBLIC pthread
    )
