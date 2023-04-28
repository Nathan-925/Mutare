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
using namespace mut;

int main(){
	int w = 100, h = 100, t = 10;
	srand(time(nullptr));
	PerlinNoise p(2, rand(), t, t);
	Image image(w, h);

	for(int i = 0; i < w; i++)
		for(int j = 0; j < h; j++){
			int c = 255*(p.get((double)i/w, (double)j/h)*0.5+0.5);
			image[i][j] = Color(c, c, c);
	}

	writebmp("test.bmp", image);
}
