#include "sorting_visualizer.h"

SortingVisualizer::SortingVisualizer(bool *state)
{
    is_running = state;
}

void SortingVisualizer::bubble_sort(float *array,
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
	    
	    visualize(0, size - 1, array, shader_handler, window);	    
	}
	if (!(*is_running))
	{
	    break;
	}
	glfwPollEvents();
    }
}

void SortingVisualizer::selection_sort(float *array,
				       unsigned int size,
				       Shader &shader_handler,
				       GLFWwindow *window)
{
    int  minimum;
 
    for (int i = 0; i < size-1; i++)
    {
        minimum = i;
        for (int j = i + 1; j < size; j++)
	{
	    if (array[j] < array[minimum])
	    {
		minimum = j;
	    }
	    visualize(0, size - 1, array, shader_handler, window);
	}
	float temp = array[i];
	array[i] = array[minimum];
	array[minimum] = temp;
	if (!(*is_running))
	{
	    break;
	}
	glfwPollEvents();
    }
}

void  SortingVisualizer::insertion_sort(float *array,
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
	    visualize(0, size - 1, array, shader_handler, window);
	}
	if (!(*is_running))
	{
	    break;
	}	
	glfwPollEvents();
    }
}

void  SortingVisualizer::visualize(unsigned int first_border,
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
