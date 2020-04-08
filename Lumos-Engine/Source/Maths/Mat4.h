#pragma once

#include "ls.h"

#include "Vec3.h"
#include "Vec4.h"

namespace lumos {

	namespace maths {

		struct Quaternion;

		struct LS_API Mat4 {

			union {
				float elements[4 * 4];
				Vec4 columns[4];
			};

			Mat4();
			Mat4(float diagonal);
			Mat4(float *elements);
			Mat4(const Vec4& column0, const Vec4& column1, const Vec4& column2, const Vec4& column3);

			static Mat4 identity();

			Mat4& multiply(const Mat4& other);
			Mat4& operator*=(const Mat4& other);
			friend Mat4 operator*(Mat4 left, const Mat4 &right);
			friend std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);

			Vec3 multiply(const Vec3& other) const;
			friend Vec3 operator*(const Mat4& left, const Vec3& right);

			Vec4 multiply(const Vec4& other) const;
			friend Vec4 operator*(const Mat4& left, const Vec4& right);

			Mat4 &invert();

			static const Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static const Mat4 perspective(float fov_degrees, float aspect_ratio, float near, float far);

			static Mat4 translation(const Vec3& translation);
			static Mat4 rotation(float angle_degrees, const Vec3& axis);
			static Mat4 rotation(const Quaternion& quat);
			static Mat4 scale(const Vec3& scalar);
			static Mat4 invert(const Mat4 &matrix);
			static Mat4 lookAt(const Vec3 &from, const Vec3 &to, const Vec3 &axis = Vec3(0, 1, 0));
			static Mat4 transpose(const Mat4& matrix);
		};

	}

}
