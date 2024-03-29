cmake_minimum_required(VERSION 3.10.2)

project(FT_Containers VERSION 1.0)

enable_testing()

# Set Project Scoped definitions

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

# DOWNLOAD ALL GIT SUBMODULES
find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if (GIT_SUBMODULE)
		message(STATUS "Submodule update")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if (NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init --recursive"
			"failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif()
	endif()
endif()

# CHECK ALL SUBMODULES
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/googletest/CMakeLists.txt")
	message(FATAL_ERROR "The googletest submodules was not downloaded!"
		" GIT_SUBMODULE was turned off or failed.")
endif()

# Manage preprocessor defines

OPTION(DEFINE_OUTPUT "Print output from tests" OFF) # Disabled by default

IF(DEFINE_OUTPUT)
    ADD_DEFINITIONS(-DPRINTED_OUTPUT)
ENDIF(DEFINE_OUTPUT)

# Configure project

add_subdirectory(src)

include_directories(src)

add_subdirectory(tst)
