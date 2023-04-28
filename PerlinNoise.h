/*
 * PerlinNoise.h
 *
 *  Created on: Apr 4, 2023
 *      Author: Nathan
 */

#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

#include <cstdarg>
#include <random>
#include <queue>

#include "Noise.h"
#include "Functions.h"

namespace mut{

	class PerlinNoise: public Noise{
	public:
		int* size;
		double** vectors;

		PerlinNoise(unsigned int dimensions, unsigned int seed, int size...);

		~PerlinNoise();

		double get(double position...);
	};

}

#endif /* PERLINNOISE_H_ */
