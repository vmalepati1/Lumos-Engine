#pragma once

#include "ls.h"

#include "Mat4.h"
#include "Vec3.h"

#include "MathFunctions.h"

namespace lumos {

	namespace maths {

		struct LS_API Quaternion {
			float x, y, z, w;

			Quaternion();
			Quaternion(const Quaternion &quaternion);
			Quaternion(float x, float y, float z, float w);
			Quaternion(const Vec3 &xyz, float w);
			Quaternion(const Vec4 &vector);
			Quaternion(float scalar);

			Quaternion &operator=(const Quaternion &quaternion);

			Quaternion &setXYZ(const Vec3 &vec);
			const Vec3 getXYZ() const;

			Quaternion &setElement(uint idx, float value);
			float getElement(uint idx) const;
			Vec3 getAxis() const;
			Vec3 toEulerAngles() const;

			const Quaternion operator+(const Quaternion &Quaternion) const;
			const Quaternion operator-(const Quaternion &Quaternion) const;
			const Quaternion operator*(const Quaternion &Quaternion) const;
			const Quaternion operator*(float scalar) const;
			const Quaternion operator/(float scalar) const;
			float operator[](uint idx) const;

			Quaternion &operator+=(const Quaternion &Quaternion)
			{
				*this = *this + Quaternion;
				return *this;
			}

			Quaternion &operator-=(const Quaternion &Quaternion)
			{
				*this = *this - Quaternion;
				return *this;
			}

			Quaternion &operator*=(const Quaternion &Quaternion)
			{
				*this = *this * Quaternion;
				return *this;
			}

			Quaternion &operator*=(float scalar)
			{
				*this = *this * scalar;
				return *this;
			}

			Quaternion &operator/=(float scalar)
			{
				*this = *this / scalar;
				return *this;
			}

			const Quaternion operator-() const;
			bool operator==(const Quaternion &quaternion) const;
			bool operator!=(const Quaternion &quaternion) const;
			static Quaternion identity();
			static Quaternion fromEulerAngles(const Vec3 &angles);

			static Vec3 rotate(const Quaternion &quaternion, const Vec3 &vector);

			static const Quaternion rotation(const Vec3 &unitVector0, const Vec3 &unitVector1);
			static const Quaternion rotation(float radians, const Vec3 &unitVector);

			static const Quaternion rotationX(float radians)
			{
				float angle = radians * 0.5f;
				return Quaternion(sin(angle), 0.0f, 0.0f, cos(angle));
			}

			static const Quaternion rotationY(float radians)
			{
				float angle = radians * 0.5f;
				return Quaternion(0.0f, sin(angle), 0.0f, cos(angle));
			}

			static const Quaternion rotationZ(float radians)
			{
				float angle = radians * 0.5f;
				return Quaternion(0.0f, 0.0f, sin(angle), cos(angle));
			}

			float dot(const Quaternion &other) const;
			Quaternion conjugate() const;

		};

	}

}