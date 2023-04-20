/*
 * Noise.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Nathan
 */

#ifndef NOISE_H_
#define NOISE_H_

namespace mut{

	template<int dimensions>
	class Noise{
	public:
		const unsigned int seed;

		Noise(unsigned int seed = 1u) : seed(seed){}
		virtual ~Noise(){}

		virtual double get(double position...){
			return 0;
		}

	};

}

#endif /* NOISE_H_ */
