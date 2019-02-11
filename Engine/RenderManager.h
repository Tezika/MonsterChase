#pragma once

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
			bool Initialize();
			void Update( float i_dt, bool & bEnd );
			bool Destroy();

		private:
			RenderManager() {};
			TList<RenderInfo> * m_pRenderInfos;
		};
	}
}
