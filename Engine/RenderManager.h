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

			RenderInfo * AddRenderObject( SmartPtr<GameObject> i_pGo, const TString & i_strSpriteName );
			bool RemoveRenderObject( GameObject * i_pGo );

			// Schedule functions
			bool Initialize( HINSTANCE i_hInstance, int i_hPrevInstance );
			void Update( float i_dt, bool & bEnd );
			bool Destroy();

			// Debug function
#if defined(_DEBUG) && defined(_DrawDebugInfo)
			void DrawDebugDot( float i_pos_x, float i_pos_y );
			void HideDebugDot();

			RenderInfo * AddDebugRenderObject( SmartPtr<GameObject> i_pGo, const TString & i_strSpriteName );
			bool RemoveDebugRenderObject( GameObject * i_pGo );
#endif

		private:
			RenderManager() {};
			RenderInfo * m_pDebugDotInfo;
			TList<RenderInfo> * m_pRenderInfos;
			bool ClearRenderInfos( TList<RenderInfo> * pRenderInfos );
			void DrawRenderInfos( TList<RenderInfo> * pRenderInfos );
#if defined(_DEBUG) && defined(_DrawDebugInfo)
				TList<RenderInfo> * m_pDebugRenderInfos;
#endif
		};
	}
}