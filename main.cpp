#define GLEW_STATIC

#include "src/random_numbers_handler.h"
#include "src/vertex_array_handler.h"
#include "src/vertex_buffer_handler.h"
#include "src/index_buffer_handler.h"
#include "src/shader_handler.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <chrono>

const unsigned int width = 800;
const unsigned int height = 500;

void delay_time(void);
void render_out(unsigned int front_border,
		unsigned int back_border,
		float *array,
		Shader &shader_handler,
		GLFWwindow *window);
void bubble_sort(float *array,
		 unsigned int size,
		 Shader &shader_handler,
		 GLFWwindow *window);
void insertion_sort(float *array,
		    unsigned int size,
		    Shader &shader_handler,
		    GLFWwindow *window);
void selection_sort(float *array,
		    unsigned int size,
		    Shader &shader_handler,
		    GLFWwindow *window);

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
    
    while (!glfwWindowShouldClose(window))
    {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	bubble_sort(array, size, bar_shader_handler, window);

	glfwSwapBuffers(window);	
	glfwPollEvents();
    }
    return 0;
}

void render_out(unsigned int first_border,
		unsigned int back_border,
		float *array,
		Shader &shader_handler,
		GLFWwindow *window)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = first_border; i <= back_border; i++)
    {
	glm::mat4 position;
	position = translate(position, glm::vec3(0.005f*i - 1.0f, array[i] - 1.0f, 0.0f));
	position = scale(position, glm::vec3(1.0f, array[i], 1.0f));
	shader_handler.set_matrix("transform", position);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    glfwSwapBuffers(window);
}

void delay_time(void)
{
    int time = 10000;

    for (int i = 0; i < time; i++);
}

void bubble_sort(float *array,
		 unsigned int size,
		 Shader &shader_handler,
		 GLFWwindow *window)
{
    for (int i = 0; i < size; i++)
    {	      	
	for (int v = 0; v < size - 1; v++)
	{
	    if (array[v] > array[v + 1])
	    {
		float temp = array[v];
		array[v] = array[v + 1];
		array[v + 1] = temp;
	    }
	    render_out(0, size - 1, array, shader_handler, window);
	    glfwPollEvents();
	}
	glfwPollEvents();
    }
}

void insertion_sort(float *array,
		    unsigned int size,
		    Shader &shader_handler,
		    GLFWwindow *window)
{

    for (int i = 1; i < size; i++)
    {
	for (int j = i; j > 0; j--)
	{
	    if (array[j] < array[j - 1])
	    {
		float temp = array[j];
		array[j] = array[j - 1];
		array[j - 1] = temp;
	    }
	    render_out(0, size - 1, array, shader_handler, window);
	}
    }
}

void selection_sort(float *array,
		    unsigned int size,
		    Shader &shader_handler,
		    GLFWwindow *window)
{
    int minimum;
    
    
    for (int i = 0; i < size; i++)
    {
	for (int j = i, minimum = i; j < size; j++)
	{
	    if (array[minimum] > array[j])
	    {
		minimum = j;
	    }
	}
	float temp = array[i];
	array[i] = array[minimum];
	array[minimum] = temp;
	render_out(0, size - 1, array, shader_handler, window);
    }
}
