#include "stdafx.h"
#include "RenderInfo.h"
#include "GameObject.h"

namespace Engine
{
	namespace Render
	{
		RenderInfo::RenderInfo( GameObject * i_pGo, GLibSprite * i_pSprite, GLibPoint2D i_pos ) :
			m_pGo( i_pGo ),
			m_pSprite( i_pSprite ),
			m_posOfSprite( i_pos )
		{

		}

		RenderInfo::~RenderInfo()
		{
			m_pGo = nullptr;
			if ( m_pSprite != nullptr )
			{
				GLib::Sprites::Release( m_pSprite );
				m_pSprite = nullptr;
			}
		}
	}
}
