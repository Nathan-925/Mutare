/*
 * PerlinNoise.h
 *
 *  Created on: Apr 4, 2023
 *      Author: Nathan
 */

#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

#include <ctime>

namespace top{

	class PerlinNoise{
	public:
		int width, height;
		double** values;

		PerlinNoise(int width, int height, int tileWidth, unsigned int seed = 1u);
		~PerlinNoise();

		const double* operator[](int n);
	};

}

#endif /* PERLINNOISE_H_ */
