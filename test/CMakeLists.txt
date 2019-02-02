set(TESTS parser_test.cpp)

include_directories(../src)

add_executable(runUnitTests ${TESTS})
target_link_libraries(runUnitTests core gtest gmock gtest_main gmock_main
                      ${MPFR_LIBRARIES} ${MPIR_LIBRARIES})
add_test(runUnitTests runUnitTests)
