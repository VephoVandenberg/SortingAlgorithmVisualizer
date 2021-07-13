#define GLEW_STATIC

#include "src/random_numbers_handler.h"
#include "src/vertex_array_handler.h"
#include "src/vertex_buffer_handler.h"
#include "src/index_buffer_handler.h"
#include "src/sorting_visualizer.h"
#include "src/shader_handler.h"

#include <iostream>

const unsigned int width = 800;
const unsigned int height = 500;

static bool is_running = true;

void key_callback(GLFWwindow *window,
		  int key,
		  int scancode,
		  int action,
		  int mods);

int main(int argc, char **argv)
{
    if (!glfwInit())
    {
	std::cout << "Could not initialize GLFW" << std::endl;
    }
    
    
    GLFWwindow *window = glfwCreateWindow(width,
					  height,
					  "Sorting algorithms",
					  0, 0);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
	std::cout << "Could not initialize GLEW" << std::endl;
    }

    float bar[24] =
	{
	    0.0f,   -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom left
	    0.0f ,   1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top left
	    0.005f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom right	  
	    0.005f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
	};

    unsigned int indices[6] =
	{
	    0, 1, 2, // first triangle
	    1, 2, 3  // second triangle
	};
    
    VertexArray vertex_array_obj;
    VertexBuffer vertex_buffer_obj(bar, sizeof(bar));
    IndexBuffer index_buffer_obj(indices, sizeof(indices));

    vertex_array_obj.set_attribute_pointer(0, 3, 6, 0);
    vertex_array_obj.set_attribute_pointer(1, 3, 6, 3);

    unsigned int size = 400;
    float *array = new float[size];
    Randomizer randomizer;
    randomizer.generate_random_numbers(size, array);

    Shader bar_shader_handler("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");
    bar_shader_handler.use();

    unsigned int input = 5;
    SortingVisualizer visualizer(&is_running);
    while (!glfwWindowShouldClose(window) && input != 0)
    {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	visualizer.visualize(0, size - 1, array, bar_shader_handler, window);
	std::cout << "If you want to terminate the sorting process hit ESC." << std::endl;
	std::cout << "0 - Exit." << std::endl;
	std::cout << "1 - Bubble sort." << std::endl;
	std::cout << "2 - Selection sort." << std::endl;
	std::cout << "3 - Insertion sort." << std::endl;
	std::cout << "4 - Merge sort." << std::endl;
	std::cout << "Your choice: ";		     
	std::cin >> input;
	std::cout << std::endl;

	is_running = true;
	randomizer.shuffle_numbers(array, size);
	switch(input)
	{
	    case 0:
	    {
		std::cout << "Bye" << std::endl;
	    }break;
	    
	    case 1:
	    {
		visualizer.bubble_sort(array, size, bar_shader_handler, window);
	    }break;

	    case 2:
	    {
		visualizer.selection_sort(array, size, bar_shader_handler, window);
	    }break;
	    
	    case 3:
	    {
	        visualizer.insertion_sort(array, size, bar_shader_handler, window);
	    }break;

	    case 4:
	    {
		visualizer.merge_sort(array, 0, size - 1, size, bar_shader_handler, window);
	    }break;

	    default:
	    {
		std::cout << "Illegal choice." << std::endl;
	    }break;
	    
	}

	glfwSwapBuffers(window);	
	glfwPollEvents();
    }
    return 0;
}

void key_callback(GLFWwindow *window,
		  int key,
		  int scancode,
		  int action,
		  int mods)
{
    switch(key)
    {
	case GLFW_KEY_ESCAPE:
	{
	    if (action == GLFW_PRESS)
	    {
		is_running = false;
	    }
	}break;

	default:
	{
	    
	}break;
    }
}
