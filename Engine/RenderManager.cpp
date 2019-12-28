#include "stdafx.h"
#include "RenderManager.h"
#include "RenderInfo.h"
#include "TList.h"
#include "GameObject.h"
#include "Assert.h"
#include "TString.h"
#include "GLibUtility.h"
#include "PhysicsManager.h"
#include "PhysicsInfo.h"
#include "AABB.h"
#include "HashedString.h"
#include <ReferenceCounting/SmartPtr.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // !M_PI

#define degToRad(angleDegrees) (float)((angleDegrees) * M_PI / 180.0)

namespace Engine
{
	namespace Render
	{
		extern GLib::Sprites::Sprite* CreateSprite( const char* i_pFilename );

		bool RenderManager::Initialize( HINSTANCE i_hInstance, int i_nCmdShow, int i_wWidth, int i_wHeight, const char* i_pWindowName )
		{
			// Setup the GLib.
			bool bSuccess = GLib::Initialize( i_hInstance, i_nCmdShow, i_pWindowName, -1, i_wWidth, i_wHeight );
			if (!bSuccess)
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

		void RenderManager::Update( float i_dt, bool& i_bEnd )
		{
			GLib::Service( i_bEnd );

			if (i_bEnd)
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

		RenderInfo* RenderManager::AddRenderObject( SmartPtr<GameObject> i_pGo, const char* i_strSpriteName, float i_spriteSizeX, float i_spriteSizeY )
		{
			assert( i_spriteSizeX != 0 );
			assert( i_spriteSizeY != 0 );
			// Add RenderInfo in
			RenderInfo* pRetInfo = this->AddRenderInfo( m_pRenderInfos, i_pGo, i_strSpriteName, i_spriteSizeX, i_spriteSizeY );
			assert( pRetInfo );

			// Add a debug AABB RenderInfo in.
#if defined(_DEBUG) && defined(_DrawDebugInfo)
			RenderInfo* pDebugInfo = this->AddRenderInfo( m_pDebugRenderInfos, i_pGo, "Content//BoundingBox_Collided.dds", i_spriteSizeX, i_spriteSizeY );
			assert( pDebugInfo );
			pDebugInfo->SetRenderable( true );
#endif
			return pRetInfo;
		}

		bool RenderManager::RemoveRenderObject( SmartPtr<GameObject> i_pGo )
		{
			assert( i_pGo );
			bool bSucceed = false;
			bSucceed = this->RemoveRenderInfo( m_pRenderInfos, i_pGo );
			assert( bSucceed );
#if defined(_DEBUG) && defined(_DrawDebugInfo)
			bSucceed = false;
			bSucceed = this->RemoveRenderInfo( m_pDebugRenderInfos, i_pGo );
			assert( bSucceed );
#endif
			return bSucceed;
		}

		RenderInfo* RenderManager::AddRenderInfo( TList<RenderInfo>* pRenderInfos, SmartPtr<GameObject> i_pGo, const char* i_pStrName, float i_spriteSizeX, float i_spriteSizeY )
		{
			assert( i_spriteSizeX != 0 );
			assert( i_spriteSizeY != 0 );
			GLibSprite* pSprite = CreateSprite( i_pStrName );
			assert( pSprite );
			RenderInfo* pNewRenderObject = RenderInfo::Create( i_pGo, pSprite, GLibPoint2D{ 0.0f, 0.0f } );
			assert( pNewRenderObject );
			// Adjust the render sprite's size based on AABB size.
			Physics::PhysicsInfo* pAssociatedPhysicsInfo = Physics::PhysicsManager::GetInstance().GetInfoByGameObject( i_pGo );
			assert( pAssociatedPhysicsInfo );
			AABB* pAABB = pAssociatedPhysicsInfo->GetAABB();
			float xScale = pAABB->extends.m_x * 2 / i_spriteSizeX;
			float yScale = pAABB->extends.m_y * 2 / i_spriteSizeY;
			pNewRenderObject->SetRenderScaleX( xScale );
			pNewRenderObject->SetRenderScaleY( yScale );
			return pRenderInfos->Insert( pNewRenderObject )->GetData();
		}

		bool RenderManager::RemoveRenderInfo( TList<RenderInfo>* pRenderInfos, SmartPtr<GameObject> i_pGo )
		{
			assert( i_pGo );
			Node<RenderInfo>* ptr = pRenderInfos->GetHead();
			RenderInfo* removeRenderInfo = nullptr;
			while (ptr != nullptr)
			{
				removeRenderInfo = ptr->GetData();
				if (removeRenderInfo->GetGameObject() == i_pGo)
				{
					assert( removeRenderInfo );
					ptr = pRenderInfos->Remove( ptr );
					delete removeRenderInfo;
				}
				else
				{
					ptr = ptr->GetNext();
				}
			}
			return true;
		}

		RenderInfo* RenderManager::GetRenderInfoByGameObject( TList<RenderInfo>* i_pRenderInfos, SmartPtr<GameObject> i_pGo )
		{
			assert( i_pGo );
			assert( i_pRenderInfos );
			Node<RenderInfo>* ptr = i_pRenderInfos->GetHead();
			RenderInfo* pCurrentInfo = nullptr;
			while (ptr != nullptr)
			{
				pCurrentInfo = ptr->GetData();
				if (pCurrentInfo->GetGameObject() == i_pGo)
				{
					return pCurrentInfo;
				}
				ptr = ptr->GetNext();
			}
			return nullptr;
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

			// Shutdown the GLib fininally
			GLib::Shutdown();
			DEBUG_PRINT_ENGINE( "The render system destoried succuessfully!" );
			return true;
		}

		bool RenderManager::ClearRenderInfos( TList<RenderInfo>* pRenderInfos )
		{
			assert( pRenderInfos );
			pRenderInfos->Clear( true );
			delete pRenderInfos;
			pRenderInfos = nullptr;
			return true;
		}

		void RenderManager::DrawRenderInfos( TList<RenderInfo>* pRenderInfos )
		{
			assert( pRenderInfos );

			// Iterate the list to update every RenderInfo
			// And render every sprite into the screen
			auto ptr = pRenderInfos->GetHead();
			while (ptr != nullptr)
			{
				RenderInfo* renderInfo = ptr->GetData();
				// Check if it is renderable first
				if (!renderInfo->IsRenderable())
				{
					ptr = ptr->GetNext();
					continue;
				}

				GLibSprite* pSprite = renderInfo->GetSprite();
				SmartPtr<GameObject> pGo = renderInfo->GetGameObject();
				if (pGo != nullptr)
				{
					Vector3SSE posOfGo = pGo->GetPosition();
					// Set the render spirte's position based on the current position of gameObject
					renderInfo->SetPosition( posOfGo.x(), posOfGo.y() );
				}

				// Render the sprite
				if (pSprite != nullptr)
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

		RenderInfo* RenderManager::GetRealRenderInfoByGameObject( SmartPtr<GameObject> i_pGo )
		{
			return this->GetRenderInfoByGameObject( m_pRenderInfos, i_pGo );
		}

#if defined(_DEBUG) && defined(_DrawDebugInfo)
		RenderInfo* RenderManager::GetDebugRenderInfoByGameObject( SmartPtr<GameObject> i_pGo )
		{
			return this->GetRenderInfoByGameObject( m_pDebugRenderInfos, i_pGo );
		}
#endif
	}
}