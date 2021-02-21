cmake_minimum_required(VERSION 3.1)
project(opengltemplate LANGUAGES CXX C)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
if(NOT MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE "${GLW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" ${CMAKE_DL_LIBS})

set(GLM_DIR "${LIB_DIR}/glm")
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_DIR})
