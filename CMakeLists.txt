cmake_minimum_required(VERSION 3.5)

project(ProjetTemp)

configure_file(CMakeLists-googletest.txt googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
execute_process(COMMAND "${CMAKE_COMMAND}" --build . WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
 
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_SOURCE_DIR}/googletest" "${CMAKE_BINARY_DIR}/googletest-build")

set(mini_banque_VERSION_MAJOR "1")
set(mini_banque_VERSION_MINOR "0")

add_library(lib_mini_banque src/lib_mini_banque/Portefeuille.cpp)
target_compile_features(lib_mini_banque PUBLIC cxx_std_14)
target_include_directories(lib_mini_banque INTERFACE include)
target_include_directories(lib_mini_banque PRIVATE include/lib_mini_banque)

add_executable(mini_banque src/mini_banque/main.cpp)
target_compile_features(mini_banque PUBLIC cxx_std_14)
target_link_libraries(mini_banque lib_mini_banque)

install(TARGETS mini_banque DESTINATION bin)
install(FILES include/lib_mini_banque/Portefeuille.h DESTINATION include)

include (CTest)

add_executable(mini_banque_tests tests/PortefeuilleTests.cpp)
add_dependencies(mini_banque_tests gtest)
target_compile_features(mini_banque_tests PUBLIC cxx_std_14)
target_include_directories(mini_banque_tests PRIVATE include)
target_include_directories(mini_banque_tests PRIVATE ${googletest_INCLUDE_DIRS})
target_link_libraries(mini_banque_tests lib_mini_banque)
target_link_libraries(mini_banque_tests gtest)

include(GoogleTest)
gtest_add_tests(TARGET mini_banque_tests)

include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR "${mini_banque_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${mini_banque_VERSION_MINOR}")
include (CPack)

