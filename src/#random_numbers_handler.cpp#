#include "random_numbers_handler.h"

void Randomizer::generate_random_numbers(unsigned int number_of_values,
					 float *values)
{
    float v = 0.0f;
    for (int i = 0; v < 1.0f; i++, v+= 0.0025f)
    {	
	values[i] = v;
    }
    std::random_shuffle(&values[0], &values[number_of_values]);
}

