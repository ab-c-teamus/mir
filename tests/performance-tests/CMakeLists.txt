mir_add_wrapped_executable(mir_performance_tests
    test_glmark2-es2.cpp
    test_compositor.cpp
    system_performance_test.cpp
)

target_link_libraries(mir_performance_tests
  mir-test-assist
)

add_dependencies(mir_performance_tests GMock)

add_custom_target(mir-smoke-test-runner ALL
    cp ${PROJECT_SOURCE_DIR}/tools/mir-smoke-test-runner.sh ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mir-smoke-test-runner
)

install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mir-smoke-test-runner
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

mir_add_test(NAME mir_performance_tests
    COMMAND "xvfb-run" "--server-num=98" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mir_performance_tests"
)

mir_add_test(NAME mir-smoke-test-runner
    COMMAND "xvfb-run" "--server-num=97" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mir-smoke-test-runner"
)