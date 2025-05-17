cmake_minimum_required(VERSION 3.16)
project(Plastic)

set(CMAKE_CXX_STANDARD 20)

set(BIN_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})

option(BUILD_AS_EXECUTABLE "Build targets as executables instead of libraries" OFF)

function(copy_folder src dest)
    if(EXISTS ${src})
        file(MAKE_DIRECTORY ${dest})
        file(GLOB_RECURSE files_to_copy
            RELATIVE ${src}
            ${src}/*
        )
        foreach(f ${files_to_copy})
            set(src_file "${src}/${f}")
            set(dest_file "${dest}/${f}")
            get_filename_component(dest_dir "${dest_file}" DIRECTORY)
            file(MAKE_DIRECTORY "${dest_dir}")
            file(COPY "${src_file}" DESTINATION "${dest_dir}")
        endforeach()
    endif()
endfunction()

# Add Plastic_shared only if building libraries (not executables)
if(NOT BUILD_AS_EXECUTABLE)
    add_subdirectory(Plastic_shared)

    # Copy include and lib folders for Plastic_shared
    copy_folder(${CMAKE_SOURCE_DIR}/Plastic_shared/include ${BIN_DIR}/Plastic_shared_includes)
    copy_folder(${CMAKE_SOURCE_DIR}/Plastic_shared/lib ${BIN_DIR}/Plastic_shared_libs)
endif()

# Process other Plastic_* folders except Plastic_shared
file(GLOB children RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Plastic_*)
foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${child} AND NOT ${child} STREQUAL "Plastic_shared")
        add_subdirectory(${child})

        # Copy includes/libs to build/bin folders for each module
        copy_folder(${CMAKE_SOURCE_DIR}/${child}/include ${BIN_DIR}/${child}_includes)
        copy_folder(${CMAKE_SOURCE_DIR}/${child}/lib ${BIN_DIR}/${child}_libs)
    endif()
endforeach()
