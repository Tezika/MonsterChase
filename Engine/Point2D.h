#pragma once
#include "stdio.h"
#include <type_traits>

namespace Engine
{
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	struct Point2D
	{
		Point2D()
		{
			this->x = 0;
			this->y = 0;
		}

		inline Point2D(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		inline Point2D(const Point2D<T>& other)
		{
			this->x = other.x;
			this->y = other.y;
		}

		inline Point2D<T>& operator=(const Point2D<T>& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		inline Point2D<T>& operator+=(const Point2D<T>& other)
		{
			this->x = other.x + this->x;
			this->y = other.y + this->y;
			return *this;
		}

		inline Point2D<T>& operator-=(const Point2D<T>& other)
		{
			this->x = this->x - other.x;
			this->y = this->y - other.y;
			return *this;
		}

		T x;
		T y;
	};

	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	inline bool operator==(const Engine::Point2D<T>& lhs, const Engine::Point2D<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	inline bool operator!=(const Engine::Point2D<T>& lhs, const Engine::Point2D<T>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y;
	}
}