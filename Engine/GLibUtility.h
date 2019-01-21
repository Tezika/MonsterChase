#pragma once
#include "GLib.h"
namespace Engine
{
	void * LoadFile( const char * i_pFilename, size_t & o_sizeFile );
	GLib::Sprites::Sprite * CreateSprite( const char * i_pFilename );
}