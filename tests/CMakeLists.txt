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

# Lex test 2 - math operations

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

# Lex test 3 - logical operations

add_executable ( # how to compile it
        lex_test3
        lex_test3.cpp
)

target_link_libraries( # link this object file with .so library
        lex_test3
        tpj-static
)

add_test ( # add binary to testsuite
        lex_test3 # name of the test
        lex_test3 # binary
)

# -------------------------------------------------------------------

# Lex test 4 - methods, other token types

add_executable ( # how to compile it
		lex_test4
		lex_test4.cpp
)

target_link_libraries( # link this object file with .so library
		lex_test4
		tpj-static
)

add_test ( # add binary to testsuite
		lex_test4 # name of the test
		lex_test4 # binary
)

# -------------------------------------------------------------------

# Lex test 5 - token values

add_executable ( # how to compile it
        lex_test5
        lex_test5.cpp
)

target_link_libraries( # link this object file with .so library
        lex_test5
        tpj-static
)

add_test ( # add binary to testsuite
        lex_test5 # name of the test
        lex_test5 # binary
)

# -------------------------------------------------------------------

# Lex test 6 - keywords

add_executable ( # how to compile it
        lex_test6
        lex_test6.cpp
)

target_link_libraries( # link this object file with .so library
        lex_test6
        tpj-static
)

add_test ( # add binary to testsuite
        lex_test6 # name of the test
        lex_test6 # binary
)

# -------------------------------------------------------------------

# Lex test 7 - strings

add_executable ( # how to compile it
        lex_test7
        lex_test7.cpp
)

target_link_libraries( # link this object file with .so library
        lex_test7
        tpj-static
)

add_test ( # add binary to testsuite
        lex_test7 # name of the test
        lex_test7 # binary
)

# -------------------------------------------------------------------

# Lex test 8 - comments

add_executable ( # how to compile it
        lex_test8
        lex_test8.cpp
        )

target_link_libraries( # link this object file with .so library
        lex_test8
        tpj-static
        )

add_test ( # add binary to testsuite
        lex_test8 # name of the test
        lex_test8 # binary
        )

# -------------------------------------------------------------------

# Lex test 9 - errors

add_executable ( # how to compile it
        lex_test9
        lex_test9.cpp
        )

target_link_libraries( # link this object file with .so library
        lex_test9
        tpj-static
        )

add_test ( # add binary to testsuite
        lex_test9 # name of the test
        lex_test9 # binary
        )

# -------------------------------------------------------------------

# Lex test 10 - example source program

add_executable ( # how to compile it
        lex_test10
        lex_test10.cpp
        )

target_link_libraries( # link this object file with .so library
        lex_test10
        tpj-static
        )

add_test ( # add binary to testsuite
        lex_test10 # name of the test
        lex_test10 # binary
        )

# -------------------------------------------------------------------

# Lex test 11 - pushback test

add_executable ( # how to compile it
		lex_test11
		lex_test11.cpp
		)

target_link_libraries( # link this object file with .so library
		lex_test11
		tpj-static
		)

add_test ( # add binary to testsuite
		lex_test11 # name of the test
		lex_test11 # binary
		)

# -------------------------------------------------------------------
