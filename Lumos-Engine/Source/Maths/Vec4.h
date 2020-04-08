#pragma once

#include "ls.h"

#include "Vec3.h"

namespace lumos {

	namespace maths {

		struct LS_API Vec4 {
			float x, y, z, w;

			Vec4() = default;
			Vec4(float scalar);
			Vec4(float x, float y, float z, float w);
			Vec4(const Vec3 &xyz, float w);

			Vec4& add(const Vec4 &other);
			Vec4& subtract(const Vec4 &other);
			Vec4& multiply(const Vec4 &other);
			Vec4& divide(const Vec4 &other);

			friend Vec4& operator+(Vec4 &left, const Vec4 &right);
			friend Vec4& operator-(Vec4 &left, const Vec4 &right);
			friend Vec4& operator*(Vec4 &left, const Vec4 &right);
			friend Vec4& operator/(Vec4 &left, const Vec4 &right);

			bool operator==(const Vec4& other);
			bool operator!=(const Vec4& other);

			Vec4& operator+=(const Vec4 &other);
			Vec4& operator-=(const Vec4 &other);
			Vec4& operator*=(const Vec4 &other);
			Vec4& operator/=(const Vec4 &other);

			friend std::ostream& operator<<(std::ostream &stream, const Vec4 &vector);

		};

	}

}

