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
	int w = 1000, h = 1000, t = 100;
	srand(time(nullptr));
	PerlinNoise p(w, h, t, rand());
	Image img(w, h);

	for(int i = 0; i < w; i++)
		for(int j = 0; j < h; j++)
			img[i][j] = Color(0xFFFFFF)*(p[i][j]*0.5+0.5);

	writebmp("test.bmp", img);
}
