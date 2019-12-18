#pragma once
#include <GLib/GLib.h>
namespace Engine
{
	namespace Render
	{
		GLib::Sprites::Sprite * CreateSprite( const char * i_pFilename );
	}
}