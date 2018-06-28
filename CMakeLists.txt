cmake_minimum_required(VERSION 2.6)
project(nicegl-test)

set(CMAKE_CXX_STANDARD 11)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories( 
	. 
	include/
    vendor/glad/include/
	vendor/glm/
	vendor/stb
	vendor/imgui/include
)

file(GLOB VENDORS_SOURCES 
    vendor/glad/src/glad.c
	vendor/imgui/src/*.cpp
)
file(GLOB PROJECT_HEADERS *.h include/*.h nicegl/*.h) 
file(GLOB PROJECT_SOURCES *.cpp)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${VENDORS_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME} 
    ${GLAD_LIBRARIES}
    glfw 
    ${GLFW_LIBRARIES} 
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw ${CMAKE_CURRENT_BINARY_DIR}/dependencies/glfw)
