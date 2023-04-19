/*
 * PerlinNoise.cpp
 *
 *  Created on: Apr 4, 2023
 *      Author: Nathan
 */
#include <random>
#include <queue>

#include "PerlinNoise.h"

using namespace std;

namespace mut{

	template<int dimensions>
	PerlinNoise<dimensions>::PerlinNoise(unsigned int seed, int size...) : size(size){
		int length = 1;
		for(int n: size)
			length *= n;
		vectors = new double*[length];

		default_random_engine rand(seed);
		normal_distribution<double> distribution;
		for(int i = 0; i < dimensions; i++){
			vectors[i] = new double[size[i]];
			double mag = 0;
			for(int i = 0; i < dimensions; i++){
				vectors[i][i] = distribution(rand);
				mag += vectors[i][i];
			}
			for(double &d: vectors[i])
				d /= mag;
		}
	}

	template<int dimensions>
	PerlinNoise<dimensions>::PerlinNoise(int size...) : PerlinNoise(1u, size){}

	template<int dimensions>
	PerlinNoise<dimensions>::~PerlinNoise(){
		delete[] vectors;
	}

	template<int dimensions>
	double PerlinNoise<dimensions>::get(double position...){
		double offset[dimensions];
		for(int i = 0; i < dimensions; i++)
			offset[i] = modf(position[i]*size[i], &position[i]);

		queue<double> queue;
		for(int i = 0; i < pow(2, dimensions); i++){
			int pos;
			for(int j = 0; j < dimensions; j++)
				pos *= (i>>j)&1 ? 1+position[j] : position[j];

			double dot = 0;
			for(int j = 0; j < dimensions; j++)
				dot += vectors[pos][j]+((i>>j)&1 ? 1-offset[j] : offset[j]);
			queue.push(dot);
		}

		while(queue.size() > 1){
			double d = queue.front();
			queue.pop();
			queue.push(d + smoothstep(offset[ceil(log2(queue.size()))])*(queue.front()-d));
			queue.pop();
		}

		return queue.front();
	}

}
