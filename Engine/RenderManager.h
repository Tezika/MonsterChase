#pragma once
#include "Windows.h"

namespace Engine
{
	class GameObject;

	template<typename T>
	class TList;

	class TString;

	template<class T>
	class SmartPtr;

	namespace Render
	{
#ifndef _DrawDebugInfo
		//#define _DrawDebugInfo
#endif // !_DrawDebugInfo

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

			RenderInfo * AddRenderObject( SmartPtr<GameObject> i_pGo, const TString & i_strSpriteName, float i_spriteSizeX, float i_spriteSizeY );
			bool RemoveRenderObject( SmartPtr<GameObject> i_pGo );

			// Schedule functions
			bool Initialize( HINSTANCE i_hInstance, int i_hPrevInstance );
			void Update( float i_dt, bool & bEnd );
			bool Destroy();

		private:
			RenderManager() {};
			RenderInfo * m_pDebugDotInfo;
			TList<RenderInfo> * m_pRenderInfos;

			void DrawRenderInfos( TList<RenderInfo> * pRenderInfos );
			bool ClearRenderInfos( TList<RenderInfo> * pRenderInfos );

			RenderInfo * AddRenderInfo( TList<RenderInfo> * pRenderInfos, SmartPtr<GameObject> i_pGo, const TString & i_strSpriteName, float i_spriteSizeX, float i_spriteSizeY );
			bool RemoveRenderInfo( TList<RenderInfo> * pRenderInfos, SmartPtr<GameObject> i_pGo );
#if defined(_DEBUG) && defined(_DrawDebugInfo)
			TList<RenderInfo> * m_pDebugRenderInfos;
#endif
		};
	}
}