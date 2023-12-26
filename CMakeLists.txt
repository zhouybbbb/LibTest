cmake_minimum_required(VERSION 3.20)

project(testlib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
add_subdirectory(qwindowkit)

add_library(testlib SHARED
  testlib_global.h
  testlib.cpp
  testlib.h
)


target_link_libraries(testlib PRIVATE Qt${QT_VERSION_MAJOR}::Core QWindowKit::Core)

target_compile_definitions(testlib PRIVATE TESTLIB_LIBRARY)

# add include directories
target_include_directories(testlib
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# install the target and create export-set
install(TARGETS testlib
        EXPORT testlibTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# install header file
#install(FILES MathFunctions.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# generate and install export file
install(EXPORT testlibTargets
        FILE testlibTargets.cmake
        NAMESPACE testlib::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/testlib
)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

# set version
set(version 3.4.1)

set_property(TARGET testlib PROPERTY VERSION ${version})
set_property(TARGET testlib PROPERTY SOVERSION 3)
set_property(TARGET testlib PROPERTY
  INTERFACE_testlib_MAJOR_VERSION 3)
set_property(TARGET testlib APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING testlib_MAJOR_VERSION
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/testlibConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/testlibConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/testlib
)

# install config files
install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/testlibConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/testlibConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/testlib
)

# generate the export targets for the build tree
export(EXPORT testlibTargets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/testlibTargets.cmake"
       NAMESPACE testlib::
)
