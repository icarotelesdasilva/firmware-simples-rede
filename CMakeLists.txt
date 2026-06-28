cmake_minimum_required(VERSION 3.16)

# Adiciona a pasta ferramentas como um diretório extra de componentes
list(APPEND EXTRA_COMPONENT_DIRS "ferramentas")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(firmware)
