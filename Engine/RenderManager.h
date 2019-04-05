#pragma once
#include "../Exports/GLib/GLib.h"

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

			bool AddRenderObject( SmartPtr<GameObject> i_pGo, const TString & i_strSpriteName );
			bool RemoveRenderObject( GameObject * i_pGo );

			// Schedule functions
			bool Initialize( HINSTANCE i_hInstance, int i_hPrevInstance );
			void Update( float i_dt, bool & bEnd );
			bool Destroy();

			// Debug function
#ifdef _DEBUG
			void DrawDebugDot( float i_pos_x, float i_pos_y );
#endif

		private:
			RenderManager() {};
			GLib::Sprites::Sprite * m_pDotSprite;
			TList<RenderInfo> * m_pRenderInfos;
		};
	}
}