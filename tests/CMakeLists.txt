set(EXECUTABLE_OUTPUT_PATH .)

# example how to create test with shared library

add_executable ( # how to compile it
	dummy_test1
	dummy_test.cpp
)

target_link_libraries( # link this object file with .so library
	dummy_test1
	tpj-shared
)

add_test ( # add binary to testsuite
	dynamic_linking # name of the test
	dummy_test1 # binary
)

# example how to create test with static library

add_executable ( # how to compile it
	dummy_test2
	dummy_test.cpp
)

target_link_libraries( # link this object file with .a library
	dummy_test2
	tpj-static
)

add_test ( # add binary to testsuite
	static_linking # name of the test
	dummy_test2 # binary
)

# --------------------------------------------------------------------