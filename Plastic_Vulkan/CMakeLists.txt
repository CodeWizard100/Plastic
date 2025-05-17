# Get folder name as unique target
set(MODULE_NAME "Plastic_Vulkan")

# Source files
file(GLOB_RECURSE LOCAL_SRC src/*.cpp src/*.c)
file(GLOB_RECURSE SHARED_SRC ${CMAKE_SOURCE_DIR}/Plastic_shared/src/*.cpp ${CMAKE_SOURCE_DIR}/Plastic_shared/src/*.c)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/Plastic_shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link platform-specific precompiled libs from shared/lib/
if(WIN32)
    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.lib)
else()
    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.a ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.o)
endif()

# Create the executable
add_executable(${MODULE_NAME} ${LOCAL_SRC} ${SHARED_SRC} ${SHARED_LIBS})
