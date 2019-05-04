#pragma once

#include "Delegate.h"
#include <vector>
#include <algorithm>

namespace Engine
{
	namespace Messaging
	{
		template<class...Params>
		class MultiCastDelegate
		{
		public:
			MultiCastDelegate(){};
			~MultiCastDelegate(){};

			void AddDelegate( Delegate<Params...> & i_Delegate )
			{
				m_Receivers.push_back( i_Delegate );
			}
			void RemoveDelegate( Delegate<Params...> & i_Delegate )
			{
				m_Receivers.erase( std::remove_if( m_Receivers.begin(), m_Receivers.end(), [&i_Delegate]( const Delegate<Params ...> & i_Entry ) {return i_Entry == i_Delegate; } ),
					m_Receivers.end() );
			}

			void ExecuteIfBound( Params...i_params )
			{
				for ( size_t i = 0; i < m_Receivers.size(); i++ )
				{
					m_Receivers[i].ExecuteIfBound( i_params ... );
				}
			}

			void RemoveAll()
			{
				m_Receivers.clear();
			}
		private:
			std::vector<Delegate<Params...>> m_Receivers;
		};
	}
}