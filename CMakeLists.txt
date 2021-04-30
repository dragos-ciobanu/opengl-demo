cmake_minimum_required(VERSION 3.19)
project(hand)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


#find_library(COCOA_LIBRARY Cocoa)

add_executable(hand src/app.cpp src/Renderer.h src/Renderer.cpp src/VertexBuffer.h src/VertexBuffer.cpp src/IndexBuffer.h src/IndexBuffer.cpp src/Shader.h src/Shader.cpp)


# Included these two lines:
target_include_directories(hand PUBLIC ${PROJECT_SOURCE_DIR}/vendor/GLFW/include ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(hand ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${PROJECT_SOURCE_DIR}/vendor/GLFW/lib/libglfw3.a ${COCOA_LIBRARY})