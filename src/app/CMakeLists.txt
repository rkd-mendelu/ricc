include_directories( ${PROJECT_SOURCE_DIR}/src/app )

set(
    APP_SOURCES
    ricc.cpp
)

add_executable(
    ricc
    ${APP_SOURCES}
)

target_link_libraries(
    ricc
    ricc-shared
)

install(
    TARGETS
    ricc
    DESTINATION
    bin
)
