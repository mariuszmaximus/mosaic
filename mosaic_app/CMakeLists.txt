
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets QuickControls2 OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets QuickControls2 OpenGL)


add_executable(mosaic_app 

    main.cpp 
    qml.qrc
    imageprovider.cpp
    )
target_link_libraries(mosaic_app PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::QuickControls2 mosaic_engine
    $<$<BOOL:${WIN32}>:OpenGL32>)
target_include_directories(mosaic_app PRIVATE ./)