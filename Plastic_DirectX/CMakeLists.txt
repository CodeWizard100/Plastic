cmake_minimum_required(VERSION 3.10)

project(Plastic_DirectX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    # Windows build:
    file(GLOB_RECURSE LOCAL_SRC src/*.cpp src/*.c)
    file(GLOB_RECURSE SHARED_SRC ${CMAKE_SOURCE_DIR}/Plastic_shared/src/*.cpp ${CMAKE_SOURCE_DIR}/Plastic_shared/src/*.c)

    include_directories(
        ${CMAKE_SOURCE_DIR}/Plastic_shared/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        SYSTEM "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.19041.0\\um"
    )

    file(GLOB SHARED_LIBS ${CMAKE_SOURCE_DIR}/Plastic_shared/lib/*.lib)
    file(GLOB LOCAL_LIBS lib/*.lib)

    add_executable(Plastic_DirectX ${LOCAL_SRC} ${SHARED_SRC})

    if(MSVC)
        target_compile_options(Plastic_DirectX PRIVATE /EHsc)
    endif()

    target_link_libraries(Plastic_DirectX
        ${SHARED_LIBS} ${LOCAL_LIBS}
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64/dxcompiler.lib"
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64/dxgi.lib"
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64/d3dcompiler.lib"
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64/d3d11.lib"
    )

else()

    add_executable(Plastic_DirectX linux.cpp)
endif()

# Post-build: copy files from 'copy' folder to output dir if it exists
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/copy")
    add_custom_command(TARGET Plastic_DirectX POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/copy"
            "$<TARGET_FILE_DIR:Plastic_DirectX>"
        COMMENT "Copying contents from 'copy' folder to output directory"
    )
endif()


set_target_properties(Plastic_DirectX PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    OUTPUT_NAME Plastic_DirectX
)
target_compile_definitions(Plastic_DirectX PRIVATE FALLBACK_PATH=\"$<TARGET_FILE_DIR:Plastic_DirectX>\")

