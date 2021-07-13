cl main.cpp src/vertex_array_handler.cpp src/vertex_buffer_handler.cpp src/index_buffer_handler.cpp src/shader_handler.cpp src/random_numbers_handler.cpp src/sorting_visualizer.cpp^
   -I dependencies/GLFW/include -I dependencies/GLEW/include -I dependencies/glm ^
   -link dependencies/GLFW/lib/glfw3dll.lib dependencies/GLEW/lib/glew32s.lib gdi32.lib opengl32.lib user32.lib 
   
