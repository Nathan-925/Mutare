/*
 * PerlinNoise.cpp
 *
 *  Created on: Apr 4, 2023
 *      Author: Nathan
 */
#include <random>

#include "PerlinNoise.h"

#include "priori/Math.h"

using namespace std;
using namespace priori;

namespace top{

	PerlinNoise::PerlinNoise(int width, int height, int tileWidth, unsigned int seed) : width(width), height(height), values(new double*[width]){
		for(int i = 0; i < width; i++)
			values[i] = new double[height];

		default_random_engine rand(seed);
		normal_distribution<double> distribution;
		int vectorWidth = width/tileWidth+1, vectorHeight = height/tileWidth+1;
		Vector** vectors = new Vector*[vectorWidth];
		for(int i = 0; i < vectorWidth; i++){
			vectors[i] = new Vector[vectorHeight];
			for(int j = 0; j < vectorHeight; j++)
				vectors[i][j] = Vector{distribution(rand), distribution(rand)}.normalize();
		}

		for(int x = 0; x < width; x++)
			for(int y = 0; y < height; y++){
				int xGrid = x/tileWidth, yGrid = y/tileWidth;
				double xPos = x%tileWidth, yPos = y%tileWidth;

				double d1 = vectors[xGrid][yGrid] * Vector{xPos, yPos};
				double d2 = vectors[xGrid+1][yGrid] * Vector{xPos-tileWidth, yPos};
				double d3 = vectors[xGrid][yGrid+1] * Vector{xPos, yPos-tileWidth};
				double d4 = vectors[xGrid+1][yGrid+1] * Vector{xPos-tileWidth, yPos-tileWidth};

				double xStep = smoothstep(xPos/tileWidth);
				double yStep = smoothstep(yPos/tileWidth);

				double d12 = d1 + xStep*(d2-d1);
				double d34 = d3 + xStep*(d4-d3);

				values[x][y] = (d12 + yStep*(d34-d12))/tileWidth;
			}
	}

	PerlinNoise::~PerlinNoise(){
		for(int i = 0; i < width; i++)
			delete[] values[i];
		delete[] values;
	}

	const double* PerlinNoise::operator[](int n){
		return values[n];
	}

}
