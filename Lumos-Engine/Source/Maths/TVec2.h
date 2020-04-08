#pragma once

#include "ls.h"

namespace lumos {

	namespace maths {

		template <class T>
		struct TVec2
		{
			T x, y;

			TVec2<T>();
			TVec2<T>(const T& x, const T& y);

			TVec2<T>& Add(const TVec2<T>& other);
			TVec2<T>& Subtract(const TVec2<T>& other);
			TVec2<T>& Multiply(const TVec2<T>& other);
			TVec2<T>& Divide(const TVec2<T>& other);

			friend TVec2<T> operator+(TVec2<T> left, const TVec2<T>& right);
			friend TVec2<T> operator-(TVec2<T> left, const TVec2<T>& right);
			friend TVec2<T> operator*(TVec2<T> left, const TVec2<T>& right);
			friend TVec2<T> operator/(TVec2<T> left, const TVec2<T>& right);

			bool operator==(const TVec2<T>& other);
			bool operator!=(const TVec2<T>& other);

			TVec2<T>& operator+=(const TVec2<T>& other);
			TVec2<T>& operator-=(const TVec2<T>& other);
			TVec2<T>& operator*=(const TVec2<T>& other);
			TVec2<T>& operator/=(const TVec2<T>& other);

			friend std::ostream& operator<<(std::ostream& stream, const TVec2& vector);
		};

		template <class T>
		TVec2<T>::TVec2()
		{
			x = 0;
			y = 0;
		}

		template <class T>
		TVec2<T>::TVec2(const T& x, const T& y)
		{
			this->x = x;
			this->y = y;
		}

		template <class T>
		TVec2<T>& TVec2<T>::Add(const TVec2<T>& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		template <class T>
		TVec2<T>& TVec2<T>::Subtract(const TVec2<T>& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		template <class T>
		TVec2<T>& TVec2<T>::Multiply(const TVec2<T>& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		template <class T>
		TVec2<T>& TVec2<T>::Divide(const TVec2<T>& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		template <class T>
		TVec2<T> operator+(TVec2<T> left, const TVec2<T>& right)
		{
			return left.Add(right);
		}

		template <class T>
		TVec2<T> operator-(TVec2<T> left, const TVec2<T>& right)
		{
			return left.Subtract(right);
		}

		template <class T>
		TVec2<T> operator*(TVec2<T> left, const TVec2<T>& right)
		{
			return left.Multiply(right);
		}

		template <class T>
		TVec2<T> operator/(TVec2<T> left, const TVec2<T>& right)
		{
			return left.Divide(right);
		}

		template <class T>
		TVec2<T>& TVec2<T>::operator+=(const TVec2<T>& other)
		{
			return Add(other);
		}

		template <class T>
		TVec2<T>& TVec2<T>::operator-=(const TVec2<T>& other)
		{
			return Subtract(other);
		}

		template <class T>
		TVec2<T>& TVec2<T>::operator*=(const TVec2<T>& other)
		{
			return Multiply(other);
		}

		template <class T>
		TVec2<T>& TVec2<T>::operator/=(const TVec2<T>& other)
		{
			return Divide(other);
		}

		template <class T>
		bool TVec2<T>::operator==(const TVec2<T>& other)
		{
			return x == other.x && y == other.y;
		}

		template <class T>
		bool TVec2<T>::operator!=(const TVec2<T>& other)
		{
			return !(*this == other);
		}

		template <class T>
		std::ostream& operator<<(std::ostream& stream, const TVec2<T>& vector)
		{
			stream << "TVec2: (" << vector.x << ", " << vector.y << ")";
			return stream;
		}

	}

}