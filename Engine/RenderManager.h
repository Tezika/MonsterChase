#pragma once

namespace Engine
{
	template<typename T>
	class TList;

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

			// Schedule functions
			bool Initialize();
			void Update( float i_dt );
			bool Destroy();

		private:
			RenderManager() {};
			TList<RenderInfo> * m_pRenderInfo;
		};
	}
}
