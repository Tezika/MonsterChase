#include "stdafx.h"
#include "RenderManager.h"
#include "RenderInfo.h"
#include "TList.h"
#include "GameObject.h"

namespace Engine
{
	namespace Render
	{
		void TestKeyCallback( unsigned int i_VKeyID, bool bWentDown )
		{
#ifdef _DEBUG
			const size_t	lenBuffer = 65;
			char			Buffer[lenBuffer];

			sprintf_s( Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up" );
			OutputDebugStringA( Buffer );
#endif // __DEBUG
		}

		bool RenderManager::Initialize()
		{
			m_pRenderInfo = new TList<RenderInfo>();
			return true;
		}

		void RenderManager::Update( float i_dt )
		{
			bool bEnd = false;
			GLib::SetKeyStateChangeCallback( TestKeyCallback );
			GLib::Service( bEnd );
			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();

			if ( bEnd )
			{
				return;
			}

			auto ptr = m_pRenderInfo->m_pHead;
			while ( ptr != nullptr )
			{
				RenderInfo * renderInfo = ptr->m_pData;
				GLibSprite * pSprite = renderInfo->GetSprite();
				auto posOfGo = renderInfo->GetGameObject()->GetPosition();

				// Set the render spirte's position based on the current position of gameObject
				renderInfo->SetPosition( posOfGo.m_x, posOfGo.m_y );

				// Render the sprite
				if ( pSprite != nullptr )
				{
					GLib::Sprites::RenderSprite( *pSprite, renderInfo->GetPosition(), 0 );
				}

				ptr = ptr->m_pNext;
			}
			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
			// Iterate the list to update every RenderInfo
			// Draw every sprite in one screen
		}

		bool RenderManager::Destroy()
		{
			return true;
		}
	}
}
