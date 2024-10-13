cmake_minimum_required(VERSION 3.16)

include(CMakePackageConfigHelpers)

project(esptk)

add_subdirectory(src)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/mo2-esptk-config.cmake"
  INSTALL_DESTINATION "lib/cmake/mo2-esptk"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/mo2-esptk-config-version.cmake"
  VERSION "1.3.12"
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/mo2-esptk-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/mo2-esptk-config-version.cmake
  DESTINATION lib/cmake/mo2-esptk
)
