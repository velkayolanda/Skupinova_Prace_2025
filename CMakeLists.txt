cmake_minimum_required(VERSION 3.16)
project(Skupinova_Prace_2025)
set(CMAKE_CXX_STANDARD 17)

# Find all main.cpp files recursively
file(GLOB_RECURSE ALL_MAINS "*/main.cpp")

# Convert to relative paths for processing
set(MAIN_DIRS "")
foreach(MAIN_FILE IN LISTS ALL_MAINS)
    get_filename_component(MAIN_DIR ${MAIN_FILE} DIRECTORY)
    list(APPEND MAIN_DIRS ${MAIN_DIR})
endforeach()

# Process each main.cpp
foreach(MAIN_FILE IN LISTS ALL_MAINS)
    get_filename_component(PROG_DIR ${MAIN_FILE} DIRECTORY)

    # Get relative path for naming
    file(RELATIVE_PATH REL_DIR ${CMAKE_SOURCE_DIR} ${PROG_DIR})
    string(REPLACE "/" "_" EXEC_NAME ${REL_DIR})

    # Collect all .cpp files from this directory
    file(GLOB LOCAL_CPP "${PROG_DIR}/*.cpp")
    set(ALL_SOURCES ${LOCAL_CPP})

    # Get all subdirectories
    file(GLOB SUBDIRS LIST_DIRECTORIES true "${PROG_DIR}/*")

    foreach(SUBDIR IN LISTS SUBDIRS)
        if(IS_DIRECTORY ${SUBDIR})
            # Check if this subdirectory contains a main.cpp
            set(HAS_MAIN FALSE)
            foreach(OTHER_MAIN_DIR IN LISTS MAIN_DIRS)
                file(RELATIVE_PATH REL_CHECK ${SUBDIR} ${OTHER_MAIN_DIR})
                if(NOT REL_CHECK MATCHES "^\\.\\.")
                    set(HAS_MAIN TRUE)
                    break()
                endif()
            endforeach()

            # If no main.cpp, include all files recursively
            if(NOT HAS_MAIN)
                file(GLOB_RECURSE SUBDIR_CPP "${SUBDIR}/*.cpp")
                list(APPEND ALL_SOURCES ${SUBDIR_CPP})
            endif()
        endif()
    endforeach()

    # Remove duplicates
    list(REMOVE_DUPLICATES ALL_SOURCES)

    # Create executable
    if(ALL_SOURCES)
        add_executable(${EXEC_NAME} ${ALL_SOURCES})
        list(LENGTH ALL_SOURCES NUM_FILES)
        message(STATUS "Executable: ${EXEC_NAME} (${NUM_FILES} files)")
    endif()
endforeach()