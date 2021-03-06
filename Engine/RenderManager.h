#pragma once
#include "Windows.h"

namespace Engine
{
#ifndef _DrawDebugInfo
	//#define _DrawDebugInfo
#endif // !_DrawDebugInfo

	class GameObject;

	template<typename T>
	class TList;

	class HashedString;

	template<class T>
	class SmartPtr;

	namespace Render
	{
		class RenderInfo;

		// This is a singleton class for handling the Render stuff
		class RenderManager
		{
		public:
			static RenderManager& GetInstance()
			{
				static RenderManager instance;
				return instance;
			}

			RenderManager( RenderManager const& ) = delete;
			void operator=( RenderManager const& ) = delete;

			RenderInfo* AddRenderObject( SmartPtr<GameObject> i_pGo, const char* i_pStrSpriteName, float i_spriteSizeX, float i_spriteSizeY );
			bool RemoveRenderObject( SmartPtr<GameObject> i_pGo );

			// Schedule functions
			bool Initialize( HINSTANCE i_hInstance, int i_hPrevInstance, int i_wWidth, int i_wHeight, const char* i_pWindowName );
			void Update( float i_dt, bool& bEnd );
			bool Destroy();

			RenderInfo* GetRealRenderInfoByGameObject( SmartPtr<GameObject> i_pGo );
#if defined(_DEBUG) && defined(_DrawDebugInfo)
			RenderInfo* GetDebugRenderInfoByGameObject( SmartPtr<GameObject> i_pGo );
#endif

		private:
			RenderManager() {};
			TList<RenderInfo>* m_pRenderInfos;

			void DrawRenderInfos( TList<RenderInfo>* pRenderInfos );
			bool ClearRenderInfos( TList<RenderInfo>* pRenderInfos );

			RenderInfo* AddRenderInfo( TList<RenderInfo>* pRenderInfos, SmartPtr<GameObject> i_pGo, const char* i_strSpriteName, float i_spriteSizeX, float i_spriteSizeY );
			bool RemoveRenderInfo( TList<RenderInfo>* pRenderInfos, SmartPtr<GameObject> i_pGo );
			RenderInfo* GetRenderInfoByGameObject( TList<RenderInfo>* pRenderInfos, SmartPtr<GameObject> i_pGo );
#if defined(_DEBUG) && defined(_DrawDebugInfo)
			TList<RenderInfo>* m_pDebugRenderInfos;
#endif
		};
	}
}