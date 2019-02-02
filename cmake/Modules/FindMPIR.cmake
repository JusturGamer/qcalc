#
# FindMPIR
# --------
#
# Find MPIR include dirs and libraries
#
# This module reads hint about search locations from variable:
#
#  MPIR_ROOT - Preferred installation prefix
#
# This script creates the following variables:
#
#  MPIR_FOUND         - Boolean that indicates if the package was found
#  MPIR_INCLUDE_DIRS  - Paths to the necessary header files
#  MPIR_LIBRARIES     - Package libraries
#  MPIR_VERSION       - MPIR version
#

# Find headers
find_path(MPIR_INCLUDE_DIR
          NAMES mpir.h
          HINTS $ENV{MPIR_ROOT} ${MPIR_ROOT}
          PATHS /usr/local /usr /opt/local
          PATH_SUFFIXES
            include
            dll/Win32/Debug/
            dll/Win32/Release/
            dll/x64/Debug/
            dll/x64/Release/
)

# Find libraries
find_library(MPIR_LIBRARY
              NAMES mpir
              HINTS $ENV{MPIR_ROOT} ${MPIR_ROOT}
              PATHS /usr/local /usr /opt/local
              PATH_SUFFIXES
                lib
                dll/Win32/Debug/
                dll/Win32/Release/
                dll/x64/Debug/
                dll/x64/Release/
)

# Set MPIR_FIND_VERSION to 1.0.0 if no minimum version is specified
if(NOT MPIR_FIND_VERSION)
  if(NOT MPIR_FIND_VERSION_MAJOR)
      set(MPIR_FIND_VERSION_MAJOR 1)
  endif()
  if(NOT MPIR_FIND_VERSION_MINOR)
      set(MPIR_FIND_VERSION_MINOR 0)
  endif()
  if(NOT MPIR_FIND_VERSION_PATCH)
      set(MPIR_FIND_VERSION_PATCH 0)
  endif()
  string(CONCAT MPIR_FIND_VERSION "${MPIR_FIND_VERSION_MAJOR}"
                                  ".${MPIR_FIND_VERSION_MINOR}"
                                  ".${MPIR_FIND_VERSION_PATCH}")
endif()

if(MPIR_INCLUDE_DIR)
  # Query MPIR_VERSION
  file(READ "${MPIR_INCLUDE_DIR}/mpir.h" _mpir_header)
  string(REGEX MATCH "define[ \t]+__MPIR_VERSION[ \t]+([0-9]+)"
          _mpir_major_version_match "${_mpir_header}")
  set(MPIR_MAJOR_VERSION "${CMAKE_MATCH_1}")
  string(REGEX MATCH "define[ \t]+__MPIR_VERSION_MINOR[ \t]+([0-9]+)"
          _mpir_minor_version_match "${_mpir_header}")
  set(MPIR_MINOR_VERSION "${CMAKE_MATCH_1}")
  string(REGEX MATCH "define[ \t]+__MPIR_VERSION_PATCHLEVEL[ \t]+([0-9]+)"
          _mpir_patchlevel_version_match "${_mpir_header}")
  set(MPIR_PATCHLEVEL_VERSION "${CMAKE_MATCH_1}")

  set(MPIR_VERSION
      ${MPIR_MAJOR_VERSION}.${MPIR_MINOR_VERSION}.${MPIR_PATCHLEVEL_VERSION})

  if(${MPIR_VERSION} VERSION_LESS ${MPIR_FIND_VERSION})
      set(MPIR_VERSION_OK FALSE)
      message(STATUS "MPIR version ${MPIR_VERSION} found in ${MPIR_INCLUDES}, "
              "but at least version ${MPIR_FIND_VERSION} is required")
  else()
      set(MPIR_VERSION_OK TRUE)
  endif()
endif()

# Set MPIR_FOUND honoring the QUIET and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  mpir
  DEFAULT_MSG
  MPIR_LIBRARY MPIR_INCLUDE_DIR MPIR_VERSION_OK
)

# Output variables
if(MPIR_FOUND)
  set(MPIR_INCLUDE_DIRS ${MPIR_INCLUDE_DIR})
  set(MPIR_LIBRARIES ${MPIR_LIBRARY})
endif()

# Replece all occurrenses of Win32, x64, Debug and Release by $(Platform) and
# $(Configuration) in MPIR_INCLUDE_DIRS and MPIR_LIBRARIES variables
if(MSVC)
  if(MPIR_FOUND)
      string(REGEX REPLACE "Win32" "$(Platform)"
              MPIR_INCLUDE_DIRS ${MPIR_INCLUDE_DIRS})
      string(REGEX REPLACE "x64" "$(Platform)"
              MPIR_INCLUDE_DIRS ${MPIR_INCLUDE_DIRS})
      string(REGEX REPLACE "Debug" "$(Configuration)"
              MPIR_INCLUDE_DIRS ${MPIR_INCLUDE_DIRS})
      string(REGEX REPLACE "Release" "$(Configuration)"
              MPIR_INCLUDE_DIRS ${MPIR_INCLUDE_DIRS})

      string(REGEX REPLACE "Win32" "$(Platform)"
              MPIR_LIBRARIES ${MPIR_LIBRARIES})
      string(REGEX REPLACE "x64" "$(Platform)"
              MPIR_LIBRARIES ${MPIR_LIBRARIES})
      string(REGEX REPLACE "Debug" "$(Configuration)"
              MPIR_LIBRARIES ${MPIR_LIBRARIES})
      string(REGEX REPLACE "Release" "$(Configuration)"
              MPIR_LIBRARIES ${MPIR_LIBRARIES})
  endif()
endif()

# Advanced options for not cluttering the cmake UIs:
mark_as_advanced(MPIR_INCLUDE_DIR MPIR_LIBRARY)
