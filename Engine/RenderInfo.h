#pragma once

#include "../Exports/GLib/GLib.h"
#include "SmartPtr.h"
#include "WeakPtr.h"

namespace Engine
{
	class GameObject;

	namespace Render
	{
		typedef GLib::Sprites::Sprite GLibSprite;
		typedef GLib::Point2D GLibPoint2D;

		class RenderInfo
		{
		public:
			static RenderInfo * Create( SmartPtr<GameObject> i_pGo, GLibSprite * i_pSprite, GLibPoint2D i_pos );

			inline void SetPosition( float i_x, float i_y ) { m_posOfSprite.x = i_x; m_posOfSprite.y = i_y; };
			inline GLibPoint2D & GetPosition(){ return m_posOfSprite; };

			inline GLibSprite * GetSprite(){ return m_pSprite; };
			inline void SetSprite( GLibSprite * i_pSprite ){ m_pSprite = i_pSprite; };

			inline SmartPtr<GameObject> GetGameObject() { return m_pGo.AcquireOwnership(); };

			RenderInfo( const RenderInfo & ) = delete;
			RenderInfo & operator=( const RenderInfo & ) = delete;

			~RenderInfo();
		private:
			RenderInfo(){};
			RenderInfo( SmartPtr<GameObject> i_pGo, GLibSprite * i_pSprite, GLibPoint2D i_pos );
			WeakPtr<GameObject> m_pGo;
			GLibSprite * m_pSprite;
			GLibPoint2D m_posOfSprite;
		};
	}
}
