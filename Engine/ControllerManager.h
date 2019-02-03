#pragma once

namespace Engine
{
	class IController;

	template<typename T>
	class TList;

	namespace Controller
	{

		class ControllerManager
		{
		public:
			static ControllerManager& GetInstance()
			{
				static ControllerManager instance;
				return instance;
			}
			ControllerManager( ControllerManager const& ) = delete;
			void operator=( ControllerManager const& ) = delete;

			bool AddContrller( IController * i_pController );
			bool RemoveController( IController * i_pController );

			// Schedule functions
			bool Initialize();
			void Update( float i_dt );
			bool Destroy();

		private:
			ControllerManager() {};
			TList<IController> * m_pControllers;
		};
	};
}
