#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MIRACL::miracl" for configuration "Release"
set_property(TARGET MIRACL::miracl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MIRACL::miracl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libmiracl.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MIRACL::miracl )
list(APPEND _IMPORT_CHECK_FILES_FOR_MIRACL::miracl "${_IMPORT_PREFIX}/lib/libmiracl.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
