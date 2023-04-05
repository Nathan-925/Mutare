/*
 * Test.cpp
 *
 *  Created on: Apr 4, 2023
 *      Author: Nathan
 */
#include <iostream>
#include <cmath>

#include "PerlinNoise.h"

#include "priori/BMPLibrary.h"

using namespace std;
using namespace priori;
using namespace top;

int main(){
	PerlinNoise noise(100, 100, 10);
	Image img(noise.width, noise.height);

	for(int i = 0; i < noise.width; i++)
		for(int j = 0; j < noise.height; j++){
			int c = 255*pow(noise[i][j]*0.5+0.5, 2.0);
			img[i][j] = Color(c, c, c);
		}

	writebmp("test.bmp", img);
}
