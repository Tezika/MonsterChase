#pragma once
#include "stdio.h"
#include <type_traits>
#include <math.h>

namespace Engine
{
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	struct Point2D
	{
		Point2D()
		{
		}

		inline Point2D( T i_x, T i_y ) :
			m_x( i_x ),
			m_y( i_y )
		{
		}

		inline Point2D( const Point2D<T> & i_other ) :
			m_x( i_other.m_x ),
			m_y( i_other.m_y )
		{
		}

		inline Point2D<T> & operator=( const Point2D<T> & i_other )
		{
			this->m_x = i_other.m_x;
			this->m_y = i_other.m_y;
			return *this;
		}

		inline Point2D<T> & operator+=( const Point2D<T> & i_other )
		{
			this->m_x += i_other.m_x;
			this->m_y += i_other.m_y;
			return *this;
		}

		inline Point2D<T> & operator-=( const Point2D<T> & i_other )
		{
			this->m_x -= i_other.m_x;
			this->m_y -= i_other.m_y;
			return *this;
		}

		inline Point2D<T> & operator+( const Point2D<T> & i_other )
		{
			this->m_x += i_other.m_x;
			this->m_y += i_other.m_y;
			return *this;
		}

		inline Point2D<T> & operator-( const Point2D<T> & i_other )
		{
			this->m_x -= i_other.m_x;
			this->m_y -= i_other.m_y;
			return *this;
		}

		inline Point2D<T> operator/( float i_other ) const
		{
			Point2D<T> newPoint( *this );
			newPoint.m_x /= i_other;
			newPoint.m_y /= i_other;
			return newPoint;
		}

		inline Point2D<T> operator*( float i_other ) const
		{
			Point2D<T> newPoint( *this );
			newPoint.m_x *= i_other;
			newPoint.m_y *= i_other;
			return newPoint;
		}

		inline T operator*( const Point2D<T> & i_other ) const
		{
			return i_other.m_x * this->m_x + i_other.m_y * this->m_y;
		}

		inline T Magnitude() const
		{
			return static_cast<T>( sqrt( this->m_x * this->m_x + this->m_y * this->m_y ) );
		}

		inline Point2D<T> Normalize()
		{
			T magnitude = this->Magnitude();
			// Prevent the situation for dividing zero.
			if ( magnitude == 0 )
			{
				return Point2D<T>( 0, 0 );
			}
			return Point2D<T>( this->m_x / magnitude, this->m_y / magnitude );
		}

		T m_x;
		T m_y;
	};

	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	inline bool operator==( const Engine::Point2D<T> & i_lhs, const Engine::Point2D<T>  &i_rhs )
	{
		return i_lhs.m_x == i_rhs.m_x && i_lhs.m_y == i_rhs.m_y;
	}

	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	inline bool operator!=( const Engine::Point2D<T> & i_lhs, const Engine::Point2D<T> & i_rhs )
	{
		return i_lhs.m_x != i_rhs.m_x || i_lhs.m_y != i_rhs.m_y;
	}
}