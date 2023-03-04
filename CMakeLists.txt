cmake_minimum_required(VERSION 3.0.0)
project(mosaic VERSION 0.1.0)

add_subdirectory("thirdparty/googletest-release-1.7.0")
add_subdirectory("mosaic_engine")
add_subdirectory("mosaic_app")
add_subdirectory("mosaic_cmd")


add_subdirectory("tests")
