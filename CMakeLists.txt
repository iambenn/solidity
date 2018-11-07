cmake_minimum_required(VERSION 3.0.0)

set(ETH_CMAKE_DIR   "${CMAKE_CURRENT_LIST_DIR}/cmake"   CACHE PATH "The the path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${ETH_CMAKE_DIR})

# Set cmake_policies
include(EthPolicy)
eth_policy()

# CMake package manager
include(HunterGate)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.21.16.tar.gz"
    SHA1 "aa1faccd24f33dd2c368f85a4e9ca2e5d9c249cb"
    LOCAL
)

# project name and version should be set after cmake_policy CMP0048
set(PROJECT_VERSION "0.5.1")
project(solidity VERSION ${PROJECT_VERSION})

option(LLL "Build LLL" OFF)
option(SOLC_LINK_STATIC "Link solc executable statically on supported platforms" OFF)
option(LLLC_LINK_STATIC "Link lllc executable statically on supported platforms" OFF)
option(INSTALL_LLLC "Include lllc executable in installation" ${LLL})

# Setup cccache.
include(EthCcache)

# Let's find our dependencies
include(EthDependencies)
include(jsoncpp)
include_directories(SYSTEM ${JSONCPP_INCLUDE_DIR})

find_package(Threads)

# Figure out what compiler and system are we using
include(EthCompilerSettings)

# Include utils
include(EthUtils)

# Create license.h from LICENSE.txt and template
# Converting to char array is required due to MSVC's string size limit.
file(READ ${CMAKE_SOURCE_DIR}/LICENSE.txt LICENSE_TEXT HEX)
string(REGEX MATCHALL ".." LICENSE_TEXT "${LICENSE_TEXT}")
string(REGEX REPLACE ";" ",\n\t0x" LICENSE_TEXT "${LICENSE_TEXT}")
set(LICENSE_TEXT "0x${LICENSE_TEXT}")

configure_file("${CMAKE_SOURCE_DIR}/cmake/templates/license.h.in" include/license.h)

include(EthOptions)
configure_project(TESTS)

add_subdirectory(libdevcore)
add_subdirectory(liblangutil)
add_subdirectory(libevmasm)
add_subdirectory(libsolidity)
add_subdirectory(libsolc)

if (NOT EMSCRIPTEN)
	add_subdirectory(solc)
	if (LLL)
		add_subdirectory(liblll)
		add_subdirectory(lllc)
	endif()
endif()

if (TESTS AND NOT EMSCRIPTEN)
	add_subdirectory(test)
endif()
