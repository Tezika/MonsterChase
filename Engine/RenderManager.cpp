#include "stdafx.h"
#include "RenderManager.h"
#include "RenderInfo.h"
#include "TList.h"
#include "GameObject.h"
#include "Assert.h"
#include "TString.h"
#include "GLibUtility.h"
#include "SmartPtr.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // !M_PI

#define degToRad(angleDegrees) (float)((angleDegrees) * M_PI / 180.0)

namespace Engine
{
	namespace Render
	{
		extern GLib::Sprites::Sprite * CreateSprite( const char * i_pFilename );
		//		void TestKeyCallback( unsigned int i_VKeyID, bool bWentDown )
		//		{
		//#ifdef _DEBUG
		//			const size_t	lenBuffer = 65;
		//			char			Buffer[lenBuffer];
		//
		//			sprintf_s( Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up" );
		//			OutputDebugStringA( Buffer );
		//#endif // __DEBUG
		//		}

		bool RenderManager::Initialize( HINSTANCE i_hInstance, int i_nCmdShow )
		{
			// Setup the GLib.
			bool bSuccess = GLib::Initialize( i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600 );
			if ( !bSuccess )
			{
				return bSuccess;
			}

			m_pRenderInfos = new TList<RenderInfo>();

#ifdef  _DEBUG
			// Add the debug renderinfo in.
			m_pDebugDotInfo = this->AddRenderObject( SmartPtr<GameObject>( nullptr ), "Data//Debug_dot.dds" );
			assert( m_pDebugDotInfo );
			// Set the renderable as the false initially.
			m_pDebugDotInfo->SetRenderable( false );
#endif //  _DEBUG

			assert( m_pRenderInfos );
			DEBUG_PRINT_ENGINE( "The render system initialized succuessfully!" );
			return true;
		}

		void RenderManager::Update( float i_dt, bool & bEnd )
		{
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
			auto ptr = m_pRenderInfos->GetHead();;
			while ( ptr != nullptr )
			{
				RenderInfo * renderInfo = ptr->GetData();
				// Check if it is renderable first
				if ( !renderInfo->IsRenderable() )
				{
					ptr = ptr->GetNext();
					continue;
				}

				GLibSprite * pSprite = renderInfo->GetSprite();
				SmartPtr<GameObject> pGo = renderInfo->GetGameObject();
				if ( pGo != nullptr )
				{
					Point2D<float> posOfGo = pGo->GetPosition();

					// Set the render spirte's position based on the current position of gameObject
					renderInfo->SetPosition( posOfGo.m_x, posOfGo.m_y );
				}

				// Render the sprite
				if ( pSprite != nullptr )
				{
					GLib::Sprites::RenderSprite( *pSprite, renderInfo->GetPosition(), pGo == nullptr ? 0 : degToRad( pGo->GetZRot() ) );
				}

				ptr = ptr->GetNext();
			}
			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
		}

		RenderInfo * RenderManager::AddRenderObject( SmartPtr<GameObject> i_pGo, const TString &  i_strSpriteName )
		{
			GLibSprite * pSprite = CreateSprite( const_cast<char*> ( i_strSpriteName.c_str() ) );
			assert( pSprite );
			RenderInfo * newRenderObject = RenderInfo::Create( i_pGo, pSprite, GLibPoint2D{ 0.0f, 0.0f } );
			assert( newRenderObject );
			return m_pRenderInfos->InsertToTail( newRenderObject )->GetData();
		}

		bool RenderManager::RemoveRenderObject( GameObject * i_pGo )
		{
			assert( i_pGo );
			Node<RenderInfo> * ptr = m_pRenderInfos->GetHead();
			RenderInfo * removeRenderInfo = nullptr;
			while ( ptr != nullptr )
			{
				removeRenderInfo = ptr->GetData();
				if ( removeRenderInfo->GetGameObject() == i_pGo )
				{
					assert( removeRenderInfo );
					ptr = m_pRenderInfos->Remove( ptr );
					delete removeRenderInfo;
				}
				else
				{
					ptr = ptr->GetNext();
				}
			}
			return true;
		}

		bool RenderManager::Destroy()
		{
			// Clean the render objects
			Node<RenderInfo> * ptr = m_pRenderInfos->GetHead();
			RenderInfo * removeRenderInfo = nullptr;
			while ( ptr != nullptr )
			{
				removeRenderInfo = ptr->GetData();
				assert( removeRenderInfo );
				ptr = m_pRenderInfos->Remove( ptr );
				delete removeRenderInfo;
			}
			// Delete the renderinfo's manager
			delete m_pRenderInfos;
			m_pRenderInfos = nullptr;
			m_pDebugDotInfo = nullptr;
			// Shutdown the GLib fininally
			GLib::Shutdown();
			DEBUG_PRINT_ENGINE( "The render system destoried succuessfully!" );
			return true;
		}

#ifdef _DEBUG
		void RenderManager::DrawDebugDot( float i_pos_x, float i_pos_y )
		{
			m_pDebugDotInfo->SetRenderable( true );
			m_pDebugDotInfo->SetPosition( i_pos_x, i_pos_y );
		}
#endif
	}
}