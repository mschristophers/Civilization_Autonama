#include "Common.h"
#include "Random.h"

#include <vector>

unsigned getIndex(unsigned width, unsigned x, unsigned y)
{
	return x + y * width;
}