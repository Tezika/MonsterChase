#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // !M_PI
#define degToRad(angleDegrees) (float)((angleDegrees) * M_PI / 180.0)

namespace Engine
{
	void* LoadFile( const char* i_pFilename, size_t& o_sizeFile );
	float RandomInRange( float min, float max );
}