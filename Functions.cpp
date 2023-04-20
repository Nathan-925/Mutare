/*
 * Functions.cpp
 *
 *  Created on: Apr 4, 2023
 *      Author: Nathan
 */
#include "Functions.h"

namespace mut{

	double smoothstep(double x){
		if(x <= 0)
			return 0;
		if(x < 1)
			return 3*x*x - 2*x*x*x;
		return 1;
	}

}
