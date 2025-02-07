set(TEST_SOURCES
        TesteurReseau.cpp
        ${PROJECT_SOURCE_DIR}/ContratException.cpp
        ${PROJECT_SOURCE_DIR}/Routeur.cpp
        ${PROJECT_SOURCE_DIR}/Reseau.cpp
)

add_executable(TesteurReseau ${TEST_SOURCES})

target_include_directories(TesteurReseau PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(TesteurReseau gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(TesteurReseau)
add_custom_command(
        TARGET TesteurReseau POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/trace.txt
        $<TARGET_FILE_DIR:TesteurReseau>
)

add_custom_command(
        TARGET TesteurReseau POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/traceFC.txt
        $<TARGET_FILE_DIR:TesteurReseau>
)
