cmake_minimum_required(VERSION 3.10)
project(cmakeProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(matrix_transformation src/matrix_transformation.cpp)
add_executable(matrix_multiplication src/matrix_multiplication.cpp)
add_executable(farthest_points src/farthest_points.cpp)

include(FetchContent)
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	1.0.1
)
FetchContent_MakeAvailable(glm)

target_link_libraries(matrix_transformation PRIVATE glm::glm)
