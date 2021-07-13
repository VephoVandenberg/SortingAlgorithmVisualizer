#ifndef SORT_H
#define SORT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader_handler.h"

class SortingVisualizer
{
public:
    SortingVisualizer(bool *state);
    void bubble_sort(float *array,
		     unsigned int size,
		     Shader &shader_handler,
		     GLFWwindow *window);
    
    void selection_sort(float *array,
			unsigned int size,
			Shader &shader_handler,
			GLFWwindow *window);
    
    void insertion_sort(float *array,
			unsigned int size,
			Shader &shader_handler,
			GLFWwindow *window);
    
    void merge_sort(float *array,
		    int low, int high,
		    unsigned int size,
		    Shader &shader_handler,
		    GLFWwindow *window);
    
    void visualize(unsigned int first_border,
		   unsigned int back_border,
		   float *array,
		   Shader &shader_handler,
		   GLFWwindow *window);    
private:
    bool *is_running;

    void merge(float *array,
	       int low, int high, int mid,
	       unsigned int size,
	       Shader &shader_handler,
	       GLFWwindow *window);
};

#endif
