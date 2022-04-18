cmake_minimum_required(VERSION 3.16)

add_library(esptk STATIC)
mo2_configure_library(esptk PRIVATE_DEPENDS boost)
mo2_install_target(esptk)
