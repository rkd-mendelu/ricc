include_directories( ${PROJECT_SOURCE_DIR}/src/library )

set(
	EXECUTABLE_OUTPUT_PATH
	.
)

# example how to create test with shared library

add_executable ( # how to compile it
	curl_json_test
        curl_json_test.cpp
)

target_link_libraries( # link this object file with .so library
        curl_json_test
        curlpp
)

add_test ( # add binary to testsuite
	curl_json_test # name of the test
	curl_json_test # binary
)
