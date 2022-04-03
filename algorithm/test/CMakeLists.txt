set(BIN_NAME test)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/bubble_sort/
)

aux_source_directory(. SRC_LIST)

add_executable(${BIN_NAME} ${SRC_LIST})

target_link_libraries(${BIN_NAME}
    bubble_sort
)