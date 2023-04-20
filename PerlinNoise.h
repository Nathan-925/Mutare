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
#include <iostream>

#include "Noise.h"
#include "Functions.h"

namespace mut{

	template<int dimensions>
	class PerlinNoise: public Noise<dimensions>{

		struct Vector{

		};

	public:
		int size[dimensions];
		double** vectors;

		PerlinNoise(unsigned int seed, int size...) : Noise<dimensions>(seed){
			va_list list;
			va_start(list, size);
			int length = size;
			for(int i = 1; i < dimensions; i++){
				this->size[i] = va_arg(list, int);
				length *= this->size[i];
			}
			va_end(list);
			vectors = new double*[length];
			std::cout << length << " " << dimensions << std::endl;

			std::default_random_engine rand(seed);
			std::normal_distribution<double> distribution;
			for(int i = 0; i < dimensions; i++){
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
			double offset[dimensions];
			va_list list;
			va_start(list, position);
			offset[0] = modf(position*size[0], &index[0]);
			for(int i = 1; i < dimensions; i++)
				offset[i] = modf(va_arg(list, double)*size[i], &index[i]);
			va_end(list);
			for(int i = 0; i < dimensions; i++)
				std::cout << index[i] << " ";
			std::cout << std::endl;

			std::queue<double> queue;
			for(int i = 0; i < pow(2, dimensions); i++){
				int pos = 1;
				for(int j = 0; j < dimensions; j++)
					pos *= (i>>j)&1 ? 1+index[j] : index[j];

				double dot = 0;
				for(int j = 0; j < dimensions; j++)
					dot += vectors[pos][j]+((i>>j)&1 ? 1-offset[j] : offset[j]);
				queue.push(dot);
			}

			while(queue.size() > 1){
				double d = queue.front();
				queue.pop();
				queue.push(d + smoothstep(offset[(int)ceil(log2(queue.size()))])*(queue.front()-d));
				queue.pop();
			}

			return queue.front();
		}
	};

}

#endif /* PERLINNOISE_H_ */
