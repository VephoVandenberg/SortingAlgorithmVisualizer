#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <algorithm>

class Randomizer
{
public:
    void generate_random_numbers(unsigned int number_of_values,
				 float *values);
    void shuffle_numbers(float *values, unsigned int size);
};

#endif
