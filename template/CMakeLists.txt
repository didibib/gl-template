set(TARGET template)

set(ROOT_FILES
    "src/main.cpp"
)

set(PCH 
    "include/gtpch.h"
    "src/gtpch.cpp"
)

set(GLAD 
    "include/glad/glad.h"
    "src/glad.c"
)

set(UTIL 
    "include/util.h"
    "include/logger.h"
    "src/logger.cpp"
)

set(WINDOW 
    "include/window.h"
    "src/window.cpp"
    "include/program.h"
)

set(CAMERA 
    "include/camera.h"
    "src/camera.cpp"
)

add_executable(${TARGET}
    ${ROOT_FILES}
	${PCH}
	${GLAD}
	${UTIL}
	${WINDOW}
	${CAMERA}
)

source_group(\\ FILES ${ROOT_FILES})
source_group(pch FILES ${PCH})
source_group(glad FILES ${GLAD})
source_group(util FILES ${UTIL})
source_group(window FILES ${WINDOW})
source_group(camera FILES ${CAMERA})

set_target_output_directories(${TARGET})

set_target_precompiled_header_msvc(${TARGET} "gtpch.h" "src/gtpch.cpp")

set(IGNORE_PCH 
	"src/glad.c"
)
ignore_precompiled_header_msvc(IGNORE_PCH)

target_include_directories(${TARGET} PUBLIC
    "include"
)

target_link_libraries(${TARGET} PUBLIC
	glfw
	glm
    spdlog::spdlog
)