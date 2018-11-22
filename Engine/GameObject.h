#pragma once
#include "Point2D.h"
#include "TString.h"

namespace Engine
{
	class GameObject
	{
	public:
		GameObject();
		GameObject(const TString &, const Point2D<int> &);
		GameObject(const GameObject &);
		void operator = (const GameObject &);
		~GameObject();

		inline const Point2D<int> & GetPosition() { return m_position; }
		inline void SetPosition(const Point2D<int> & i_other) { m_position = i_other; };

		inline const Point2D<int> & GetDirection() { return m_direction; }
		inline void SetDirection(const Point2D<int> & i_other) { m_direction = i_other; };

	private:
		TString m_name;
		Point2D<int> m_direction;
		Point2D<int> m_position;
	};
}