set(EXECUTABLE_OUTPUT_PATH .)

#example
add_executable ( # how to compile it
	dummy_test
	dummy_test.cpp
)

add_test ( # add binary to testsuite
	test_name # name of the test
	dummy_test # binary
)
