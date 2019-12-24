#pragma once

namespace TPong
{
	class Engine::HashedString;
	class Ball
	{
	public:
		Ball();
		Ball( const Engine::HashedString & i_name, const Engine::Vector3SSE & i_position );
		void Shoot();
		void Reset();
		virtual ~Ball();
	};
}