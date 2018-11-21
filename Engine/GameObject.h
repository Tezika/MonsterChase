#pragma once
#include "Point2D.h"
#include "TString.h"

namespace Engine
{
	class GameObject
	{
	public:
		GameObject();
		GameObject(const TString &, const Point2D<float> &);
		GameObject(const GameObject &);
		void operator= (const GameObject &);
		~GameObject();

		inline const Point2D<float> & GetPosition() { return m_position; }
		inline void SetPosition(const Point2D<float> & i_other) { m_position = i_other; };

		inline const Point2D<float> & GetDirection() { return m_direction; }
		inline void SetDirection(const Point2D<float> & i_other) { m_direction = i_other; };

	private:
		TString m_name;
		Point2D<float> m_direction;
		Point2D<float> m_position;
	};
}