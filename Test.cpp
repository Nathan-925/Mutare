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
	int w = 100, h = 100, d = 10, t = 5;
	srand(time(nullptr));
	PerlinNoise<3> p(rand(), t, t, t);
	Image img(w, h);

	for(int i = 0; i < w; i++)
		for(int j = 0; j < h; j++)
		for(int l = 0; l < d; l++){
			int c = 255*(p.get((double)i/w, (double)j/h, (double)l/d)*0.5+0.5);
			img[i][j] = Color(c, c, c);
		}

	for(int i = 0; i < d; i++)
		writebmp("test"+to_string(i)+".bmp", img);
}
