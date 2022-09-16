set(EXC_NAME program)

set(ROOT_FILES
    "src/main.cpp"
)

add_executable(${EXC_NAME}
    ${ROOT_FILES}
)

source_group(// FILES ${ROOT_FILES})

target_link_libraries(${EXC_NAME} PUBLIC
    template
)