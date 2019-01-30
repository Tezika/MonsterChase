#pragma once
#include "GLib.h"

class GameObject;

namespace Rendering
{
	typedef GLib::Sprites::Sprite GLibSprite;
	typedef GLib::Point2D GLibPoint2D;

	class RenderInfo
	{
	public:
		RenderInfo(){};
		RenderInfo( GameObject * i_pGo, GLibSprite * i_pSprite, GLibPoint2D i_pos );

		inline void SetPosition( GLibPoint2D & i_pos ) { m_posOfSprite = i_pos; };
		inline GLibPoint2D & GetPosition(){ return m_posOfSprite; };

		inline GLibSprite * GetSprite(){ return m_pSprite; };
		inline void SetSprite( GLibSprite * i_pSprite ){ m_pSprite = i_pSprite; };

		~RenderInfo();
	private:
		GameObject * m_pGo;
		GLibSprite * m_pSprite;
		GLibPoint2D m_posOfSprite;
	};
}