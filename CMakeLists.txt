cmake_minimum_required(VERSION 3.10)

PROJECT(ovpn-convert C)
INCLUDE(GNUInstallDirs)
SET(OVPN_CONVERT_VERSION 0.9.0)

ADD_DEFINITIONS(-Wall -Werror --std=gnu99 -D_GNU_SOURCE)
ADD_DEFINITIONS(-DOVPN_CONVERT_VERSION="${OVPN_CONVERT_VERSION}")

ADD_DEFINITIONS(-DGETTEXT_LOCALEDIR="${CMAKE_INSTALL_LOCALEDIR}")
ADD_DEFINITIONS(-DGETTEXT_PACKAGE="${PROJECT_NAME}")

FIND_LIBRARY(json-c NAMES libjson-c)

INCLUDE_DIRECTORIES(src)

SET(SOURCES
	src/main.c
	src/ovpn.c
	src/ovpn-parse.c
	src/ovpn-options.c
)

ADD_EXECUTABLE(ovpn-convert ${SOURCES})

TARGET_LINK_LIBRARIES(ovpn-convert json-c)

INSTALL(TARGETS ovpn-convert RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

ADD_SUBDIRECTORY(po)
