#pragma once
#include <Engine/Assets/ReferenceCountedAssets.h>

namespace eae6320
{
	namespace Audio
	{
		namespace Sound
		{
			struct sSoundSource;
		}
		namespace SoundEffect
		{
			struct sSoundEffect
			{
			public:
#if defined(EAE6320_PLATFORM_WINDOWS)
				EAE6320_ASSETS_DECLAREREFERENCECOUNTINGFUNCTIONS();
				EAE6320_ASSETS_DECLAREDELETEDREFERENCECOUNTEDFUNCTIONS( sSoundEffect );
#endif
			private:
				EAE6320_ASSETS_DECLAREREFERENCECOUNT();
				sSoundEffect() = default;
				~sSoundEffect();
			};
		}
	}
}