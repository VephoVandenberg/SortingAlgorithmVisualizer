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

void SortingVisualizer::merge(float *array,
			      int low, int high, int mid,
			      unsigned int size,
			      Shader &shader_handler,
			      GLFWwindow *window)
{
    int left_len = (mid - low) + 1;
    int right_len = (high - mid);
    
    float *left_part = new float[left_len];
    float *right_part = new float[right_len];

    int i, j;
    int part_counter;

    for (i = 0; i < left_len; i++)
    {
	left_part[i] = array[low + i];
    }

    for (j = 0; j < right_len; j++)
    {
	right_part[j] = array[mid + 1 + j];
    }

    i = j = 0;
    int index = low;
    while (i < left_len && j < right_len)
    {
	if (left_part[i] <= right_part[j])
	{
	    array[index++] = left_part[i++];	    
	}
	else
	{
	    array[index++] = right_part[j++];
	}
	visualize(0, size - 1, array, shader_handler, window);
    }

    while (i < left_len)
    {
	array[index++] = left_part[i++];
	visualize(0, size - 1, array, shader_handler, window);
    }

    while (j < right_len)
    {
	array[index++] = right_part[j++];
	visualize(0, size - 1, array, shader_handler, window);       	
    }
    delete [] left_part;
    delete [] right_part;
}

void SortingVisualizer::merge_sort(float *array,
				   int low, int high,
				   unsigned int size,
				   Shader &shader_handler,
				   GLFWwindow *window)
{
    if (low < high)
    {
	int mid = low + (high - low) / 2;
	merge_sort(array,
		   low, mid,
		   size,
		   shader_handler, window);
	
	merge_sort(array,
		   mid + 1, high,
		   size,
		   shader_handler, window);

	merge(array,
	      low, high, mid,
	      size,
	      shader_handler, window);
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
