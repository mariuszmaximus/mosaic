

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets QuickControls2)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets QuickControls2)

add_library(mosaic_engine
    badnesscomposite.cpp 
    evolutionrunner.cpp 
    imageutilities.cpp
    interactionhelpers.cpp 
    interactiontileborder.cpp 
    interactiontiletile.cpp 
    lennardjones.cpp 
    maindriver.cpp 
    mosaicevolution.cpp mosaicupdate.cpp 
    mosaicmodel.cpp 
    mosaicrenderer.cpp 
    mosaicupdatedelay.cpp 
    mosaicupdateoptimize.cpp 
    mosaicview.cpp 
    potentiallennardjones.cpp 
    sourceimages.cpp 
    targetimage.cpp 
    thumbnail.cpp 
    tile.cpp 
    tiletextures.cpp 
    engine_resources.qrc
)

target_include_directories(mosaic_engine PUBLIC ./)

target_link_libraries(mosaic_engine  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::QuickControls2)