cmake_minimum_required(VERSION 3.13.4)

project(DINO)

add_executable(${PROJECT_NAME} Main.cpp)

add_subdirectory(src)
add_subdirectory(libraries/include/glad)
add_subdirectory(libraries/include/GLFW)
add_subdirectory(libraries/include/glm)
add_subdirectory(libraries/include/SOIL2)
add_library(glm::glm ALIAS glm)

target_include_directories(${PROJECT_NAME} 
	PUBLIC src
	PUBLIC libraries/include/GLFW
	PUBLIC libraries/include/glad
	PUBLIC libraries/include/glm
	PUBLIC libraries/include/SOIL2
)
target_link_directories(${PROJECT_NAME} PRIVATE src)

target_link_directories(${PROJECT_NAME} 
	PRIVATE libraries/include/GLFW
	PRIVATE libraries/include/glad
	PRIVATE libraries/include/glm
	PRIVATE libraries/include/SOIL2
)

find_library(SOIL2 soil2-debug)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} src1)
target_link_libraries(${PROJECT_NAME} src2)
target_link_libraries(${PROJECT_NAME} src3)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} SOIL2)