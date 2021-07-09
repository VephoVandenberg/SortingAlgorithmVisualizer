#define GLEW_STATIC

#include "src/random_numbers_handler.h"
#include "src/vertex_array_handler.h"
#include "src/vertex_buffer_handler.h"
#include "src/index_buffer_handler.h"
#include "src/shader_handler.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <time.h>

const unsigned int width = 800;
const unsigned int height = 500;

void delay_time(unsigned int milli_seconds);
void render_out(unsigned int size,
		float *array,
		Shader &shader_handler);

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
    glfwSwapInterval(1);
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
	for (int i = 0; i < size; i++)
	{
	    for (int v = 0; v < size - 1; v++)
	    {
		if (array[v] > array[v + 1])
		{
		    float temp = array[v];
		    array[v] = array[v + 1];
		    array[v + 1] = temp;
		    break;
		}
	    }
	    render_out(size, array, bar_shader_handler);
	    break;
	}
	
	glfwSwapBuffers(window);
	glfwPollEvents();
    }
    return 0;
}

void render_out(unsigned int size,
		float *array,
		Shader &shader_handler)
{
    for (int i = 0; i < size; i++)
    {
	glm::mat4 position;
	position = translate(position, glm::vec3(0.005f*i - 1.0f, array[i] - 1.0f, 0.0f));
	position = scale(position, glm::vec3(1.0f, array[i], 1.0f));
	shader_handler.set_matrix("transform", position);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void delay_time(unsigned int milli_seconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
	;
}

