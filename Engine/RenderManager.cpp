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
			assert( m_pRenderInfos );

#if defined(_DEBUG) && defined(_DrawDebugInfo)
			m_pDebugRenderInfos = new TList<RenderInfo>();
			assert( m_pDebugRenderInfos );
#endif //  _DEBUG

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

#if defined(_DEBUG) && defined(_DrawDebugInfo)
			this->DrawRenderInfos( m_pDebugRenderInfos );
#endif

			this->DrawRenderInfos( m_pRenderInfos );

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
			bool bSucceed = false;

			// Clean the render objects
			bSucceed = this->ClearRenderInfos( m_pRenderInfos );
			assert( bSucceed );

#if defined(_DEBUG) && defined(_DrawDebugInfo)
			bSucceed = false;
			bSucceed = this->ClearRenderInfos( m_pDebugRenderInfos );
			assert( bSucceed );
#endif
			m_pDebugDotInfo = nullptr;
			// Shutdown the GLib fininally
			GLib::Shutdown();
			DEBUG_PRINT_ENGINE( "The render system destoried succuessfully!" );
			return true;
		}

		bool RenderManager::ClearRenderInfos( TList<RenderInfo> * pRenderInfos )
		{
			assert( pRenderInfos );
			// Clean the render objects
			Node<RenderInfo> * ptr = pRenderInfos->GetHead();
			RenderInfo * removeRenderInfo = nullptr;
			while ( ptr != nullptr )
			{
				removeRenderInfo = ptr->GetData();
				assert( removeRenderInfo );
				ptr = pRenderInfos->Remove( ptr );
				delete removeRenderInfo;
			}
			// Delete the renderinfo's manager
			delete pRenderInfos;
			pRenderInfos = nullptr;
			return true;
		}

		void RenderManager::DrawRenderInfos( TList<RenderInfo> * pRenderInfos )
		{
			assert( pRenderInfos );
			// Iterate the list to update every RenderInfo
			// And render every sprite into the screen
			auto ptr = pRenderInfos->GetHead();;
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
					GLib::Sprites::RenderSprite( *pSprite,
						renderInfo->GetPosition(),
						pGo == nullptr ? 0 : degToRad( pGo->GetZRot() ),
						renderInfo->GetRenderScaleX(),
						renderInfo->GetRenderScaleY()
					);
				}

				ptr = ptr->GetNext();
			}
		}

#if defined(_DEBUG) && defined(_DrawDebugInfo)
		void RenderManager::DrawDebugDot( float i_pos_x, float i_pos_y )
		{
			//m_pDebugDotInfo->SetRenderable( true );
			//m_pDebugDotInfo->SetPosition( i_pos_x, i_pos_y );
		}

		void RenderManager::HideDebugDot()
		{
			//m_pDebugDotInfo->SetRenderable( false );
		}

		RenderInfo * RenderManager::AddDebugRenderObject( SmartPtr<GameObject> i_pGo, const TString &  i_strSpriteName )
		{
			GLibSprite * pSprite = CreateSprite( const_cast<char*> ( i_strSpriteName.c_str() ) );
			assert( pSprite );
			RenderInfo * newRenderObject = RenderInfo::Create( i_pGo, pSprite, GLibPoint2D{ 0.0f, 0.0f } );
			assert( newRenderObject );
			return m_pDebugRenderInfos->InsertToTail( newRenderObject )->GetData();
		}

		bool RenderManager::RemoveDebugRenderObject( GameObject * i_pGo )
		{
			assert( i_pGo );
			Node<RenderInfo> * ptr = m_pDebugRenderInfos->GetHead();
			RenderInfo * removeRenderInfo = nullptr;
			while ( ptr != nullptr )
			{
				removeRenderInfo = ptr->GetData();
				if ( removeRenderInfo->GetGameObject() == i_pGo )
				{
					assert( removeRenderInfo );
					ptr = m_pDebugRenderInfos->Remove( ptr );
					delete removeRenderInfo;
				}
				else
				{
					ptr = ptr->GetNext();
				}
			}
			return true;
		}
#endif
	}
}