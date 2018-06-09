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
include_directories(${CMAKE_CURRENT_BINARY_DIR}/DxLib/src/DxLib/プロジェクトに追加すべきファイル_VC用)
link_directories(C:/DxLib_VC/プロジェクトに追加すべきファイル_VC用)
link_directories(Libralies)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/DxLib/src/DxLib/プロジェクトに追加すべきファイル_VC用)

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/Resources)
file(COPY Resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resources)

include(ExternalProject)
ExternalProject_Add(
    DxLibGameFramework
    PREFIX "DxLibGameFramework"
    URL https://ydeagames.gitlab.io/DxLibGameFramework/DxLibGameFramework.tar.gz
    URL_HASH SHA512=151954a388597a338361e7c7a74b7d9e91086238aeb0a49cb0f591e2b27d8dba7ae47306845f1ea4251374b9195efb25661f0746cefe36ca689371fef0c955c3
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
ExternalProject_Add(
    DxLib
    PREFIX "DxLib"
    URL http://dxlib.o.oo7.jp/DxLib/DxLib_VC3_19b.zip
    URL_HASH SHA512=4d19f3aa752c53b92f8f077ebeaed1a82353a9687dcb482b57cdaafcc3c707f66e4d062ea0782055c11c2b984ba96625f9225cbb2913bbe679587481d2a5ab3e
    TMP_DIR "C:/DxLib_VC/DxLib-tmp"
    DOWNLOAD_DIR "C:/DxLib_VC/DxLib-dl"
    SOURCE_DIR "C:/DxLib_VC/DxLib-src"
    STAMP_DIR "C:/DxLib_VC/DxLib-stamp"
    BINARY_DIR "C:/DxLib_VC/DxLib-build"
    INSTALL_DIR "C:/DxLib_VC/プロジェクトに追加すべきファイル_VC用"
)