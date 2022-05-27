# This project was set up on v3.21.3, although may work on earlier versions
# depending on when some of the features were introduced
cmake_minimum_required(VERSION 3.21.3)

project(LoginProject VERSION 1.0.0 LANGUAGES CXX)

# Project wide setup
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

include_directories(include)

add_executable(
	${PROJECT_NAME}
	src/loginProject/user.cpp
	src/loginProject/system.cpp
	src/loginProject/systemManager.cpp
	src/loginProject/main.cpp
	)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Set the IDE structure to match the folder structure
get_target_property(sources ${PROJECT_NAME} SOURCES)

source_group(
	TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${sources}
	)

# Set the startup project for Visual Studio
if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

