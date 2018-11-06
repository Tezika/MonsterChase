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
			this->m_x = 0;
			this->m_y = 0;
		}

		inline Point2D(T x, T y)
		{
			this->m_x = x;
			this->m_y = y;
		}

		inline Point2D(const Point2D<T>& other)
		{
			this->m_x = other.m_x;
			this->m_y = other.m_y;
		}

		inline Point2D<T>& operator=(const Point2D<T>& other)
		{
			this->m_x = other.m_x;
			this->m_y = other.m_y;
			return *this;
		}

		inline Point2D<T>& operator+=(const Point2D<T>& other)
		{
			this->m_x = other.m_x + this->m_x;
			this->m_y = other.m_y + this->m_y;
			return *this;
		}

		inline Point2D<T>& operator-=(const Point2D<T>& other)
		{
			this->m_x = this->m_x - other.m_x;
			this->m_y = this->m_y - other.m_y;
			return *this;
		}

		T m_x;
		T m_y;
	};

	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	inline bool operator==(const Engine::Point2D<T>& lhs, const Engine::Point2D<T>& rhs)
	{
		return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
	}

	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	inline bool operator!=(const Engine::Point2D<T>& lhs, const Engine::Point2D<T>& rhs)
	{
		return lhs.m_x != rhs.m_x || lhs.m_y != rhs.m_y;
	}
}