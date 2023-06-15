# CMakeList.txt: проект CMake для RTS3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("RTS3")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (RTS3  "RTS3.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RTS3 PROPERTY C_STANDARD 11)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
