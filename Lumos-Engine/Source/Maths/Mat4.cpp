#include "ls.h"

#include "Mat4.h"

#include "quaternion.h"

namespace lumos {

	namespace maths {

		Mat4::Mat4() {
			for (int i = 0; i < 4 * 4; i++) {
				elements[i] = 0.0f;
			}
		}

		Mat4::Mat4(float diagonal) {
			for (int i = 0; i < 4 * 4; i++) {
				elements[i] = 0.0f;
			}

			elements[0] = diagonal;
			elements[5] = diagonal;
			elements[10] = diagonal;
			elements[15] = diagonal;
		}

		Mat4::Mat4(float *elements) {
			memcpy(this->elements, elements, 4 * 4 * sizeof(elements[0]));
		}

		Mat4::Mat4(const Vec4& column0, const Vec4& column1, const Vec4& column2, const Vec4& column3)
		{
			columns[0] = column0;
			columns[1] = column1;
			columns[2] = column2;
			columns[3] = column3;
		}

		Mat4 Mat4::identity() {
			return Mat4(1.0f);
		}

		Mat4& Mat4::multiply(const Mat4& other) {
			float data[4 * 4];
			for (int row = 0; row < 4; row++) {
				for (int column = 0; column < 4; column++) {
					float sum = 0.0f;
					for (int e = 0; e < 4; e++) {
						sum += elements[e + row * 4] * other.elements[column + e * 4];
						data[column + row * 4] = sum;
					}
				}
			}
			memcpy(elements, data, 4 * 4 * sizeof(data[0]));
			return *this;
		}

		Vec3 Mat4::multiply(const Vec3& other) const {
			return Vec3(
				columns[0].x * other.x + columns[0].y * other.y + columns[0].z * other.z + columns[0].w,
				columns[1].x * other.x + columns[1].y * other.y + columns[1].z * other.z + columns[1].w,
				columns[2].x * other.x + columns[2].y * other.y + columns[2].z * other.z + columns[2].w
			);
		}

		Vec4 Mat4::multiply(const Vec4& other) const {
			return Vec4(
				columns[0].x * other.x + columns[0].y * other.y + columns[0].z * other.z + columns[0].w * other.w,
				columns[1].x * other.x + columns[1].y * other.y + columns[1].z * other.z + columns[1].w * other.w,
				columns[2].x * other.x + columns[2].y * other.y + columns[2].z * other.z + columns[2].w * other.w,
				columns[3].x * other.x + columns[3].y * other.y + columns[3].z * other.z + columns[3].w * other.w
			);
		}


		Vec3 operator*(const Mat4& left, const Vec3& right) {
			return left.multiply(right);
		}

		Vec4 operator*(const Mat4& left, const Vec4& right) {
			return left.multiply(right);
		}

		Mat4 operator*(Mat4 left, const Mat4 &right) {
			return left.multiply(right);
		}

		Mat4& Mat4::operator*=(const Mat4& other) {
			return multiply(other);
		}

		Mat4 &Mat4::invert() {
			double temp[16];
			double determinent;

			temp[0] = elements[5] * elements[10] * elements[15] -
				elements[5] * elements[11] * elements[14] -
				elements[9] * elements[6] * elements[15] +
				elements[9] * elements[7] * elements[14] +
				elements[13] * elements[6] * elements[11] -
				elements[13] * elements[7] * elements[10];

			temp[4] = -elements[4] * elements[10] * elements[15] +
				elements[4] * elements[11] * elements[14] +
				elements[8] * elements[6] * elements[15] -
				elements[8] * elements[7] * elements[14] -
				elements[12] * elements[6] * elements[11] +
				elements[12] * elements[7] * elements[10];

			temp[8] = elements[4] * elements[9] * elements[15] -
				elements[4] * elements[11] * elements[13] -
				elements[8] * elements[5] * elements[15] +
				elements[8] * elements[7] * elements[13] +
				elements[12] * elements[5] * elements[11] -
				elements[12] * elements[7] * elements[9];

			temp[12] = -elements[4] * elements[9] * elements[14] +
				elements[4] * elements[10] * elements[13] +
				elements[8] * elements[5] * elements[14] -
				elements[8] * elements[6] * elements[13] -
				elements[12] * elements[5] * elements[10] +
				elements[12] * elements[6] * elements[9];

			temp[1] = -elements[1] * elements[10] * elements[15] +
				elements[1] * elements[11] * elements[14] +
				elements[9] * elements[2] * elements[15] -
				elements[9] * elements[3] * elements[14] -
				elements[13] * elements[2] * elements[11] +
				elements[13] * elements[3] * elements[10];

			temp[5] = elements[0] * elements[10] * elements[15] -
				elements[0] * elements[11] * elements[14] -
				elements[8] * elements[2] * elements[15] +
				elements[8] * elements[3] * elements[14] +
				elements[12] * elements[2] * elements[11] -
				elements[12] * elements[3] * elements[10];

			temp[9] = -elements[0] * elements[9] * elements[15] +
				elements[0] * elements[11] * elements[13] +
				elements[8] * elements[1] * elements[15] -
				elements[8] * elements[3] * elements[13] -
				elements[12] * elements[1] * elements[11] +
				elements[12] * elements[3] * elements[9];

			temp[13] = elements[0] * elements[9] * elements[14] -
				elements[0] * elements[10] * elements[13] -
				elements[8] * elements[1] * elements[14] +
				elements[8] * elements[2] * elements[13] +
				elements[12] * elements[1] * elements[10] -
				elements[12] * elements[2] * elements[9];

			temp[2] = elements[1] * elements[6] * elements[15] -
				elements[1] * elements[7] * elements[14] -
				elements[5] * elements[2] * elements[15] +
				elements[5] * elements[3] * elements[14] +
				elements[13] * elements[2] * elements[7] -
				elements[13] * elements[3] * elements[6];

			temp[6] = -elements[0] * elements[6] * elements[15] +
				elements[0] * elements[7] * elements[14] +
				elements[4] * elements[2] * elements[15] -
				elements[4] * elements[3] * elements[14] -
				elements[12] * elements[2] * elements[7] +
				elements[12] * elements[3] * elements[6];

			temp[10] = elements[0] * elements[5] * elements[15] -
				elements[0] * elements[7] * elements[13] -
				elements[4] * elements[1] * elements[15] +
				elements[4] * elements[3] * elements[13] +
				elements[12] * elements[1] * elements[7] -
				elements[12] * elements[3] * elements[5];

			temp[14] = -elements[0] * elements[5] * elements[14] +
				elements[0] * elements[6] * elements[13] +
				elements[4] * elements[1] * elements[14] -
				elements[4] * elements[2] * elements[13] -
				elements[12] * elements[1] * elements[6] +
				elements[12] * elements[2] * elements[5];

			temp[3] = -elements[1] * elements[6] * elements[11] +
				elements[1] * elements[7] * elements[10] +
				elements[5] * elements[2] * elements[11] -
				elements[5] * elements[3] * elements[10] -
				elements[9] * elements[2] * elements[7] +
				elements[9] * elements[3] * elements[6];

			temp[7] = elements[0] * elements[6] * elements[11] -
				elements[0] * elements[7] * elements[10] -
				elements[4] * elements[2] * elements[11] +
				elements[4] * elements[3] * elements[10] +
				elements[8] * elements[2] * elements[7] -
				elements[8] * elements[3] * elements[6];

			temp[11] = -elements[0] * elements[5] * elements[11] +
				elements[0] * elements[7] * elements[9] +
				elements[4] * elements[1] * elements[11] -
				elements[4] * elements[3] * elements[9] -
				elements[8] * elements[1] * elements[7] +
				elements[8] * elements[3] * elements[5];

			temp[15] = elements[0] * elements[5] * elements[10] -
				elements[0] * elements[6] * elements[9] -
				elements[4] * elements[1] * elements[10] +
				elements[4] * elements[2] * elements[9] +
				elements[8] * elements[1] * elements[6] -
				elements[8] * elements[2] * elements[5];

			determinent = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];

			if (determinent != 0) determinent = 1.0 / determinent;

			if (determinent != 0) {
				for (int i = 0; i < 4 * 4; i++)
					elements[i] = (float)(temp[i] * determinent);
			}

			return *this;
		}

		const Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
			Mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);
			result.elements[3 + 0 * 4] = (left + right) / (left - right);
			result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
			result.elements[3 + 2 * 4] = (far + near) / (far - near);
			return result;
		}

		const Mat4 Mat4::perspective(float fov_degrees, float aspect_ratio, float near, float far) {
			Mat4 result(1.0f);

			float q = 1.0f / tan(MathFunctions::DegreesToRadians(0.5f * fov_degrees));
			float a = q / aspect_ratio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[2 + 3 * 4] = -1.0f;
			result.elements[3 + 2 * 4] = c;

			return result;
		}

		Mat4 Mat4::translation(const Vec3& translation) {
			Mat4 result(1.0f);

			result.elements[3 + 0 * 4] = translation.x;
			result.elements[3 + 1 * 4] = translation.y;
			result.elements[3 + 2 * 4] = translation.z;

			return result;
		}

		Mat4 Mat4::rotation(float angle_degrees, const Vec3& axis) {
			Mat4 result(1.0f);

			float r = MathFunctions::DegreesToRadians(angle_degrees);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * x * omc + c;
			result.elements[0 + 1 * 4] = y * x * omc + z * s;
			result.elements[0 + 2 * 4] = x * z * omc - y * s;

			result.elements[1 + 0 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * y * omc + c;
			result.elements[1 + 2 * 4] = y * z * omc + x * s;

			result.elements[2 + 0 * 4] = x * z * omc + y * s;
			result.elements[2 + 1 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * z * omc + c;

			return result;
		}

		Mat4 Mat4::scale(const Vec3& scalar) {
			Mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scalar.x;
			result.elements[1 + 1 * 4] = scalar.y;
			result.elements[2 + 2 * 4] = scalar.z;

			return result;
		}

		std::ostream& operator<<(std::ostream& stream, const Mat4& matrix) {
			stream << "Mat4 elements:";
			for (int i = 0; i < 16; i++) {
				if (i % 4 == 0) {
					stream << std::endl;
				}
				stream << matrix.elements[i] << ", ";
			}
			return stream;
		}

		Mat4 Mat4::rotation(const Quaternion& quat)
		{
			Mat4 result = identity();

			float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;
			qx = quat.x;
			qy = quat.y;
			qz = quat.z;
			qw = quat.w;
			qx2 = (qx + qx);
			qy2 = (qy + qy);
			qz2 = (qz + qz);
			qxqx2 = (qx * qx2);
			qxqy2 = (qx * qy2);
			qxqz2 = (qx * qz2);
			qxqw2 = (qw * qx2);
			qyqy2 = (qy * qy2);
			qyqz2 = (qy * qz2);
			qyqw2 = (qw * qy2);
			qzqz2 = (qz * qz2);
			qzqw2 = (qw * qz2);

			result.columns[0] = Vec4(((1.0f - qyqy2) - qzqz2), (qxqy2 - qzqw2), (qxqz2 + qyqw2), 0.0f);
			result.columns[1] = Vec4((qxqy2 + qzqw2), ((1.0f - qxqx2) - qzqz2), (qyqz2 - qxqw2), 0.0f);
			result.columns[2] = Vec4((qxqz2 - qyqw2), (qyqz2 + qxqw2), ((1.0f - qxqx2) - qyqy2), 0.0f);
			return result;
		}


		Mat4 Mat4::invert(const Mat4 &matrix) {
			Mat4 result = matrix;
			return result.invert();
		}

		Mat4 Mat4::lookAt(const Vec3 &from, const Vec3 &to, const Vec3 &axis)
		{
			Vec3 copyFrom, copyTo;
			copyFrom = from;
			copyTo = to;

			Vec3 forward = (copyFrom - copyTo).normalize();
			Vec3 right = (axis.normalize()).cross(forward);
			Vec3 up = forward.cross(right);

			Mat4 result = identity();

			result.elements[0 + 0 * 4] = right.x;
			result.elements[1 + 0 * 4] = right.y;
			result.elements[2 + 0 * 4] = right.z;
			result.elements[0 + 1 * 4] = up.x;
			result.elements[1 + 1 * 4] = up.y;
			result.elements[2 + 1 * 4] = up.z;
			result.elements[0 + 3 * 4] = forward.x;
			result.elements[1 + 3 * 4] = forward.y;
			result.elements[2 + 3 * 4] = forward.z;

			result.elements[0 + 4 * 4] = from.x;
			result.elements[1 + 4 * 4] = from.y;
			result.elements[2 + 4 * 4] = from.z;

			return result;
		}

		Mat4 Mat4::transpose(const Mat4& matrix)
		{
			return Mat4(
				Vec4(matrix.columns[0].x, matrix.columns[1].x, matrix.columns[2].x, matrix.columns[3].x),
				Vec4(matrix.columns[0].y, matrix.columns[1].y, matrix.columns[2].y, matrix.columns[3].y),
				Vec4(matrix.columns[0].z, matrix.columns[1].z, matrix.columns[2].z, matrix.columns[3].z),
				Vec4(matrix.columns[0].w, matrix.columns[1].w, matrix.columns[2].w, matrix.columns[3].w)
			);
		}

	}

}