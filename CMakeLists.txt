cmake_minimum_required(VERSION 3.2)

set(PROJ_NAME bulk)
set(TESTS_NAME bulk_tests)
set(SRC ${CMAKE_BINARY_DIR}/../src)
set(INCLUDE ${CMAKE_BINARY_DIR}/../include)
set(TESTS ${CMAKE_BINARY_DIR}/../tests)


# set version
if($ENV{TRAVIS_BUILD_NUMBER})
    project(${PROJ_NAME} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${PROJ_NAME} VERSION 0.0.42)
endif()

configure_file(description.json.in description.json)

find_package(GTest REQUIRED)

include_directories(
    ${INCLUDE}
    ${GTEST_INCLUDE_DIRS}
)   

add_executable(${PROJ_NAME} 
    ${SRC}/main.cpp
    ${SRC}/CommandHandler.cpp
    ${SRC}/CommandReader.cpp
    ${SRC}/CommandPool.cpp
    ${SRC}/Logger.cpp
    ${INCLUDE}/CommandHandler.hpp
    ${INCLUDE}/CommandReader.hpp
    ${INCLUDE}/CommandPool.hpp
    ${INCLUDE}/Logger.hpp
)
add_executable(${TESTS_NAME} 
    ${TESTS}/tests.cpp
    ${SRC}/CommandHandler.cpp
    ${SRC}/CommandReader.cpp
    ${SRC}/CommandPool.cpp
    ${SRC}/Logger.cpp
    ${INCLUDE}/CommandHandler.hpp
    ${INCLUDE}/CommandReader.hpp
    ${INCLUDE}/CommandPool.hpp
    ${INCLUDE}/Logger.hpp
)

set_target_properties(${PROJ_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    ${PROJ_NAME} PRIVATE
    stdc++fs
)
target_link_libraries(
    ${TESTS_NAME} PRIVATE
    ${GTEST_LIBRARIES}
    stdc++fs
    pthread
    gtest
    gtest_main
)

if(MSVC)
    target_compile_options(${PROJ_NAME} PRIVATE
        /W4
    )
    target_compile_options(${TESTS_NAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${PROJ_NAME} PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
    target_compile_options(${TESTS_NAME} PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
endif()

# packaging
install(TARGETS ${PROJ_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

# testing
enable_testing()
add_test(${TESTS_NAME} ${TESTS_NAME})