/*
 * Maths.cpp
 *
 *  Created on: 2016Äê6ÔÂ24ÈÕ
 *      Author: euwyzbc
 */
#include <stdint.h>
#include "Maths.h"

namespace Algorithms {

Maths::Maths() {
  // TODO Auto-generated constructor stub

}

Maths::~Maths() {
  // TODO Auto-generated destructor stub
}

float Maths::fastSqrt(float x)
{
  uint32_t x_bits = 0;

  x_bits = *((uint32_t*) &x);

  x_bits = (x_bits >> 1) + 532369198;

  return *((float*) &x_bits);
}

} /* namespace Algorithms */
