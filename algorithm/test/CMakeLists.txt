set(BIN_NAME test_main)

include_directories(

)

aux_source_directory(. SRC_LIST)

add_executable(${BIN_NAME} ${SRC_LIST})

target_link_libraries(${BIN_NAME}
    sort_bubble
    sort_selection
    sort_insertion
    sort_shell
    sort_quick
)