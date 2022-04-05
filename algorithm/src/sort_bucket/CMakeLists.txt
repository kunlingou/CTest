aux_source_directory(. SRC_LIST)

add_library(sort_bucket SHARED ${SRC_LIST})

target_link_libraries(${BIN_NAME}
    sort_quick
)