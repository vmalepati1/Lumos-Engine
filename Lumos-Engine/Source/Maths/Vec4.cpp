#include "ls.h"

#include "Vec4.h"

namespace lumos {

	namespace maths {

		Vec4::Vec4(float scalar) {
			this->x = scalar;
			this->y = scalar;
			this->z = scalar;
			this->w = scalar;
		}

		Vec4::Vec4(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vec4::Vec4(const Vec3 &xyz, float w) {
			this->x = xyz.x;
			this->y = xyz.y;
			this->z = xyz.z;
			this->w = w;
		}

		Vec4& Vec4::add(const Vec4 &other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Vec4& Vec4::subtract(const Vec4 &other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		Vec4& Vec4::multiply(const Vec4 &other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		Vec4& Vec4::divide(const Vec4 &other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}

		Vec4& operator+(Vec4 &left, const Vec4 &right) {
			return left.add(right);
		}

		Vec4& operator-(Vec4 &left, const Vec4 &right) {
			return left.subtract(right);
		}

		Vec4& operator*(Vec4 &left, const Vec4 &right) {
			return left.multiply(right);
		}

		Vec4& operator/(Vec4 &left, const Vec4 &right) {
			return left.divide(right);
		}

		Vec4& Vec4::operator+=(const Vec4 &other) {
			*this = *this + other;
			return *this;
		}

		Vec4& Vec4::operator-=(const Vec4 &other) {
			*this = *this - other;
			return *this;
		}

		Vec4& Vec4::operator*=(const Vec4 &other) {
			*this = *this * other;
			return *this;
		}

		Vec4& Vec4::operator/=(const Vec4 &other) {
			*this = *this / other;
			return *this;
		}

		bool Vec4::operator==(const Vec4& other) {
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool Vec4::operator!=(const Vec4& other) {
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream &stream, const Vec4 &vector) {
			stream << "Vec4 [" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "]";
			return stream;
		}

	}

}