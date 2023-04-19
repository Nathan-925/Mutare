/*
 * PerlinNoise.h
 *
 *  Created on: Apr 4, 2023
 *      Author: Nathan
 */

#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

#include "Noise.h"

namespace mut{

	template<int dimensions>
	class PerlinNoise: public Noise<dimensions>{
	public:
		int size[dimensions];
		double** vectors;

		PerlinNoise(unsigned int seed , int size...);
		PerlinNoise(int size...);
		~PerlinNoise();

		double get(double position...);
	};

}

#endif /* PERLINNOISE_H_ */
