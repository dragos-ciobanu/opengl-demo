cmake_minimum_required(VERSION 3.19)
project(hand)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

find_package(OpenGL REQUIRED)

#add_executable(hand src/app.cpp src/Renderer.h src/Renderer.cpp src/VertexBuffer.h src/VertexBuffer.cpp src/IndexBuffer.h src/IndexBuffer.cpp src/Shader.h src/Shader.cpp vendor/stb_image/stb_image.h vendor/stb_image/stb_image.cpp src/Texture.h src/Texture.cpp vendor/imgui/imgui.h vendor/imgui/imgui.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_internal.h vendor/imgui/backends/imgui_impl_glfw.h vendor/imgui/backends/imgui_impl_opengl2.h  vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl2.cpp)
add_executable(hand src/app.cpp src/Renderer.h src/Renderer.cpp src/VertexBuffer.h src/VertexBuffer.cpp src/IndexBuffer.h src/IndexBuffer.cpp src/Shader.h src/Shader.cpp vendor/stb_image/stb_image.h vendor/stb_image/stb_image.cpp src/Texture.h src/Texture.cpp)
include_directories(${PROJECT_SOURCE_DIR}/vendor/GLFW/include)
## Imgui lib
add_library(imgui STATIC
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.h
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imconfig.h
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_internal.h
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_impl_glfw.h
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_impl_opengl2.h
        ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_impl_opengl2.cpp)

# Included these two lines:
target_include_directories(hand PUBLIC ${PROJECT_SOURCE_DIR}/vendor/GLFW/include ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/vendor ${PROJECT_SOURCE_DIR}/vendor/imgui )
target_link_libraries(hand ${OPENGL_LIBRARIES} ${PROJECT_SOURCE_DIR}/vendor/GLFW/lib/libglfw3.a imgui)