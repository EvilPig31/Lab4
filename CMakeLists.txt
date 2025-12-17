cmake_minimum_required(VERSION 3.10)
project(Labs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Создаем библиотеку из заголовочных файлов (шаблонные классы)
add_library(labs_lib INTERFACE)
target_include_directories(labs_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Основное приложение (если есть main.cpp)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(Labs_app main.cpp)
    target_link_libraries(Labs_app PRIVATE labs_lib)
endif()

# Тесты
enable_testing()

add_executable(tests test/tests1.cpp)
target_link_libraries(tests PRIVATE labs_lib gtest_main)

target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME LabsTests COMMAND tests)