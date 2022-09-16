set(LIB_NAME template)

set(ROOT_FILES
)

set(PCH 
    "include/template_pch.h"
    "src/template_pch.cpp"
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
)

set(SCENE 
    "include/camera.h"
    "src/camera.cpp"
    "include/shader.h"
    "src/shader.cpp"
)

add_library(${LIB_NAME} STATIC
    ${ROOT_FILES}
	${PCH}
	${GLAD}
	${UTIL}
	${WINDOW}
	${SCENE}
)

source_group(//     FILES ${ROOT_FILES})
source_group(pch    FILES ${PCH})
source_group(glad   FILES ${GLAD})
source_group(util   FILES ${UTIL})
source_group(window FILES ${WINDOW})
source_group(scene FILES ${SCENE})

set_target_output_directories(${LIB_NAME})

set_target_precompiled_header_msvc(${LIB_NAME} "template_pch.h" "src/template_pch.cpp")

set(IGNORE_PCH 
	"src/glad.c"
)
ignore_precompiled_header_msvc(IGNORE_PCH)

target_include_directories(${LIB_NAME} PUBLIC
    "include"
)

target_link_libraries(${LIB_NAME} PUBLIC
	glfw
	glm
    spdlog::spdlog
)