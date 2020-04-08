#pragma once

#include "ls.h"

#define LS_PI 3.14159265358f

namespace lumos {

	namespace maths {

		struct LS_API MathFunctions {
		public:

			static inline float DegreesToRadians(float degrees) {
				return (float)((LS_PI / 180) * degrees);
			}

			static inline float RadiansToDegrees(float radians) {
				return (float)((180 / LS_PI) * radians);
			}

			static inline int Sign(float value) {
				return (value > 0) - (value < 0);
			}

			static inline float Sin(float angle) {
				return sin(angle);
			}

			static inline float Cos(float angle) {
				return cos(angle);
			}

			static inline float Tan(float angle) {
				return tan(angle);
			}

			static inline float Sqrt(float value) {
				return sqrt(value);
			}

			static inline float RSqrt(float value) {
				return 1.0f / sqrt(value);
			}
				 
		};


	}
}