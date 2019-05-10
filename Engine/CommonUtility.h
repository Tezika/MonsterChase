#pragma once
namespace Engine
{
	void * LoadFile( const char * i_pFilename, size_t & o_sizeFile );
	float RandomInRange( float min, float max );
}