#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <iostream>
#include <algorithm>

class Randomizer
{
public:
    void generate_random_numbers(unsigned int number_of_values,
				 float *values);
};

#endif
