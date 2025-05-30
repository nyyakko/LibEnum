function(enable_tests PROJECT)
    include(GoogleTest)

    if (NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
        message(STATUS "[${PROJECT}] running on ${CMAKE_HOST_SYSTEM_NAME}, sanitizers for tests are enabled.")
        set(LibEnum_TestsLinkerOptions ${LibEnum_TestsLinkerOptions} -fsanitize=undefined,leak,address)
    else()
        message(STATUS "[${PROJECT}] running on ${CMAKE_HOST_SYSTEM_NAME}, sanitizers for tests are disabled.")
    endif()

    set(LibEnum_TestsCompilerOptions ${LibEnum_TestsCompilerOptions} ${LibEnum_CompilerOptions})
    set(LibEnum_TestsLinkerOptions ${LibEnum_TestsLinkerOptions} ${LibEnum_LinkerOptions})

    CPMAddPackage(
        NAME googletest
        GITHUB_REPOSITORY google/googletest
        GIT_TAG release-1.12.1
        VERSION 1.12.1
        OPTIONS
            "INSTALL_GTEST OFF"
            "gtest_force_shared_crt"
    )

    enable_testing()
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endfunction()
