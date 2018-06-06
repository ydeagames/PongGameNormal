cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

# Pong Project
set(PROJ_NAME Pong)
project(${PROJ_NAME})

file(GLOB_RECURSE SOURCES
	Libralies/*.h
	Libralies/*.cpp
	Game/*.h
	Game/*.cpp
	WinMain.cpp
)
add_executable(${PROJ_NAME} WIN32 ${SOURCES} Resources/Icon/Icon.rc)

if(MSVC)
	add_definitions(/FI"GameLibrary/GameLib.h")
	add_definitions(/FI"Utilities/MemoryLeakDetector.h")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
else()
	add_definitions(-include GameLibrary/GameLib.h)
	add_definitions(-include Utilities/MemoryLeakDetector.h)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

include_directories(C:/DxLib_VC/プロジェクトに追加すべきファイル_VC用)
include_directories(Libralies)
link_directories(C:/DxLib_VC/プロジェクトに追加すべきファイル_VC用)
link_directories(Libralies)

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/Resources)
file(COPY Resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resources)