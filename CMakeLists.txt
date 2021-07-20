cmake_minimum_required(VERSION 3.18)
project(cubes LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

message("Build type: ${CMAKE_BUILD_TYPE}")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
list(REMOVE_ITEM SRC_FILES ${SRC_DIR}/main.cpp)

set(SHARED_NAME "shared${PROJECT_NAME}")
set(EXE_NAME ${PROJECT_NAME})
set(TEST_NAME "test${PROJECT_NAME}")

add_library(${SHARED_NAME} STATIC ${SRC_FILES})
target_include_directories(${SHARED_NAME} PUBLIC ${INCLUDE_DIR})
if(NOT MSVC)
    target_compile_options(${SHARED_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Enabled trace logging and debug assertions")
    target_compile_definitions(${SHARED_NAME} PRIVATE ENABLE_LOG_TRACE ENABLE_DEBUG_ASSERT)
endif()

target_include_directories(${SHARED_NAME} PUBLIC ${LIB_DIR})

set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})
target_link_libraries(${SHARED_NAME} "glfw" ${GLFW_LIBRARIES})
target_include_directories(${SHARED_NAME} PUBLIC "${GLW_DIR}/include")
target_compile_definitions(${SHARED_NAME} PUBLIC "GLFW_INCLUDE_NONE")

set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${SHARED_NAME} PUBLIC "${GLAD_DIR}/include")
target_link_libraries(${SHARED_NAME} "glad" ${CMAKE_DL_LIBS})

set(GLM_DIR "${LIB_DIR}/glm")
target_include_directories(${SHARED_NAME} PUBLIC ${GLM_DIR})

set(NOISE_DIR "${LIB_DIR}/FastNoise2")
set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build noise tool" FORCE)
add_subdirectory(${NOISE_DIR})
target_link_libraries(${SHARED_NAME} "FastNoise")

add_executable(${EXE_NAME} ${SRC_DIR}/main.cpp)
target_link_libraries(${EXE_NAME} PRIVATE ${SHARED_NAME})

enable_testing()

file(GLOB_RECURSE TEST_FILES ${TEST_DIR}/*.cpp)

add_executable(${TEST_NAME} ${TEST_FILES})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

set(CATCH_DIR "${LIB_DIR}/catch")
target_include_directories(${TEST_NAME} PRIVATE ${CATCH_DIR})
