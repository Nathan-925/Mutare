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

	template<int dimensions>
	class PerlinNoise: public Noise<dimensions>{
	public:
		int size[dimensions];
		double** vectors;

		PerlinNoise(unsigned int seed, int size...) : Noise<dimensions>(seed){
			va_list list;
			va_start(list, size);
			this->size[0] = size;
			int length = this->size[0];
			for(int i = 1; i < dimensions; i++){
				this->size[i] = va_arg(list, int);
				length *= this->size[i];
			}
			va_end(list);

			vectors = new double*[length];

			std::default_random_engine rand(seed);
			std::normal_distribution<double> distribution;
			for(int i = 0; i < length; i++){
				vectors[i] = new double[dimensions];
				double mag = 0;
				for(int j = 0; j < dimensions; j++){
					vectors[i][j] = distribution(rand);
					mag += vectors[i][j]*vectors[i][j];
				}

				mag = std::sqrt(mag);
				for(int j = 0; j < dimensions; j++)
					vectors[i][j] /= mag;
			}
		}

		~PerlinNoise(){
			int length = 1;
			for(int n: size)
				length *= n;
			for(int i = 0; i < length; i++)
				delete[] vectors[i];
			delete[] vectors;
		}

		double get(double position...){
			double index[dimensions];
			va_list list;
			va_start(list, position);
			index[0] = position*(size[0]-1);
			for(int i = 1; i < dimensions; i++)
				index[i] = va_arg(list, double)*(size[i]-1);
			va_end(list);

			std::queue<double> queue;
			for(int i = 0; i < pow(2, dimensions); i++){
				int pos = 0;
				int offset = 1;
				for(int j = 0; j < dimensions; offset *= size[j], j++)
					pos += offset*((i>>j)&1 ? std::ceil(index[j]) : std::floor(index[j]));

				double fraction[dimensions];
				double temp;
				for(int j = 0; j < dimensions; j++)
					fraction[j] = (i>>j)&1 ? std::modf(index[j], &temp)-1 : std::modf(index[j], &temp);

				double dot = 0;
				for(int j = 0; j < dimensions; j++)
					dot += vectors[pos][j]*fraction[j];
				queue.push(dot);
			}

			double temp;
			while(queue.size() > 1){
				int dimension = dimensions-(int)ceil(log2(queue.size()));
				double d1 = queue.front();
				queue.pop();
				double d2 = queue.front();
				queue.pop();

				queue.push(d1 + smoothstep(std::modf(index[dimension], &temp))*(d2-d1));
			}

			return queue.front();
		}
	};

}

#endif /* PERLINNOISE_H_ */
