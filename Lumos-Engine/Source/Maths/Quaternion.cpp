#include "ls.h"

#include "quaternion.h"

namespace lumos {

	namespace maths {

		Quaternion::Quaternion() :
			x(0), y(0), z(0), w(0) {

		}

		Quaternion::Quaternion(const Quaternion &quaternion) {
			this->x = quaternion.x;
			this->y = quaternion.y;
			this->z = quaternion.z;
			this->w = quaternion.w;
		}

		Quaternion::Quaternion(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Quaternion::Quaternion(const Vec4 &vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			w = vector.w;
		}

		Quaternion::Quaternion(float scalar)
		{
			x = scalar;
			y = scalar;
			z = scalar;
			w = scalar;
		}
		Quaternion::Quaternion(const Vec3 &xyz, float w)
		{
			this->setXYZ(xyz);
			this->w = w;
		}

		Quaternion Quaternion::identity()
		{
			return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		}

		Quaternion Quaternion::fromEulerAngles(const Vec3 &angles)
		{
			Quaternion pitch(Vec3(1.0, 0.0, 0.0), angles.x);
			Quaternion yaw(Vec3(0.0, 1.0, 0.0), angles.y);
			Quaternion roll(Vec3(0.0, 0.0, 1.0), angles.z);
			return pitch * yaw * roll;
		}

		Quaternion &Quaternion::operator =(const Quaternion &quaternion)
		{
			x = quaternion.x;
			y = quaternion.y;
			z = quaternion.z;
			w = quaternion.w;
			return *this;
		}

		Quaternion &Quaternion::setXYZ(const Vec3 &vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			return *this;
		}

		const Vec3 Quaternion::getXYZ() const
		{
			return Vec3(x, y, z);
		}

		Quaternion &Quaternion::setElement(uint idx, float value)
		{
			*(&x + idx) = value;
			return *this;
		}

		float Quaternion::getElement(uint idx) const
		{
			return *(&x + idx);
		}

		float Quaternion::operator [](uint idx) const
		{
			return *(&x + idx);
		}

		Vec3 Quaternion::getAxis() const
		{
			float x = 1.0f - w * w;
			if (x < 0.0000001f)
				return Vec3(1.0f, 0.0f, 0.0f);

			float x2 = x * x;
			return getXYZ() / x2;
		}

		Vec3 Quaternion::toEulerAngles() const
		{
			return Vec3(atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
				atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
				asin(2 * x * y + 2 * z * w));
		}

		const Quaternion Quaternion::operator+(const Quaternion& quaternion) const
		{
			return Quaternion(x + quaternion.x, y + quaternion.y, z + quaternion.z, w + quaternion.w);
		}

		const Quaternion Quaternion::operator-(const Quaternion& quaternion) const
		{
			return Quaternion(x - quaternion.x, y - quaternion.y, z - quaternion.z, w - quaternion.w);
		}

		const Quaternion Quaternion::operator*(float scalar) const
		{
			return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		const Quaternion Quaternion::operator/(float scalar) const
		{
			return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		const Quaternion Quaternion::operator-() const
		{
			return Quaternion(-x, -y, -z, -w);
		}


		bool Quaternion::operator ==(const Quaternion & Quaternion) const
		{
			return (x == Quaternion.x) && (y == Quaternion.y) && (z == Quaternion.z) && (w == Quaternion.w);
		}

		bool Quaternion::operator !=(const Quaternion & Quaternion) const
		{
			return !(*this == Quaternion);
		}

		float norm(const Quaternion& quaternion)
		{
			float result;
			result = (quaternion.x * quaternion.x);
			result = (result + (quaternion.y * quaternion.y));
			result = (result + (quaternion.z * quaternion.z));
			result = (result + (quaternion.w * quaternion.w));
			return result;
		}

		float length(const Quaternion& quaternion)
		{
			return sqrt(norm(quaternion));
		}

		const Quaternion normalize(const Quaternion& quaternion)
		{
			float lenSqr, lenInv;
			lenSqr = norm(quaternion);
			lenInv = MathFunctions::RSqrt(lenSqr);
			return quaternion * lenInv;
		}

		const Quaternion Quaternion::rotation(const Vec3& unitVector0, const Vec3& unitVector1)
		{
			float cosHalfAngleX2, recipCosHalfAngleX2;
			cosHalfAngleX2 = sqrt((2.0f * (1.0f + unitVector0.dot(unitVector1))));
			recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
			return Quaternion((unitVector0.cross(unitVector1) * recipCosHalfAngleX2), (cosHalfAngleX2 * 0.5f));
		}

		const Quaternion Quaternion::rotation(float radians, const Vec3 &unitVector)
		{
			float angle = radians * 0.5f;
			return Quaternion((unitVector * sin(angle)), cos(angle));
		}

		const Quaternion Quaternion::operator*(const Quaternion& quat) const
		{
			return normalize(Quaternion(
				(((w * quat.x) + (x * quat.w)) + (y * quat.z)) - (z * quat.y),
				(((w * quat.y) + (y * quat.w)) + (z * quat.x)) - (x * quat.z),
				(((w * quat.z) + (z * quat.w)) + (x * quat.y)) - (y * quat.x),
				(((w * quat.w) - (x * quat.x)) - (y * quat.y)) - (z * quat.z)
			));
		}

		Vec3 Quaternion::rotate(const Quaternion& quaternion, const Vec3& vector)
		{
			float tmpX, tmpY, tmpZ, tmpW;
			tmpX = (((quaternion.w * vector.x) + (quaternion.y * vector.z)) - (quaternion.z * vector.y));
			tmpY = (((quaternion.w * vector.y) + (quaternion.z * vector.x)) - (quaternion.x * vector.z));
			tmpZ = (((quaternion.w * vector.z) + (quaternion.x * vector.y)) - (quaternion.y * vector.x));
			tmpW = (((quaternion.x * vector.x) + (quaternion.y * vector.y)) + (quaternion.z * vector.z));
			return Vec3(
				((((tmpW * quaternion.x) + (tmpX * quaternion.w)) - (tmpY * quaternion.z)) + (tmpZ * quaternion.y)),
				((((tmpW * quaternion.y) + (tmpY * quaternion.w)) - (tmpZ * quaternion.x)) + (tmpX * quaternion.z)),
				((((tmpW * quaternion.z) + (tmpZ * quaternion.w)) - (tmpX * quaternion.y)) + (tmpY * quaternion.x))
			);
		}

		Quaternion Quaternion::conjugate() const
		{
			return Quaternion(-x, -y, -z, w);
		}

		const Quaternion select(const Quaternion& quaternion0, const Quaternion& quaternion1, bool select1)
		{
			return Quaternion(select1 ? quaternion1.x : quaternion0.x, select1 ? quaternion1.y : quaternion0.y, select1 ? quaternion1.z : quaternion0.z, select1 ? quaternion1.w : quaternion0.w);
		}

		float Quaternion::dot(const Quaternion& other) const
		{
			float result = (x * other.x);
			result = (result + (y * other.y));
			result = (result + (z * other.z));
			result = (result + (w * other.w));
			return result;
		}

	}

}