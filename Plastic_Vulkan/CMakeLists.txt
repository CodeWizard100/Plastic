cmake_minimum_required(VERSION 3.5)
project(Plastic_Vulkan)

set(MODULE_NAME "Plastic_Vulkan")

file(GLOB_RECURSE LOCAL_SRC src/*.cpp src/*.c)
file(GLOB_RECURSE SHARED_SRC ${CMAKE_SOURCE_DIR}/Plastic_shared/src/*.cpp ${CMAKE_SOURCE_DIR}/Plastic_shared/src/*.c)

include_directories(
    ${CMAKE_SOURCE_DIR}/Plastic_shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.lib)
else()
    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.a ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.o)
endif()

if(WIN32)
    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.lib)
    file(GLOB LOCAL_LIBS ${CMAKE_SOURCE_DIR}/${MODULE_NAME}/lib/*.lib)
else()
    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.a ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.o)
    file(GLOB LOCAL_LIBS ${CMAKE_SOURCE_DIR}/${MODULE_NAME}/lib/*.a ${CMAKE_SOURCE_DIR}/${MODULE_NAME}/lib/*.o)
endif()

message(STATUS "Building module: ${MODULE_NAME}")

add_executable(${MODULE_NAME} ${LOCAL_SRC} ${SHARED_SRC})

target_link_libraries(${MODULE_NAME} ${SHARED_LIBS} ${LOCAL_LIBS})
set_target_properties(${MODULE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)