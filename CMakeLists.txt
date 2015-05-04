cmake_minimum_required( VERSION 2.8 )
project( Test_OpenCV )
find_package( OpenCV REQUIRED )

include_directories( "${CMAKE_SOURCE_DIR}/include" )

set( SRC_LIST src/main.cpp src/imageProcessor.cpp )
add_executable( test_opencv ${SRC_LIST} )
target_link_libraries( test_opencv ${OpenCV_LIBS} )
