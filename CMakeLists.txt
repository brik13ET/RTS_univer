# CMakeList.txt: проект CMake для RTS3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("RTS3")
project ("RTS4")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (RTS3  "${CMAKE_SOURCE_DIR}/lab3/main.c")
add_executable (RTS4  "${CMAKE_SOURCE_DIR}/lab4/main.c" "lab4/matr.c" "lab4/arr.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_target_properties(RTS3
	  PROPERTIES
	  C_STANDARD 11
	  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lab3"
	)
	set_target_properties(RTS4
	  PROPERTIES
	  C_STANDARD 11
	  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lab4"
	  INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/lab4"
	)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
