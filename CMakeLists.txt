cmake_minimum_required(VERSION 3.25)

project(LibEnum LANGUAGES CXX)

include(cmake/get_cpm.cmake)
include(GNUInstallDirs)

# CPMAddPackage("gh:repo/package1#REF")
# CPMAddPackage("gh:repo/package2#REF")

include(cmake/static_analyzers.cmake)
include(cmake/enable_tests.cmake)

if (ENABLE_TESTING)
    enable_tests(${PROJECT_NAME})
endif()

# set(LibEnum_CompilerOptions ${LibEnum_CompilerOptions})
# set(LibEnum_LinkerOptions ${LibEnum_LinkerOptions})

# set(LibEnum_ExternalLibraries package1 package2 ...)

add_subdirectory(LibEnum)

