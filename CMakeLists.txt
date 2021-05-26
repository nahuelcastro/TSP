cmake_minimum_required(VERSION 3.8)
project(tp2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake") 

file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/cpp/*.cpp" "${PROJECT_SOURCE_DIR}/cpp/*.h")
list(REMOVE_ITEM SOURCE_FILES 
	"${PROJECT_SOURCE_DIR}/cpp/main.cpp"
	)

add_executable(tp2 "${PROJECT_SOURCE_DIR}/cpp/main.cpp" ${SOURCE_FILES})

target_link_libraries(tp2)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-g")
