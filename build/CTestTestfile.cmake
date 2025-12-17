# CMake generated Testfile for 
# Source directory: /workspaces/Lab4
# Build directory: /workspaces/Lab4/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(LabsTests "/workspaces/Lab4/build/tests")
set_tests_properties(LabsTests PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/Lab4/CMakeLists.txt;40;add_test;/workspaces/Lab4/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
