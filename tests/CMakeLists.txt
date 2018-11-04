set(
	EXECUTABLE_OUTPUT_PATH
	.
)

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

# ObjPool test 1

add_executable ( # how to compile it
	objpool_test1
	objpool_test1.cpp
)

target_link_libraries( # link this object file with .so library
	objpool_test1
	tpj-shared
)

add_test ( # add binary to testsuite
	objpool_test1 # name of the test
	objpool_test1 # binary
)

# -------------------------------------------------------------------

# ObjPool test 2

add_executable ( # how to compile it
	objpool_test2
	objpool_test2.cpp
)

target_link_libraries( # link this object file with .so library
	objpool_test2
	tpj-shared
)

add_test ( # add binary to testsuite
	objpool_test2 # name of the test
	objpool_test2 # binary
)

# -------------------------------------------------------------------

# ObjPool test 2

add_executable ( # how to compile it
	objpool_test3
	objpool_test3.cpp
)

target_link_libraries( # link this object file with .so library
	objpool_test3
	tpj-shared
)

add_test ( # add binary to testsuite
	objpool_test3 # name of the test
	objpool_test3 # binary
)

# -------------------------------------------------------------------

# Lex test 1 - brackets

add_executable ( # how to compile it
		lex_test1
		lex_test1.cpp
)

target_link_libraries( # link this object file with .so library
		lex_test1
		tpj-static
)

add_test ( # add binary to testsuite
		lex_test1 # name of the test
		lex_test1 # binary
)

# -------------------------------------------------------------------

# Lex test 1 - math operations

add_executable ( # how to compile it
		lex_test2
		lex_test2.cpp
)

target_link_libraries( # link this object file with .so library
		lex_test2
		tpj-static
)

add_test ( # add binary to testsuite
		lex_test2 # name of the test
		lex_test2 # binary
)

# -------------------------------------------------------------------
