cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME Plastic_OpenGL)
project(${MODULE_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Remove the next line if MODULE_NAME is already correct
# get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)


file(GLOB_RECURSE LOCAL_SRC src/*.cpp src/*.c)
file(GLOB_RECURSE SHARED_SRC ${CMAKE_SOURCE_DIR}/Plastic_shared/src/*.cpp ${CMAKE_SOURCE_DIR}/Plastic_shared/src/*.c)

include_directories(
    ${CMAKE_SOURCE_DIR}/Plastic_shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.lib)
    file(GLOB LOCAL_LIBS lib/*.lib)
else()
    file(GLOB LOCAL_LIBS lib/*.a lib/*.o)
    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.a ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.o)
endif()

add_executable(${MODULE_NAME} ${LOCAL_SRC} ${SHARED_SRC})
set_target_properties(${MODULE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    OUTPUT_NAME ${MODULE_NAME}
)
target_link_libraries(${MODULE_NAME} ${SHARED_LIBS} ${LOCAL_LIBS})