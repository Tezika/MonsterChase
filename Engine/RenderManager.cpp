#include "stdafx.h"
#include "RenderManager.h"
#include "RenderInfo.h"
#include "TList.h"
#include "GameObject.h"
#include "Assert.h"
#include "TString.h"
#include "GLibUtility.h"

namespace Engine
{
	namespace Render
	{
		extern GLib::Sprites::Sprite * CreateSprite( const char * i_pFilename );
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
			m_pRenderInfos = new TList<RenderInfo>();
			assert( m_pRenderInfos );
			DEBUG_PRINT( "The render system initialized succuessfully!" );
			return true;
		}

		void RenderManager::Update( float i_dt, bool & bEnd )
		{
			GLib::SetKeyStateChangeCallback( TestKeyCallback );
			GLib::Service( bEnd );

			if ( bEnd )
			{
				return;
			}

			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();
			GLib::Sprites::BeginRendering();

			// Iterate the list to update every RenderInfo
			// And render every sprite into the screen
			auto ptr = m_pRenderInfos->m_pHead;
			while ( ptr != nullptr )
			{
				RenderInfo * renderInfo = ptr->m_pData;
				GLibSprite * pSprite = renderInfo->GetSprite();
				auto posOfGo = renderInfo->GetGameObject()->GetPosition();

				// Set the render spirte's position based on the current position of gameObject
				renderInfo->SetPosition( (float) posOfGo.m_x, (float) posOfGo.m_y );

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
		}

		bool RenderManager::AddRenderObject( GameObject * i_pGo, const TString &  i_strSpriteName )
		{
			assert( i_pGo );
			GLibSprite * pSprite = CreateSprite( const_cast<char*> ( i_strSpriteName.c_str() ) );
			assert( pSprite );
			RenderInfo * newRenderObject = new RenderInfo( i_pGo, pSprite, GLibPoint2D{ (float) i_pGo->GetPosition().m_x, (float) i_pGo->GetPosition().m_y } );
			assert( newRenderObject );
			return ( m_pRenderInfos->InsertToTail( newRenderObject ) != nullptr );
		}

		bool RenderManager::RemoveRenderObject( GameObject * i_pGo )
		{
			assert( i_pGo );
			Node<RenderInfo> * ptr = m_pRenderInfos->m_pHead;
			RenderInfo * removeRenderInfo = nullptr;
			while ( ptr != nullptr )
			{
				if ( ptr->m_pData->GetGameObject() == i_pGo )
				{
					removeRenderInfo = ptr->m_pData;
					assert( removeRenderInfo );
					ptr = m_pRenderInfos->Remove( ptr );
					delete removeRenderInfo;
				}
				else
				{
					ptr = ptr->m_pNext;
				}
			}
			return true;
		}

		bool RenderManager::Destroy()
		{
			// Clean the render objects
			Node<RenderInfo> * ptr = m_pRenderInfos->m_pHead;
			RenderInfo * removeRenderInfo = nullptr;
			while ( ptr != nullptr )
			{
				removeRenderInfo = ptr->m_pData;
				assert( removeRenderInfo );
				ptr = m_pRenderInfos->Remove( ptr );
				delete removeRenderInfo;
			}
			// Delete the renderinfo's manager
			delete m_pRenderInfos;
			m_pRenderInfos = nullptr;

			// Shutdown the GLib fininally
			GLib::Shutdown();
			DEBUG_PRINT( "The render system destoried succuessfully!" );
			return true;
		}
	}
}