cmake_minimum_required(VERSION 3.0.0)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.8.x)

# For Windows: Prevent overriding the parent project's compiler/linker
# settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


function(setup_test_mosaic target)
    target_link_libraries(${target}
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::QuickControls2
        mosaic_engine 
        gtest
        $<$<BOOL:${WIN32}>:OpenGL32>)    
endfunction()




set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets QuickControls2 OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets QuickControls2 OpenGL)


add_library(test_utilities test_utilities/test_utilities.cpp)
target_link_directories(test_utilities PUBLIC test_utilities/)
target_link_libraries(test_utilities 
    PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::QuickControls2 
    mosaic_engine
    $<$<BOOL:${WIN32}>:OpenGL32>)


add_executable(badnesscomposite_test badnesscomposite_test/badnesscomposite_test.cpp)
setup_test_mosaic(badnesscomposite_test) 


add_executable(mosaicviewrenderer_test mosaicviewrenderer_test/mosaicviewrenderer_test.cpp)
setup_test_mosaic(mosaicviewrenderer_test)

